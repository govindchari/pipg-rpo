using LinearAlgebra

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

x0 = [150.0; 1000.0; 200.0; 0.0; 0.0; 0.0] # Initial Condition [r v] [m ms^-1]
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
Px = Diagonal([abs.(x0[1:3]); vmax; vmax; vmax]) # State scaling matrix
Pu = umax * I(3)    # Control scaling Matrix
Pσ = σmax           # Dilation scaling factor

# Construct problem parameter struct
par = PARAMS(n, x0, xT, umax, vmax, σmin, σmax, rc, rho, Px, Pu, Pσ)

# Solve with ECOS
pecos = ptr(nx, nu, K, f, dfx, dfu, par, :impulsive, :multiple)
time_ecos, zecos = solveTraj!(pecos, :ecos, true)

# Solve with PIPG
ppipg = ptr(nx, nu, K, f, dfx, dfu, par, :impulsive, :multiple)
time_pipg, zpipg = solveTraj!(ppipg, :pipg, true)

# Print solve time stats
println("ECOS Time: ", sum(time_ecos))
println("PIPG Time: ", sum(time_pipg))
println("Performance: ", sum(time_ecos) / sum(time_pipg))
acc = (norm(zecos - zpipg) / norm(zecos)) * 100
println("PIPG within ", acc, " percent of ECOS")

if acc > 1.0
    println("####################")
    println("### NOT ACCURATE ###")
    println("####################")
end

# Plot PIPG Trajectory
Zecos= single_shot(pecos, 1000)
Zpipg = single_shot(ppipg, 1000)

figure(dpi=200)
n = 100
u = range(0, 2 * π, n)
v = range(0, π, n)

x = par.rc[1] .+ par.rho * (cos.(u) * sin.(v)')
y = par.rc[2] .+ par.rho * (sin.(u) * sin.(v)')
z = par.rc[3] .+ par.rho * (ones(n) * cos.(v)')

# plot3D(p.xref[1, :], p.xref[2, :], p.xref[3, :], "o", markersize=3, label="SCP Nodes", color="black")
plot3D(Zecos[1, :], Zecos[2, :], Zecos[3, :], label="Single Shot Trajectory", color="blue")
plot3D(Zpipg[1, :], Zpipg[2, :], Zpipg[3, :], label="Single Shot Trajectory", color="red")

surf(x, y, z, rstride=4, cstride=4, color="red", alpha=0.7)
legend(loc="upper right")
axis("equal")
xlabel("Radial [m]")
ylabel("Along Track [m]")
zlabel("Across Track [m]")
title("Rendezvous Trajectory")
grid(false)

println("ECOS Cost: ", sum(pecos.uref .^ 2))
println("PIPG Cost: ", sum(ppipg.uref .^ 2))
println("ECOS Single Shooting Position Error: ", norm(Zecos[1:3,end]))
println("PIPG Single Shooting Position Error: ", norm(Zpipg[1:3,end]))
println("ECOS Single Shooting Velocity Error: ", norm(Zecos[4:6,end]))
println("PIPG Single Shooting Velocity Error: ", norm(Zpipg[4:6,end]))

# plot_all(ppipg, Zpipg)
# plot_all(pecos, Zecos)
