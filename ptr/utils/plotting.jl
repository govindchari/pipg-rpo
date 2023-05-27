using PyPlot

include("set_plot.jl")

function plot_all(p::ptr)
    par = p.par

    pygui(true)

    set_fonts()
    set_fonts()

    # Post Process Data
    unorm = zeros(p.K)
    vnorm = zeros(p.K)
    for i = 1 : p.K
        unorm[i] = norm(p.uref[:,i])
        vnorm[i] = norm(p.xref[4:6,i])
    end

    ## 3D Plot
    figure(dpi=200)
    n = 100
    u = range(0,2*π,n);
    v = range(0,π,n);
    
    x = par.rc[1] .+ par.rho * (cos.(u) * sin.(v)');
    y = par.rc[2] .+ par.rho * (sin.(u) * sin.(v)');
    z = par.rc[3] .+ par.rho * (ones(n) * cos.(v)');
    
    plot3D(p.xref[1, :], p.xref[2, :], p.xref[3, :], "o-", markersize = 3, label="Trajectory", color="blue")
    surf(x,y,z, rstride=4, cstride=4, color="red", alpha=0.7)
    scatter3D(p.xref[1, 1], p.xref[2, 1], p.xref[3, 1], marker="*", color="green", label="Initial Position")
    scatter3D(p.xref[1, end], p.xref[2, end], p.xref[3, end], marker="*", color="red", label="Terminal Position")
    legend()
    axis("equal")
    xlabel("Radial [m]")
    ylabel("Along Track [m]")
    zlabel("Across Track [m]")
    title("Rendezvous Trajectory")
    grid(true)

    # Control Norm
    figure(dpi=200)
    plot(unorm[1:end-1], "o-", markersize = 5, label=L"$\|u\|$")
    axhline(par.umax, color="red", label=L"$u_{max}$")
    grid(true)
    legend()
    title("Control Norm over Time")
    xlabel("Time Step")
    ylabel("Control Norm")

    # Speed
    figure(dpi=200)
    plot(vnorm , "o-", markersize = 5, label=L"\|v\|")
    axhline(par.vmax, color="red", label=L"$v_{max}$")
    grid(true)
    legend()
    title("Speed over Time")
    xlabel("Time Step")
    ylabel("Speed")

    # Control Input
    figure(dpi=200)
    plot(p.uref[1,1:end-1]' , "o-", markersize = 5, label=L"$u_x$")
    plot(p.uref[2,1:end-1]' , "o-", markersize = 5, label=L"$u_y$")
    plot(p.uref[3,1:end-1]' , "o-", markersize = 5, label=L"$u_z$")
    axhline(par.umax, color="red", label=L"$u_{max}$")
    axhline(-par.umax, color="red")
    grid(true)
    legend()
    title("Control over Time")
    xlabel("Time Step")
    ylabel("Control")

    plt.show()

end