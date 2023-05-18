using Printf

function log(k::Int64, p::ptr)
    @printf("%3d   %10.3e  %9.2e  %9.2e  %9.2e  %9.2e\n",
        k, sum(p.σref), norm(reshape(p.vc, (p.nx * (p.K - 1), 1)), 1), sum(p.vb), p.Δ, p.Δσ)
end
function solveTraj!(p::ptr)
    initialize!(p)
    println("iter       tf        |νc|       |νb|        |Δ|       |Δσ|    ")
    println("--------------------------------------------------------------")
    for k = 1:20
        discretize!(p)
        P, q, H, h = vectorize(p)
        z = solveSubproblemVectorized!(p, P, q, H, h)
        x, u, s = solveSubproblem!(p, H, h)
        # println(norm(z - [x;u[1:end-3];s]))
        # println(norm(H*[(par.Px \ p.xref)[:];(par.Pu \ p.uref)[:][1:end-3];((par.Pσ * I(p.K - 1))) \ p.σref[:]] - h))
        # println(norm(u[end-2:end]))
        log(k, p)
    end
end