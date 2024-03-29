using Printf

function log(k::Int64, p::ptr, pipg_iter::Int64)
    @printf("%3d   %10.3e  %9.2e  %9.2e  %9.2e  %9.2e    %3d\n",
        k, sum(p.σref), norm(reshape(p.vc, (p.nx * (p.K - 1), 1)), 1), sum(p.vb), p.Δ, p.Δσ, pipg_iter)
end
function solveTraj!(p::ptr, slvr::Symbol, verbose::Bool)
    initialize!(p)
    if (verbose)
        println("iter       tf        |νc|       |νb|        |Δ|       |Δσ|   PIPG Iters")
        println("------------------------------------------------------------------------")
    end
    opts = PIPG_OPTS()
    c = CACHE(p)
    time = []
    pipg_iter = 0
    z = zeros(p.nx * (3 * p.K - 2) + p.nu * (p.K - 1) + (2 * p.K - 1))
    for k = 1:p.max_iter
        discretize!(p)
        P, q, H, h = vectorize(p)
        if slvr == :ecos
            z, t = solveSubproblemVectorizedJuMP!(p, P, q, H, h)
            package_solution(p, z, zeros(p.nx * (p.K - 1)))
        elseif slvr == :pipg
            z, w, pipg_iter, t = pipg_vec_solve!(p, opts, c, P, q, H, h)
            package_solution(p, z, w)
        end
        append!(time, t)
        if verbose
            log(k, p, pipg_iter)
        end
        p.converged = (norm(reshape(p.vc, (p.nx * (p.K - 1), 1)), 1) <= p.vc_tol) && (p.Δ <= p.tr_tol) && (sum(p.vb) <= p.vb_tol)
        p.iters = k
        if (p.converged)
            break
        end
    end
    return time, z
end