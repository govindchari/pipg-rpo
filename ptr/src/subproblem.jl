using Convex, ECOS

function solveSubproblem!(p::ptr, H, h)

    # Scaled optimization variables
    x = Variable(p.nx, p.K)
    u = Variable(p.nu, p.K)
    σ = Variable(p.K - 1)
    nu = Variable(p.nx * (p.K - 1))
    vb = Variable(p.K)

    par = p.par

    # Scaled deviations
    dx = x - par.Px \ p.xref
    du = u - par.Pu \ p.uref
    dσ = σ - p.σref / par.Pσ

    # Minimuim Control Effort
    objective = sumsquares(u) + p.wtr * (sumsquares(dx) + sumsquares(du) + sumsquares(dσ)) + p.wvc * norm(nu, 1) + p.wvb * sumsquares(vb)
    # objective = sumsquares(u) + p.wtr * (sumsquares(dx) + sumsquares(du) + sumsquares(dσ))

    # Minimum Fuel
    # objective = p.wtr * (sumsquares(dx) + sumsquares(du) + sumsquares(dσ)) + p.wvc * norm(nu, 1) + p.wvb * sumsquares(vb)
    # for k = 1:p.K
    #     objective += norm(u[:, k], 2)
    # end

    # Scaled Dynamics Matrices
    A(k) = par.Px \ p.A[:, :, k] * par.Px
    B(k) = par.Px \ p.A[:, 4:6, k] * par.Pu
    S(k) = par.Px \ p.S[:, k] * par.Pσ
    z(k) = par.Px \ p.z[:, k]
    constraints = Constraint[
        x[:, k+1] == A(k) * x[:, k] + B(k) * u[:, k] + S(k) * σ[k] + z(k) + nu[(k-1)*p.nx+1:k*p.nx] for k in 1:p.K-1
    ]
    # constraints = Constraint[
    #     x[:, k+1] == A(k) * x[:, k] + B(k) * u[:, k] + S(k) * σ[k] + z(k) for k in 1:p.K-1
    # ]

    # Boundary Conditions
    # x = [r v]
    push!(constraints, x[:, 1] == par.Px \ par.x0)
    push!(constraints, x[:, p.K] == par.Px \ par.xT)

    # State Constraints (Keepout Zone + Max Speed)
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

    prob = minimize(objective, constraints)
    solve!(prob, ECOS.Optimizer, silent_solver=true)

    xrs = par.Px \ p.xref
    urs = par.Pu \ p.uref
    σrs = p.σref ./ par.Pσ

    # println(prob.optval - p.wtr * (sum(xrs.^2) + sum(urs.^2) + sum(σrs.^2)))

    p.xref .= par.Px * evaluate(x)
    p.uref .= par.Pu * evaluate(u)
    p.σref .= par.Pσ * I(p.K - 1) * evaluate(σ)
    p.vc .= reshape(evaluate(nu), (p.nx, p.K - 1))
    # p.vb .= evaluate(vb)
    p.Δ = sqrt(norm(evaluate(dx)[:])^2 + norm(evaluate(du)[:])^2)
    p.Δσ = norm(evaluate(dσ))
    return evaluate(x)[:], evaluate(u)[:], evaluate(σ)[:]
end

function solveSubproblemVectorized!(p::ptr, P, q, H, h)
    n_x = 6
    n_u = 3
    K = p.K

    # z = Variable(n_x * (3 * K - 2) + n_u * (K - 1) + (2 * K - 1))
    # z = Variable(n_x * (K) + n_u * (K - 1) + (K - 1))
    z = Variable(n_x * (3 * K - 2) + n_u * (K - 1) + (K - 1))

    objective = (0.5 * quadform(z, P) + dot(z, q))
    constraints = Constraint[H*z==h]

    base = n_x * K + n_u * (K - 1) + (K - 1)
    shift = n_x * (K - 1)
    for k = 1:n_x*(p.K-1)
        push!(constraints, -z[base+shift+k] <= z[base+k])
        push!(constraints, z[base+k] <= z[base+shift+k])
    end

    push!(constraints, z[1:6] == par.Px \ par.x0)
    push!(constraints, z[p.K*nx-n_x+1:p.K*n_x] == par.Px \ par.xT)

    prob = minimize(objective, constraints)
    solve!(prob, ECOS.Optimizer, silent_solver=true)

    println(prob.optval)

    return evaluate(z)
end