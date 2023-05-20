using Convex, ECOS

function solveSubproblem!(p::ptr)

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

    # Minimum Control Effort
    objective = sumsquares(u) + p.wtr * (sumsquares(dx) + sumsquares(du) + sumsquares(dσ)) + p.wvc * norm(nu, 1) + p.wvb * sum(vb)

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

    p.xref .= par.Px * evaluate(x)
    p.uref .= par.Pu * evaluate(u)
    p.σref .= par.Pσ * I(p.K - 1) * evaluate(σ)
    p.vc .= reshape(evaluate(nu), (p.nx, p.K - 1))
    p.vb .= evaluate(vb)
    p.Δ = sqrt(norm(evaluate(dx)[:])^2 + norm(evaluate(du)[:])^2)
    p.Δσ = norm(evaluate(dσ))
end

function solveSubproblemVectorized!(p::ptr, P, q, H, h)
    n_x = 6
    n_u = 3
    K = p.K

    z = Variable(n_x * (3 * K - 2) + n_u * (K - 1) + (2 * K - 1))
    # z = Variable(n_x * (3 * K - 2) + n_u * (K - 1) + (K - 1))

    r = p.wtr * (sum((par.Px\p.xref)[:] .^ 2) + sum((par.Pu\p.uref)[:] .^ 2) + sum((par.Pσ \ p.σref) .^ 2))
    objective = (0.5 * quadform(z, P) + dot(z, q)) + r
    constraints = Constraint[H*z==h]

    # L1 Norm Reformulation for virtual control
    base = n_x * K + n_u * (K - 1) + (K - 1)
    shift = n_x * (K - 1)
    for k = 1:n_x*(p.K-1)
        push!(constraints, -z[base+shift+k] <= z[base+k])
        push!(constraints, z[base+k] <= z[base+shift+k])
    end

    # Boundary Conditions
    push!(constraints, z[1:n_x] == par.Px \ par.x0)
    push!(constraints, z[p.K*nx-n_x+1:p.K*n_x] == par.Px \ par.xT)

    # State Constraints (Keepout Zone + Max Speed)
    Xi(k) = (p.xref[1:3, k] - par.rc) / norm((p.xref[1:3, k] - par.rc))
    shift = n_x * (3 * K - 2) + n_u * (K - 1) + (K - 1)
    for k = 1:p.K
        push!(constraints, par.rho <= norm(p.xref[1:3, k] - par.rc) + dot(Xi(k), (par.Px[1:3, 1:3] * z[6*(k-1)+1:6*(k-1)+3] - p.xref[1:3, k])) + z[shift+k])
        push!(constraints, z[shift+k] >= 0)
        push!(constraints, norm(z[n_x*(k-1)+4:n_x*k]) <= par.vmax / maximum(diag(par.Px[4:6, 4:6])))
    end

    # Dilation Constraints
    shift = n_x * K + n_u * (K - 1)
    for k = 1:p.K-1
        push!(constraints, z[shift+k] >= par.σmin / par.Pσ, z[shift+k] <= par.σmax / par.Pσ)
    end

    # Control Constraints
    shift = n_x * K
    for k = 1:p.K-1
        push!(constraints, norm(z[shift+3*(k-1)+1:shift+3*(k)]) <= par.umax / maximum(diag(par.Pu)))
    end

    prob = minimize(objective, constraints)

    t = @elapsed solve!(prob, ECOS.Optimizer, silent_solver=true)

    return evaluate(z), t
end
