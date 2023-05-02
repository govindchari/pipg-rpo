using Convex, ECOS, SCS

function solveSubproblem!(p::ptr)

    # Scaled optimization variables
    x = Variable(p.nx, p.K)
    u = Variable(p.nu, p.K)
    σ = Variable(p.K - 1)

    nu = Variable(p.nx * (p.K - 1))
    vb = Variable(p.K)
    Δ = Variable(p.K)
    Δσ = Variable(1)

    par = p.par

    # Scaled deviations
    dx = x - par.Px \ p.xref
    du = u - par.Pu \ p.uref
    dσ = σ - p.σref / par.Pσ

    par = p.par

    # Minimuim Control Effort
    # objective = (sumsquares(u) + p.wD * norm(Δ) + p.wDσ * norm(Δσ) + p.wvc * norm(nu, 1) + p.wvb * norm(vb, 1)) / max(p.wvc, p.wvb)

    # Minimum Fuel
    objective = p.wD * norm(Δ) + p.wDσ * norm(Δσ) + p.wvc * norm(nu, 1) + p.wvb * norm(vb, 1)
    for k = 1:p.K
        objective += norm(u[:, k], 2)
    end
    objective /= max(p.wvc, p.wvb)

    # Scaled Dynamics Matrices
    A(k) = par.Px \ p.A[:, :, k] * par.Px
    B(k) = par.Px \ p.A[:, 4:6, k] * par.Pu
    S(k) = par.Px \ p.S[:, k] * par.Pσ
    z(k) = par.Px \ p.z[:, k]
    constraints = Constraint[
        x[:, k+1] == A(k) * x[:, k] + B(k) * u[:, k] + S(k) * σ[k] + z(k) + nu[(k-1)*p.nx+1:k*p.nx] for k in 1:p.K-1
    ]

    # Boundary Conditions
    # x = [r v]
    push!(constraints, x[:, 1] == par.Px \ par.x0)
    push!(constraints, x[:, p.K] == par.Px \ par.xT)

    # State Constraints (Keepout Zone)
    Xi(k) = (p.xref[1:3, k] - par.rc) / norm((p.xref[1:3, k] - par.rc))
    for k = 1:p.K
        push!(constraints, par.rho <= norm(p.xref[1:3, k] - par.rc) + dot(Xi(k), (par.Px[1:3, 1:3] * x[1:3, k] - p.xref[1:3, k])) + vb[k])
        push!(constraints, vb[k] >= 0)
        push!(constraints, norm(x[4:6, k]) <= par.vmax / maximum(diag(par.Px[4:6, 4:6])))
    end

    # Control Constraints
    for k = 1:p.K
        push!(constraints, norm(u[:, k]) <= par.umax / maximum(diag(par.Pu)))
    end

    # Dilation Constraints
    for k = 1:p.K-1
        push!(constraints, σ[k] >= par.σmin / par.Pσ, σ[k] <= par.σmax / par.Pσ)
    end

    # Trust Regions
    for k = 1:p.K
        push!(constraints, norm(dot(dx[:, k], dx[:, k]) + dot(du[:, k], du[:, k]), 2) <= Δ[k])
    end
    push!(constraints, norm(dσ, 2) <= Δσ)

    prob = minimize(objective, constraints)
    solve!(prob, ECOS.Optimizer, silent_solver=true)

    p.xref = par.Px * evaluate(x)
    p.uref = par.Pu * evaluate(u)
    p.σref = par.Pσ * I(p.K - 1) * evaluate(σ)
    p.vc = reshape(evaluate(nu), (p.nx, p.K - 1))
    p.vb = evaluate(vb)
    p.Δ = evaluate(Δ)
    p.Δσ = evaluate(Δσ)
end