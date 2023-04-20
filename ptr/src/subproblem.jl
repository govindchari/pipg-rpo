using Convex, ECOS

function solveSubproblem!(p::ptr)
    x = Variable(p.nx, p.K)
    u = Variable(p.nu, p.K)
    σ = Variable(1)

    nu = Variable(p.nx * (p.K - 1))
    Δ = Variable(p.K)
    Δσ = Variable(1)

    dx = x - p.xref
    du = u - p.uref
    dσ = σ - p.σref

    par = p.par

    # Objective
    # objective = (σ + p.wD * norm(Δ) + p.wDσ * norm(Δσ, 1) + p.wnu * sumsquares(nu)) / p.wnu
    objective = (sumsquares(u) + p.wD * norm(Δ) + p.wDσ * norm(Δσ) + p.wnu * norm(nu, 1)) / p.wnu

    # Dynamics Constraint
    constraints = Constraint[
        x[:, k+1] == p.A[:, :, k] * x[:, k] + p.A[:, 4:6, k] * u[:, k] + p.S[:, k] * σ + p.z[:, k] + nu[(k-1)*p.nx+1:k*p.nx] for k in 1:p.K-1
    ]

    # Boundary Conditions
    # x = [r v]
    push!(constraints, x[:, 1] == par.x0)
    push!(constraints, x[:, p.K] == par.xT)

    # Control Constraints
    for k = 1:p.K
        push!(constraints, norm(u[:, k]) <= par.umax)
    end

    # Trust Regions
    for k = 1:p.K
        push!(constraints, norm(dot(dx[:, k], dx[:, k]) + dot(du[:, k], du[:, k]), 2) <= Δ[k])
    end
    push!(constraints, norm(dσ, 2) <= Δσ)
    # push!(constraints, σ >= 10)


    prob = minimize(objective, constraints)
    solve!(prob, ECOS.Optimizer, silent_solver=true)
    p.xref = evaluate(x)
    p.uref = evaluate(u)
    p.σref = evaluate(σ)
    p.vc = reshape(evaluate(nu), (p.nx, p.K - 1))
    p.Δ = evaluate(Δ)
    p.Δσ = evaluate(Δσ)
end