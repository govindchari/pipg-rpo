using LinearAlgebra
using PyPlot
using Printf
using IterativeSolvers

include("set_fonts.jl")

function pipg(P, q, H, h)

    # PIPG Hyperparameters
    omega = 1.0
    rho = 1.0

    # Initialize PIPG Vectors
    n = size(P)[1]
    m = size(H)[1]

    z = zeros(n)
    w = zeros(m)
    xi = zeros(n)
    eta = zeros(m)

    # Compute Stepsizes
    normP = maximum(diag(P))
    HtH = H' * H
    norm2H = maximum(eigvals(HtH))
    a = 2 / (sqrt(normP^2 + 4 * omega * norm2H) + normP)
    b = omega * a

    # Initialize Logging
    iter = 0
    z1 = []
    z2 = []
    w1 = []
    w2 = []
    println("iter     objv       |Hx-h|\n")
    println("-----------------------------\n")
    for k = 1:50       
        # Primal Update
        z = xi - a * (P * xi + q + H' * eta)

        # Dual Update
        w = eta + b * (H * (2 * z - xi) - h)

        # Extrapolation
        xi = (1 - rho) * xi + rho * z
        eta = (1 - rho) * eta + rho * w

        @printf("%3d   %10.3e  %9.2e\n",
            iter, norm(0.5 * xi' * P * xi) + dot(xi, q), norm(H * xi - h))
        iter += 1
        append!(z1, xi[1])
        append!(z2, xi[2])
        append!(w1, eta[1])
    end
    return iter, xi, eta, z1, z2, w1, w2
end

let
    P = [0 0; 0 0]
    q = [1.0; 0.0]

    # Preconditioned Problem
    H = [1.0 1.0]
    h = [1.0]

    n = size(P)[1]
    m = size(H)[1]

    # Solve with PIPG
    iters, z_pipg, w_pipg, z1, z2, w1, w2 = pipg(P, q, H, h)
    println(z_pipg)
    println(w_pipg)

    # Generate data for level curves and constraints
    f(x, y) = 0.5 .* (P[1, 1] * x .^ 2 .+ P[2, 2] * y .^ 2 .+ q[1] .* x .+ q[2] .* y)
    xx = LinRange(-10, 10, 100)
    yy = LinRange(-10, 10, 100)
    X = xx' .* ones(100)
    Y = ones(100)' .* yy
    Z = f(X, Y)
    lvls = LinRange(-20, 20, 100)
    xc1 = LinRange(-5, 5, 10)
    yc1 = (h[1] .- H[1, 1] .* xc1) ./ H[1, 2]

    # Plot
    pygui(true)
    set_fonts()
    set_fonts()
    figure(dpi=200)
    contour(X, Y, Z, levels=lvls)
    plot(z1, z2, "o-", color="Black", markersize="3", label="Iterates")
    plot(xc1, yc1, color="red", label="Equality constraint", alpha=0.5)
    # plot(xc2, yc2, color="red", alpha=0.5)
    axis("equal")
    legend()
    xlim([-10, 10])
    ylim([-10, 10])
    title("PIPG Iterates")
    savefig("doc/img/dual_infeas_pipg_iters.png")

    figure(dpi=200)
    plot(z1, color="blue")
    plot(z2, color="red")
    grid(true)
    xlabel("Iteration")
    ylabel("Value")
    title("Primal Variables vs Iteration")
    savefig("doc/img/dual_infeas_prim_iters.png")
    show()
end