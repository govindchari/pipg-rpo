using PyPlot

include("set_plot.jl")

function plot_all(p::ptr, Z::Matrix{Float64}, t::Vector{Float64})
    par = p.par

    pygui(true)

    set_fonts()
    set_fonts()
    Zlen = size(Z, 2)

    # Post Process Data
    unorm = zeros(p.K)
    vnorm = zeros(p.K)
    vnormss = zeros(Zlen)
    time_grid = zeros(p.K)
    for i = 1 : p.K - 1
        time_grid[i+1] = time_grid[i] + p.σref[i]
    end

    for i = 1:p.K
        unorm[i] = norm(p.uref[:, i])
        vnorm[i] = norm(p.xref[4:6, i])
    end
    for i = 1:Zlen
        vnormss[i] = norm(Z[4:6, i])
    end

    ## 3D Plot
    figure(dpi=200)
    n = 100
    u = range(0, 2 * π, n)
    v = range(0, π, n)

    x = par.rc[1] .+ par.rho * (cos.(u) * sin.(v)')
    y = par.rc[2] .+ par.rho * (sin.(u) * sin.(v)')
    z = par.rc[3] .+ par.rho * (ones(n) * cos.(v)')

    plot3D(p.xref[1, :], p.xref[2, :], p.xref[3, :], "o", markersize=3, label="SCP Nodes", color="black")
    plot3D(Z[1, :], Z[2, :], Z[3, :], label="Single Shooting Trajectory", color="blue")
    surf(x, y, z, rstride=4, cstride=4, color="red", alpha=0.7)
    scatter3D(p.xref[1, 1], p.xref[2, 1], p.xref[3, 1], marker="*", color="green", label="Initial Position")
    scatter3D(p.xref[1, end], p.xref[2, end], p.xref[3, end], marker="*", color="red", label="Terminal Position")
    legend(loc="upper right")
    axis("equal")
    xlabel("Radial [m]", fontsize=15)
    ylabel("Along Track [m]", fontsize=15)
    zlabel("Across Track [m]", fontsize=15)
    grid(false)

    # Control Norm
    figure(dpi=200)
    plot(time_grid[1:end-1], unorm[1:end-1], "o", color="black", markersize=5, label=L"$\Delta v$")
    axhline(par.umax, color="red", label=L"$\Delta v_{max}$")
    axvline(time_grid[end], linestyle="dashed", color="gray", label="Time of Flight")
    xlim(0, 1.1 * time_grid[end])
    grid(true)
    legend()
    xlabel("Time [s]")
    ylabel(L"Thruster $\Delta v$ [m/s]")

    # Speed
    figure(dpi=200)
    plot(time_grid, vnorm, "o", color="black", markersize=5, label="SCP Nodes")
    # plot(((0:Zlen-1) * (p.K-1) / Zlen), vnormss, label=L"\|v\|_{ss}")
    plot(t, vnormss, color="blue")
    axhline(par.vmax, color="red", label=L"$v_{max}$")
    grid(true)
    legend()
    xlabel("Time [s]")
    ylabel("Speed [m/s]")
    plt.show()

end