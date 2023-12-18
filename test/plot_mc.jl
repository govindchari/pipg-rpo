using  JLD2, PyPlot, LinearAlgebra, UnPack
include("../utils/set_plot.jl")

rc = [0.0; 300.0; 0.0] # Keepout zone center [m]
rho = 250.0         # Keepout zone radius [m]
umax = 0.1          # Maximum delta V [m/sec]

file = jldopen("test/data/mc_data.jld2")
@unpack traj_pipg, u_pipg, σ_pipg, iters_pipg, error_pipg, time_pipg, converged_pipg, x0_list = file
close(file)

Nmc = size(error_pipg)[1]
K = size(u_pipg)[3]
println("PIPG Percent Converged: ", 100 * sum(converged_pipg) / Nmc)

set_fonts()
set_fonts()
figure(dpi=200)
n = 100
u = range(0, 2 * π, n)
v = range(0, π, n)

x = rc[1] .+ rho * (cos.(u) * sin.(v)')
y = rc[2] .+ rho * (sin.(u) * sin.(v)')
z = rc[3] .+ rho * (ones(n) * cos.(v)')
for i = 1 : Nmc
    if (converged_pipg[i])
        plot3D(traj_pipg[i, 1, :], traj_pipg[i, 2, :], traj_pipg[i, 3, :])
    end
end
surf(x, y, z, rstride=4, cstride=4, color="red", alpha=0.7)
scatter3D(0, 0, 0, marker="*", color="red", label="Terminal Position")
legend(loc="upper right")
axis("equal")
xlabel("Radial [m]")
ylabel("Along Track [m]")
zlabel("Across Track [m]")
title("Rendezvous Trajectory")
grid(false)

figure(dpi=200)
set_fonts()
set_fonts()
hist(iters_pipg, color="mediumseagreen")
xlabel("SCP Iterations")
ylabel("Frequency")
grid()

error_converged = []
for i = 1 : Nmc
    if (converged_pipg[i])
        append!(error_converged, error_pipg[i])
    end
end
figure(dpi=200)
set_fonts()
set_fonts()
hist(error_converged, color="mediumseagreen")
xlabel("Single Shooting Error")
ylabel("Frequency")
grid()

figure(dpi=200)
unorm = zeros(Nmc, K)
time_grid = zeros(Nmc, K)
for i = 1 : Nmc
    for j = 1 : K
        unorm[i, j] = norm(u_pipg[i,:,j])
    end
end
for i = 1 : Nmc
    for j = 1 : K-1
        time_grid[i,j+1] = time_grid[i, j] + σ_pipg[i, j]
    end
end

for i = 1 : Nmc
    if (converged_pipg[i])
        plot(time_grid[i,:], unorm[i,:], color="gray", alpha=0.3)
    end
end
axhline(umax, color="red", label=L"$\Delta v_{max}$")
legend()
xlabel("Time [secs]")
ylabel("Delta-V [m/sec]")
grid()