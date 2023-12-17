using LinearAlgebra, JLD2

include("../utils/structs.jl")
include("../utils/discretize.jl")
include("../utils/plotting.jl")

include("../src/initialize.jl")
include("../src/dynamics.jl")
include("../src/solver.jl")
include("../src/subproblem.jl")
include("../src/pipg.jl")

K = 15              # Number of nodes
n = 0.00113         # Mean Motion

x0 = [200.0; 1000.0; 200.0; 0.0; 0.0; 0.0] # Initial Condition [r v] [m ms^-1]
xT = zeros(6)       # Terminal condition [r v] [m ms^-1]
σmax = 300.0        # Dilation upper bound [s]
σmin = 100.0        # Dilation lower bound [s]
umax = 0.1          # Max dv [m s^-1]
vmax = 0.5          # Max speed [m s^-1]
rc = [0.0; 300.0; 0.0] # Keepout zone center [m]
rho = 250.0         # Keepout zone radius [m]
nx = 6              # Number of states
nu = 3              # Number of controls

# Scaling Matrices
Px = Diagonal([abs.(x0[1:3]); vmax; vmax; vmax]) # State scaling matrix
Pu = umax * I(3)    # Control scaling Matrix
Pσ = σmax           # Dilation scaling factor

# Construct problem parameter struct
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
save_object("data/ecos_times.jld2", ecos)
save_object("data/pipg_times.jld2", pipg)