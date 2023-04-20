using Printf

function log(k::Int64, p::ptr)
    @printf("%3d   %10.3e  %9.2e  %9.2e  %9.2e  %9.2e\n",
    k, p.σref, norm(reshape(p.vc, (p.nx * (p.K - 1), 1))), norm(p.Δ), p.Δσ, maximum(p.def))
end
function solveTraj!(p::ptr)
    initialize!(p)
    println("iter       σ         |ν|        |Δ|        |Δσ|     |x-xprop|")
    println("-------------------------------------------------------------")
    for k = 1:15
        FOH_discretize!(p)
        solveSubproblem!(p)
        log(k, p)
    end
end