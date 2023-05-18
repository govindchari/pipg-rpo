using Printf

function log(k::Int64, p::ptr)
    @printf("%3d   %10.3e  %9.2e  %9.2e  %9.2e  %9.2e\n",
        k, sum(p.σref), norm(reshape(p.vc, (p.nx * (p.K - 1), 1)), 1), sum(p.vb), p.Δ, p.Δσ)
end
function solveTraj!(p::ptr)
    initialize!(p)
    println("iter       tf        |νc|       |νb|        |Δ|       |Δσ|    ")
    println("--------------------------------------------------------------")
    z = zeros(6 * (3 * p.K - 2) + 3 * (p.K - 1) + (p.K - 1))
    for k = 1:20
        discretize!(p)
        P, q, H, h = vectorize(p)
        # solveSubproblemVectorized!(p, P, q, H, h)
        solveSubproblem!(p)
        log(k, p)
    end
    return z
end