using LinearAlgebra
using PyPlot
using Printf
using IterativeSolvers

include("set_fonts.jl")

function proj_D(z, rc, rho)
    if (norm(z - rc) > rho)
        zproj = (rho / norm(z - rc)) * (z - rc) + rc
    else
        zproj = z
    end
    return zproj
end

function pipg(P, q, H, h, rc, r)

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
    # while ((norm(zopt - xi) / norm(zopt) > 1e-2 || norm(wopt - eta) / norm(wopt) > 1e-2) && iter <= 1e7)
    for i = 1:20
        # Primal Update
        z = xi - a * (P * xi + q + H' * eta)
        # append!(z1, z[1])
        # append!(z2, z[2])
        z = proj_D(z, rc, r)
        append!(z1, z[1])
        append!(z2, z[2])

        # Dual Update
        w = eta + b * (H * (2 * z - xi) - h)

        # Extrapolation
        xi = (1 - rho) * xi + rho * z
        eta = (1 - rho) * eta + rho * w

        @printf("%3d   %10.3e  %9.2e\n",
            iter, norm(0.5 * xi' * P * xi), norm(H * xi - h))
        iter += 1
        append!(z1, z[1])
        append!(z2, z[2])
        append!(w1, w[1])
        # append!(w2, eta[2])
    end
    println(a)
    return iter, z, w, z1, z2, w1, w2
end

let
    P = [1 0; 0 1]
    q = [0.0; 0.0]

    # Preconditioned Problem
    H = [1.0 1.0] * sqrt(2) / 2
    h = [1.0] * sqrt(2) / 2

    n = size(P)[1]
    m = size(H)[1]

    rc = [1.0; 0.0]
    rho = 0.5

    # Get exact solution
    KKT = [P H'; H zeros(m, m)]
    rhs = [-q; h]
    sol = KKT \ rhs
    z = sol[1:n]
    w = sol[n+1:end]

    # Solve with PIPG
    iters, z_pipg, w_pipg, z1, z2, w1, w2 = pipg(P, q, H, h, rc, rho)
    println(z_pipg)
    println(w_pipg)
    println(z)
    println(w)

    # Generate data for level curves and constraints
    f(x, y) = 0.5 .* (P[1, 1] * x .^ 2 .+ P[2, 2] * y .^ 2 .+ q[1] .* x .+ q[2] .* y)
    xx = LinRange(-2, 2, 100)
    yy = LinRange(-2, 2, 100)
    X = xx' .* ones(100)
    Y = ones(100)' .* yy
    Z = f(X, Y)
    lvls = LinRange(0, 1, 10)
    xc1 = LinRange(-5, 5, 10)
    yc1 = (h[1] .- H[1, 1] .* xc1) ./ H[1, 2]
    # xc2 = LinRange(-5, 5, 10)
    # yc2 = (h[2] .- H[2, 1] .* xc2) ./ H[2, 2]

    # Plot
    pygui(true)
    set_fonts()
    set_fonts()
    figure(dpi=200)
    D = plt.Circle((rc[1], rc[2]), rho, color="b", alpha=0.5, label=L"$\mathcal{D}$")
    plot(z1, z2, "o-", color="Black", markersize="3", label="Iterates")
    contour(X, Y, Z, levels=lvls)
    plt.gca().add_patch(D)
    plot(xc1, yc1, color="red", label="Equality constraint", alpha=0.5)
    axis("equal")
    legend()
    xlim([-1.5, 1.5])
    ylim([-1.5, 1.5])
    title(string(iters) * " PIPG Iterates")
    savefig("doc/img/actual_pipg_iterates.png")

    figure(dpi=200)
    plot(w1, color="blue")
    plot(w2, color="red")
    grid(true)
    xlabel("Iteration")
    ylabel("Value")
    title("Dual Variables vs Iteration")
    show()
end