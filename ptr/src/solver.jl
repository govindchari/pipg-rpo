using Printf

function log(k::Int64, p::ptr)
    @printf("%3d   %10.3e  %9.2e  %9.2e  %9.2e  %9.2e\n",
        k, sum(p.σref), norm(reshape(p.vc, (p.nx * (p.K - 1), 1)), 1), sum(p.vb), p.Δ, p.Δσ)
end
function solveTraj!(p::ptr)
    initialize!(p)
    println("iter       tf        |νc|       |νb|        |Δ|       |Δσ|    ")
    println("--------------------------------------------------------------")
    opts = PIPG_OPTS()
    tecos_l = []
    tpipg_l = []
    for k = 1:15
        discretize!(p)
        P, q, H, h = vectorize(p)
        zopt, tecos = solveSubproblemVectorized!(p, P, q, H, h)
        tpipg = @elapsed xi = pipg_vec_solve!(p, opts, P, q, H, h, zopt)
        package_solution(p, xi)
        append!(tecos_l, tecos)
        append!(tpipg_l, tpipg)
        log(k, p)
    end
    return tecos_l, tpipg_l
end