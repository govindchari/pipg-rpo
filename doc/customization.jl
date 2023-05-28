using LinearAlgebra, SparseArrays, BenchmarkTools

K = 15
nx = 6

A = rand(nx, nx)
x = rand(nx)
y = zeros(nx)
Ab = deepcopy(sparse(A))
xb = deepcopy(x)
yb = zeros(K * nx)

for k = 2:K
    global Ab = blockdiag(Ab, sparse(A))
    global xb = [xb;x]
end

function vec(y, A::SparseMatrixCSC{Float64, Int64}, x)
    mul!(y, A, x)
end

function devec(y, A::Matrix{Float64}, x, K)
    @inbounds @simd for k = 1 : K
        mul!(y, A, x)
    end
end

@btime vec($yb, $Ab, $xb)
@btime devec($y, $A, $x, $K)