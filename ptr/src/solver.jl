using Printf

function log(k::Int64, p::ptr, pipg_iter::Int64)
    @printf("%3d   %10.3e  %9.2e  %9.2e  %9.2e  %9.2e    %3d\n",
        k, sum(p.σref), norm(reshape(p.vc, (p.nx * (p.K - 1), 1)), 1), sum(p.vb), p.Δ, p.Δσ, pipg_iter)
end
function solveTraj!(p::ptr, slvr)
    initialize!(p)
    println("iter       tf        |νc|       |νb|        |Δ|       |Δσ|   PIPG Iters")
    println("------------------------------------------------------------------------")
    opts = PIPG_OPTS()
    time = []
    pipg_iter = 0
    z = zeros(p.nx * (3 * p.K - 2) + p.nu * (p.K - 1) + (2 * p.K - 1))
    for k = 1:15
        discretize!(p)
        P, q, H, h = vectorize(p)
        if slvr == :ecos
            z, t = solveSubproblemVectorized!(p, P, q, H, h)
            package_solution(p, z)
        elseif slvr == :pipg
            t = @elapsed z, pipg_iter = pipg_vec_solve!(p, opts, P, q, H, h)
            package_solution(p, z)    
        end
        append!(time, t)
        log(k, p, pipg_iter)
    end
    return time, z
end