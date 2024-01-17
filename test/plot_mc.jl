using  JLD2, PyPlot, LinearAlgebra, UnPack, Statistics
include("../utils/set_plot.jl")

rc = [0.0; 300.0; 0.0] # Keepout zone center [m]
rho = 200.0         # Keepout zone radius [m]
umax = 0.1          # Maximum delta V [m/sec]

file = jldopen("test/data/mc_data.jld2")
@unpack traj_ecos, u_ecos, σ_ecos, iters_ecos, error_ecos, time_ecos, converged_ecos, traj_pipg, u_pipg, σ_pipg, iters_pipg, error_pipg, time_pipg, converged_pipg, x0_list = file
# @unpack traj_pipg, u_pipg, σ_pipg, iters_pipg, error_pipg, time_pipg, converged_pipg, x0_list = file
close(file)

Nmc = size(error_pipg)[1]
K = size(u_pipg)[3]
println("PIPG Percent Converged: ", 100 * sum(converged_pipg) / Nmc)

error_converged_pipg = []
error_converged_ecos = []
for i = 1 : Nmc
    if (converged_pipg[i])
        append!(error_converged_pipg, error_pipg[i])
    end
    if (converged_ecos[i])
        append!(error_converged_ecos, error_ecos[i])
    end
end
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

println("ECOS Mean Iters: ", mean(iters_ecos))
println("ECOS STD Iters: ", std(iters_ecos))

println("PIPG Mean Iters: ", mean(iters_pipg))
println("PIPG STD Iters: ", std(iters_pipg))

println("ECOS Mean Error: ", mean(error_converged_ecos))
println("ECOS STD Error: ", std(error_converged_ecos))

println("PIPG Mean Error: ", mean(error_converged_pipg))
println("PIPG STD Error: ", std(error_converged_pipg))

println("ECOS Mean Time: ", 1000 * mean(time_ecos))
println("ECOS STD Time: ", 1000 * std(time_ecos))

println("PIPG Mean Time: ", 1000 * mean(time_pipg))
println("PIPG STD Time: ", 1000 * std(time_pipg))

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
    else
        # scatter3D(x0_list[i,1], x0_list[i,2], x0_list[i,3], marker="*", color="red")
    end
end
surf(x, y, z, rstride=4, cstride=4, color="red", alpha=0.7)
scatter3D(0, 0, 0, marker="*", color="red", label="Terminal Position")
legend(loc="upper right")
axis("equal")
xlabel("Radial [m]", fontsize=15)
ylabel("Along Track [m]",  fontsize=15)
zlabel("Across Track [m]",  fontsize=15)
grid(false)

figure(dpi=200)
set_fonts()
set_fonts()
hist(iters_pipg, color="coral")
xlabel("SCP Iterations")
ylabel("Frequency")
xlim(0, 30)

figure(dpi=200)
set_fonts()
set_fonts()
hist(iters_ecos, color="mediumseagreen")
xlabel("SCP Iterations")
ylabel("Frequency")
xlim(0, 30)

figure(dpi=200)
set_fonts()
set_fonts()
hist(error_converged_pipg, color="coral")
xlabel("Single Shooting Position Error [m]")
ylabel("Frequency")
xlim(0, 1.5)

figure(dpi=200)
hist(error_converged_ecos, color="mediumseagreen")
xlabel("Single Shooting Position Error [m]")
ylabel("Frequency")
xlim(0, 1.5)

figure(dpi=200)
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