using LinearAlgebra
using PyPlot

function set_fonts()::Nothing
    # Set the figure fonts.
    fig_smaller_sz = 13
    fig_small_sz = 14
    fig_med_sz = 15
    fig_big_sz = 17
    plt.rc("text", usetex=true)
    plt.rc("font", size=fig_small_sz, family="serif")
    plt.rc("axes", titlesize=fig_small_sz)
    plt.rc("axes", labelsize=fig_small_sz)
    plt.rc("xtick", labelsize=fig_smaller_sz)
    plt.rc("ytick", labelsize=fig_smaller_sz)
    plt.rc("legend", fontsize=fig_smaller_sz)
    plt.rc("figure", titlesize=fig_big_sz)
    plt.rc("figure", dpi=150) 
    plt.rc("figure", figsize = [7, 5])
    plt.rc("axes", xmargin=0)
    plt.rc("animation", html="html5")
    return nothing
end

function plot_sphere()

    
    plt.show()
end

function plot_all(p::ptr)
    par = p.par

    pygui(true)

    set_fonts()
    set_fonts()

    ## 3D Plot
    figure(dpi=200)
    n = 100
    u = range(0,2*π,n);
    v = range(0,π,n);
    
    x = par.rc[1] .+ par.rho * (cos.(u) * sin.(v)');
    y = par.rc[2] .+ par.rho * (sin.(u) * sin.(v)');
    z = par.rc[3] .+ par.rho * (ones(n) * cos.(v)');
    
    plot3D(p.xref[1, :], p.xref[2, :], p.xref[3, :], "o-", markersize = 3, label="Trajectory", color="blue")
    surf(x,y,z, rstride=4, cstride=4, label="Keepout Zone", color="red", alpha=0.7)

    plot3D(p.xref[1, 1], p.xref[2, 1], p.xref[3, 1], marker="*", markeredgecolor="green", markerfacecolor="green")
    plot3D(p.xref[1, end], p.xref[2, end], p.xref[3, end], marker="*", markeredgecolor="red", markerfacecolor="red")

    # legend()
    plt.axis("equal")
    xlabel("Radial [m]")
    ylabel("Along Track [m]")
    zlabel("Across Track [m]")

    title("Rendezvous Trajectory")
    grid(true)

    ## 2D Rendezvous
    # figure(dpi=200)
    # theta = range( 0 , stop=2 * pi , length=150 )
    # a = rc[1] .+ rho * cos.( theta )
    # b = rc[2] .+ rho * sin.( theta )

    # scatter(p.xref[2,:], p.xref[1,:], label="Trajectory")
    # plot(b, a, color="red", label="Keepout Zone")
    # legend()
    # plt.axis("equal")
    # title("Rendezvous Trajectory")
    # grid(true)

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