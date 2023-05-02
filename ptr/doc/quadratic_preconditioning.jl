using PyPlot
using LinearAlgebra

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

function grad_descent(Q, x0)
    ix = [x0[1]]
    iy = [x0[2]]
    f(P, z) = 0.5 * dot(z, P * z)
    gf(P, z) = P * z
    eps = 1e-6
    x = copy(x0)
    iter = 0
    while norm(x) > eps
        gfx = gf(Q, x)
        g = dot(gfx, gfx) / dot(gfx, Q * gfx)
        x -= g * gfx
        iter += 1
        append!(ix, x[1])
        append!(iy, x[2])
    end
    return iter, ix, iy
end

let
    k = 10
    Q = [1 0; 0 k]
    iter, ix, iy = grad_descent(Q, [11.0; 1.0])

    f(x, y) = 0.5 .* (x.^2 .+ k * y.^2)
    xx = LinRange(-15,15,100)
    yy = LinRange(-10,10,100)
    X = xx' .* ones(100)
    Y = ones(100)' .* yy
    Z = f(X, Y)

    println(iter)
    pygui(true)
    set_fonts()
    set_fonts()
    figure(dpi=200)
    lvls = LinRange(0,500,10)
    plot(ix, iy, "o-", color = "blue", markersize = 4, markerfacecolor = "red")
    title(string(iter) * " Gradient Descent Iterates")
    contour(X, Y, Z, levels=lvls)
    axis("equal")
    xlim([-11, 11])
    # savefig("img/well_conditioned.png")

    show()
end