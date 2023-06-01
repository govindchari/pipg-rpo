using LinearAlgebra, BlockDiagonals, StaticArrays, SparseArrays, BenchmarkTools, Statistics, PyPlot

include("../ptr/utils/set_plot.jl")

function devecmul!(v,R,u,K)
    @inbounds @simd for k in 1:K
        mul!(v[k],R[k],u[k])
    end
end

function vecmul!(V,Q,U)
    mul!(V,Q,U)
end

function verifymul(v,V,m,K)
    err = 0
    @inbounds @simd for k in 1:K
        err = err + norm(v[k]-V[(k-1)*m+1:k*m])
    end
    return err
end

Nlist = [1, 2, 4, 8, 16, 32]
vec_time = []
devec_time = []
n = 6

for N in Nlist
    a = [randn(n,n) for _ in 1:N]
    b = [randn(n) for _ in 1:N]
    c = randn(n*N)

    A = [SMatrix{n,n}(a[k]) for k in 1:N]
    x = [SVector{n}(b[k]) for k in 1:N]
    y = [MVector{n}(c[(k-1)*n+1:k*n]) for k in 1:N]

    B = sparse(BlockDiagonal(a))
    d = cat(deepcopy(b)...,dims=1)

    bdevec = @benchmarkable devecmul!($y,$A,$x,$N)
    tdevec = run(bdevec)

    bvec = @benchmarkable vecmul!($c,$B,$d)
    tvec = run(bvec)
    append!(vec_time, mean(tvec.times))
    append!(devec_time, mean(tdevec.times))
    println(N)
end

pygui(true)

set_fonts()
set_fonts()

figure(dpi=200)
plot(Nlist, vec_time / 1e3, marker = "o", label="Vectorized")
plot(Nlist, devec_time / 1e3, marker = "o", label="Customized")
xscale("log")
yscale("log")
xlabel("Number of Blocks")
ylabel("Time (us)")
legend()
grid(true)
title("Vectorized vs Customized Matrix-Vector Multiplication")
savefig("img/customized.png")

figure(dpi=200)
plot(Nlist, vec_time ./ devec_time, marker = "o")
xscale("log")
xlabel("Number of Blocks")
ylabel("Speedup")
grid(true)
title("Vectorized vs Customized Matrix-Vector Multiplication")
savefig("img/customized_speedup.png")

show()