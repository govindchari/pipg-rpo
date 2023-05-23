using LinearAlgebra, BenchmarkTools

include("../utils/structs.jl")
include("../utils/discretize.jl")
include("../utils/plotting.jl")

include("../src/initialize.jl")
include("../src/dynamics.jl")
include("../src/solver.jl")
include("../src/subproblem.jl")
include("../src/pipg.jl")

K = 15
n = 0.00113
x0 = [200.0; 1000.0; 200.0; 0.0; 0.0; 0.0]
xT = zeros(6)
σmax = 300.0
σmin = 100.0
umax = 0.1
vmax = 0.5
rc = [0.0; 300.0; 0.0]
rho = 250.0
nx = 6
nu = 3

# Scaling Matrices
Pu = umax * I(3)
Px = Diagonal([abs.(x0[1:3]); vmax; vmax; vmax])
Pσ = σmax

par = PARAMS(n, x0, xT, umax, vmax, σmin, σmax, rc, rho, Px, Pu, Pσ)

# Solve with ECOS
pecos = ptr(nx, nu, K, f, dfx, dfu, par, :impulsive, :multiple)
time_ecos, zecos = solveTraj!(pecos, :ecos, true)

# Solve with PIPG
ppipg = ptr(nx, nu, K, f, dfx, dfu, par, :impulsive, :multiple)
time_pipg, zpipg = solveTraj!(ppipg, :pipg, true)

println("ECOS Time: ", sum(time_ecos))
println("PIPG Time: ", sum(time_pipg))
println("Performance: ", sum(time_pipg) / sum(time_ecos))
println("PIPG within ", (norm(zecos - zpipg) / norm(zecos)) * 100, " percent of ECOS")

# plot_all(ppipg)

