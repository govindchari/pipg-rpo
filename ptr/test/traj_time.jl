using LinearAlgebra, JLD2

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

numruns = 200
pipg = zeros(numruns)
ecos = zeros(numruns)
for i = 1:numruns
    pecos = ptr(nx, nu, K, f, dfx, dfu, par, :impulsive, :multiple)
    time_ecos, zecos = solveTraj!(pecos, :ecos, false)
    ppipg = ptr(nx, nu, K, f, dfx, dfu, par, :impulsive, :multiple)
    time_pipg, zpipg = solveTraj!(ppipg, :pipg, false)
    pipg[i] = sum(time_pipg)
    ecos[i] = sum(time_ecos)
    println(i)
end
println("ECOS: ", ecos)
println("PIPG: ", pipg)
save_object("data/ecos_times.jld2", ecos)
save_object("data/pipg_times.jld2", pipg)