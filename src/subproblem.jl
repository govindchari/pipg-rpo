using ECOS, JuMP

function solveSubproblemVectorizedJuMP!(p::ptr, P, q, H, h)
    n_x = 6
    n_u = 3
    K = p.K

    model = Model(ECOS.Optimizer)
    set_silent(model)

    @variable(model, z[1:n_x * (3 * K - 2) + n_u * (K - 1) + (2 * K - 1)])
    r = p.wtr * (sum((par.Px\p.xref)[:] .^ 2) + sum((par.Pu\p.uref)[:] .^ 2) + sum((par.Pσ \ p.σref) .^ 2))
    @objective(model, Min, 0.5 * z' * P * z + q' * z + r)
    @constraint(model, H * z .== h)

    # L1 Norm Reformulation for virtual control
    base = n_x * K + n_u * (K - 1) + (K - 1)
    shift = n_x * (K - 1)
    for k = 1:n_x*(p.K-1)
        @constraint(model, -z[base+shift+k] <= z[base+k])
        @constraint(model, z[base+k] <= z[base+shift+k])
    end

    # Boundary Conditions
    @constraint(model, z[1:n_x] == par.Px \ par.x0)
    @constraint(model, z[p.K*nx-n_x+1:p.K*n_x] == par.Px \ par.xT)

    # State Constraints (Keepout Zone + Max Speed)
    Xi(k) = (p.xref[1:3, k] - par.rc) / norm((p.xref[1:3, k] - par.rc))
    shift = n_x * (3 * K - 2) + n_u * (K - 1) + (K - 1)
    for k = 1:p.K
        nrm = norm(p.xref[1:3, k] - par.rc)
        @constraint(model, par.rho <= nrm + dot(Xi(k), (par.Px[1:3, 1:3] * z[6*(k-1)+1:6*(k-1)+3] - p.xref[1:3, k])) + z[shift+k])
        @constraint(model, z[shift+k] >= 0)
        @constraint(model, [par.vmax / maximum(diag(par.Px[4:6, 4:6])); z[n_x*(k-1)+4:n_x*k]] in SecondOrderCone())
    end

    # Dilation Constraints
    shift = n_x * K + n_u * (K - 1)
    for k = 1:p.K-1
        @constraint(model, z[shift+k] >= par.σmin / par.Pσ)
        @constraint(model, z[shift+k] <= par.σmax / par.Pσ)
    end

    # Control Constraints
    shift = n_x * K
    for k = 1:p.K-1
        @constraint(model, [par.umax / maximum(diag(par.Pu)); z[shift+3*(k-1)+1:shift+3*(k)]]  in SecondOrderCone())
    end
    set_optimizer_attribute(model, "abstol", 1e-7)
    set_optimizer_attribute(model, "reltol", 1e-7)

    optimize!(model)
    t = solve_time(model)

    return value.(z), t
end
