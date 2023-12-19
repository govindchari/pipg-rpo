using LinearAlgebra, JLD2, Random


include("../utils/structs.jl")
include("../utils/discretize.jl")
include("../utils/plotting.jl")
include("../utils/propagation.jl")

include("../src/initialize.jl")
include("../src/dynamics.jl")
include("../src/solver.jl")
include("../src/subproblem.jl")
include("../src/pipg.jl")

K = 15              # Number of nodes
n = 0.00113         # Mean Motion
Nsim = 500          # Number of simulation nodes
Nmc = 1

x0_nom = [150.0; 1000.0; 200.0; 0.0; 0.0; 0.0] # Initial Condition [r v] [m ms^-1]
xT = zeros(6)       # Terminal condition [r v] [m ms^-1]
σmax = 300.0        # Dilation upper bound [s]
σmin = 100.0        # Dilation lower bound [s]
umax = 0.1          # Max dv [m s^-1]
vmax = 0.5          # Max speed [m s^-1]
rc = [0.0; 300.0; 0.0] # Keepout zone center [m]
rho = 200.0         # Keepout zone radius [m]
nx = 6              # Number of states
nu = 3              # Number of controls

# Scaling Matrices
Px = Diagonal([abs.(x0_nom[1:3]); vmax; vmax; vmax]) # State scaling matrix
Pu = umax * I(3)    # Control scaling Matrix
Pσ = σmax           # Dilation scaling factor

traj_ecos = zeros(Nmc, nx, 6986)
traj_pipg = zeros(Nmc, nx, 6986)

u_ecos = zeros(Nmc, nu, K)
u_pipg = zeros(Nmc, nu, K)

σ_ecos = zeros(Nmc, K-1)
σ_pipg = zeros(Nmc, K-1)


iters_ecos = zeros(Nmc)
iters_pipg = zeros(Nmc)

error_ecos = zeros(Nmc)
error_pipg = zeros(Nmc)

time_ecos = zeros(Nmc)
time_pipg = zeros(Nmc)

converged_ecos = zeros(Bool, Nmc)
converged_pipg = zeros(Bool, Nmc)

x0_list = zeros(Nmc, nx)

rng = MersenneTwister(1234);

for i = 1 : Nmc
    # Construct problem parameter struct
    x0 = x0_nom + [25 * randn(rng, 3); 0 * randn(rng, 3)]
    x0_list[i,:] = x0
    par = PARAMS(n, x0, xT, umax, vmax, σmin, σmax, rc, rho, Px, Pu, Pσ)

    # Solve with ECOS
    pecos = ptr(nx, nu, K, f, dfx, dfu, par, :impulsive, :multiple)
    t_ecos, zecos = solveTraj!(pecos, :ecos, true)
    Zecos = single_shot(pecos, Nsim)
    traj_ecos[i, :, :] = Zecos
    u_ecos[i, :, :] = pecos.uref
    σ_ecos[i,:] = pecos.σref
    iters_ecos[i] = pecos.iters
    error_ecos[i] = norm(Zecos[1:3, end])
    time_ecos[i] = sum(t_ecos)
    converged_ecos[i] = pecos.converged

    # Solve with PIPG
    ppipg = ptr(nx, nu, K, f, dfx, dfu, par, :impulsive, :multiple)
    t_pipg, zpipg = solveTraj!(ppipg, :pipg, true)
    Zpipg = single_shot(ppipg, Nsim)
    traj_pipg[i, :, :] = Zpipg
    u_pipg[i, :, :] = ppipg.uref
    σ_pipg[i,:] = ppipg.σref
    iters_pipg[i] = ppipg.iters
    error_pipg[i] = norm(Zpipg[1:3, end])
    time_pipg[i] = sum(t_pipg)
    converged_pipg[i] = ppipg.converged
end
jldsave("test/data/mc_data.jld2"; traj_ecos, u_ecos, σ_ecos, iters_ecos, error_ecos, time_ecos, converged_ecos, traj_pipg, u_pipg, σ_pipg, iters_pipg, error_pipg, time_pipg, converged_pipg, x0_list)

# # Print solve time stats
# println("ECOS Time: ", sum(time_ecos))
# println("PIPG Time: ", sum(time_pipg))
# println("Performance: ", sum(time_ecos) / sum(time_pipg))
# acc = (norm(zecos - zpipg) / norm(zecos)) * 100
# println("PIPG within ", acc, " percent of ECOS")

# if acc > 1.0
#     println("####################")
#     println("### NOT ACCURATE ###")
#     println("####################")
# end

println("PIPG Percent Converged: ", 100 * sum(converged_pipg) / Nmc)
println("ECOS Percent Converged: ", 100 * sum(converged_ecos) / Nmc)