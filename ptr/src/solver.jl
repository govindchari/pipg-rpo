using Printf

function log(k::Int64, p::ptr)
    @printf("%3d   %10.3e  %9.2e  %9.2e  %9.2e  %9.2e\n",
        k, p.σref, norm(reshape(p.vc, (p.nx * (p.K - 1), 1)), 1), sum(p.vb), norm(p.Δ), abs(p.Δσ))
end
function solveTraj!(p::ptr)
    initialize!(p)
    println("iter       σ         |νc|       |νb|        |Δ|        |Δσ|    ")
    println("--------------------------------------------------------------")
    for k = 1:15
        FOH_discretize!(p)
        solveSubproblem!(p)
        log(k, p)
    end
end