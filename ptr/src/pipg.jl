using SparseArrays, IterativeSolvers

struct PIPG_OPTS
    omega::Float64
    rho::Float64
    max_iters::Int64
    check_iter::Int64
    function PIPG_OPTS()
        omega = 200.0
        rho = 1.8
        max_iters = 500
        check_iter = 1
        new(omega, rho, max_iters, check_iter)
    end
end
function vectorize(p::ptr)
    par = p.par
    nx = 6
    nu = 3
    nc = nx * (p.K - 1)   # Number of equality constraints in vectorized problem

    # Construct P
    # Pvec = [2.0 * p.wtr * ones(nx * p.K); 2.0 * (1 + p.wtr) * ones(nu * (p.K - 1)); 2.0 * p.wtr * ones(p.K - 1); zeros(nx * (p.K - 1)); zeros(nx * (p.K - 1)); zeros(p.K)]
    Pvec = [2.0 * p.wtr * ones(nx * p.K); 2.0 * (1 + p.wtr) * ones(nu * (p.K - 1)); 2.0 * p.wtr * ones(p.K - 1); zeros(nx * (p.K - 1)); zeros(nx * (p.K - 1))]
    P = Diagonal(Pvec)

    # Construct q
    # q = [-2.0 * p.wtr * (par.Px\p.xref)[:]; -2.0 * p.wtr * (par.Pu\p.uref)[:][1:end-nu]; -2.0 * p.wtr * (p.σref./par.Pσ)[:]; zeros(nx * (p.K - 1)); p.wvc * ones(nx * (p.K - 1)); p.wvb * ones(p.K)]
    q = [-2.0 * p.wtr * (par.Px\p.xref)[:]; -2.0 * p.wtr * (par.Pu\p.uref)[:][1:end-nu]; -2.0 * p.wtr * (p.σref./par.Pσ)[:]; zeros(nx * (p.K - 1)); p.wvc * ones(nx * (p.K - 1))]

    # Scaled Dynamics Matrices
    A(k) = sparse(par.Px \ p.A[:, :, k] * par.Px)
    B(k) = sparse(par.Px \ p.A[:, 4:6, k] * par.Pu)
    S(k) = sparse(par.Px \ reshape(p.S[:, k], 6, 1) * par.Pσ)
    z(k) = par.Px \ p.z[:, k]

    # Construct H
    Ab = A(1)
    Hu = B(1)
    Hs = S(1)
    for k = 2:p.K-1
        Ab = blockdiag(Ab, A(k))
        Hu = blockdiag(Hu, B(k))
        Hs = blockdiag(Hs, S(k))
    end
    zrs = zeros(nc, 6)
    Hx = sparse([Ab zrs] - [zrs 1.0 * I(nc)])
    Hvc = 1.0 * I(nc)
    HG = sparse(zeros(nc, nc))
    Hvb = sparse(zeros(nc, p.K))
    # H = sparse([Hx Hu Hs Hvc HG Hvb])
    H = sparse([Hx Hu Hs Hvc HG])

    # Construct h
    h = -(par.Px\p.z)[:]

    return P, q, H, h
end
function proj_ball!(x::SubArray{Float64,1,Vector{Float64},Tuple{UnitRange{Int64}},true}, r::Float64)
    if (norm(x) > r)
        x .= (r / norm(x)) .* x
    end
end
function proj_box!(x::SubArray{Float64,1,Vector{Float64},Tuple{UnitRange{Int64}},true}, l::Float64, u::Float64)
    x .= min.(max.(x, l), u)
end
function proj_inter_halfspaces!(c, u1::Vector{Float64}, u2::Vector{Float64}, eta1::Float64, eta2::Float64)
    eps = 1e-9
    a1 = dot(c, u1)
    a2 = dot(c, u2)
    b = dot(u1, u2)
    if (min(abs(norm(u1) - 1), abs(norm(u2) - 1)) >= eps)
        error("u1 and u2 must be unit vectors")
    end
    if abs(b - 1) <= eps
        eta = min(eta1, eta2)
        if a1 <= eta
            c .= c
        else
            c .= c + (eta - a1) * u1
        end
    elseif abs(b + 1) <= eps
        if eta2 <= -eta1
            error("Empty Intersection of Halfspaces")
        else
            if a1 < -eta2
                c .= c - (a1 + eta2) * u1
            elseif (-eta2 <= a1 && a1 <= eta1)
                c .= c
            else
                c .= c - (a1 - eta1) * u1
            end
        end
    else
        nu1 = 0.0
        nu2 = 0.0
        if a1 <= eta1 && a2 <= eta2
            nu1 = 0.0
            nu2 = 0.0
        elseif a1 - eta1 > b * (a2 - eta2) && a2 - eta2 > b * (a1 - eta1)
            nu1 = (a1 - eta1 - b * (a2 - eta2)) / (1 - b^2)
            nu2 = (a2 - eta2 - b * (a1 - eta1)) / (1 - b^2)
        elseif a2 > eta2 && a1 - eta1 <= b * (a2 - eta2)
            nu1 = 0
            nu2 = a2 - eta2
        else
            nu1 = a1 - eta1
            nu2 = 0
        end
        c .= c - nu1 * u1 - nu2 * u2
    end
    return c
end
function project_D!(p::ptr, z::Vector{Float64})
    for k = 1:p.K
    #     idx_r = p.nx*(k-1)+1:p.nx*(k-1)+3
        idx_v = p.nx*(k-1)+4:p.nx*k
        idx_u = (p.nx*K)+p.nu*(k-1)+1:(p.nx*K)+p.nu*k
    #     # idx_σ = n_x * K + n_u * (K - 1) + k
    #     idx_vc = (p.nx*K)+p.nu*(k-1)+1:(p.nx*K)+p.nu*k
    #     idx_vb = p.nx * (3 * p.K - 2) + p.nu * (p.K - 1) + (p.K - 1) + k

        proj_ball!((@view z[idx_v]), par.vmax / maximum(diag(par.Px[4:6, 4:6])))
        proj_ball!((@view z[idx_u]), par.umax / maximum(diag(par.Pu)))
    end

    # L1 Norm Reformulation for virtual control
    base = p.nx * p.K + p.nu * (p.K - 1) + (p.K - 1)
    shift = p.nx * (p.K - 1)
    for k = 1:p.nx*(p.K-1)
        proj_inter_halfspaces!((@view z[[base + k, base + shift + k]]), [-1.0; -1.0] / sqrt(2), [1.0; -1.0] / sqrt(2), 0.0, 0.0)
    end

    # Dilation Constraints
    idx_σ = p.nx*p.K+p.nu*(p.K-1)+1:p.nx*p.K+p.nu*(p.K-1)+p.K-1
    proj_box!((@view z[idx_σ]), par.σmin / par.Pσ, par.σmax / par.Pσ)

    # Boundary Conditions
    z[1:p.nx] = par.Px \ par.x0
    z[p.K*p.nx-p.nx+1:p.K*p.nx] = par.Px \ par.xT
end
function compute_stepsizes(p::ptr, opts::PIPG_OPTS, H)
    normP = 2.0 * (1.0 + p.wtr)
    HtH = H' * H
    norm2H = real(powm(HtH)[1])
    alpha = 2 / (sqrt(normP^2 + 4 * opts.omega * norm2H) + normP)
    beta = opts.omega * alpha
    return alpha, beta
end
function package_solution(p::ptr, xi::Vector{Float64})
    # Package z back into ptr struct
    x = xi[1:p.nx*p.K]
    u = [xi[p.nx*p.K+1:p.nx*p.K+p.nu*(p.K-1)]; 0; 0; 0]
    σ = xi[p.nx*p.K+p.nu*(p.K-1)+1:p.nx*p.K+p.nu*(p.K-1)+p.K-1]
    vc = xi[p.nx*p.K+p.nu*(p.K-1)+p.K:p.nx*p.K+p.nu*(p.K-1)+p.K-1+p.nx*(K-1)]
    # G = xi[3*(K-1)+(K-1)+6*(2*K-1)+1:3*(K-1)+(K-1)+6*(3*K-2)]
    vb = xi[p.nu*(p.K-1)+(p.K-1)+p.nx*(p.nu*p.K-2)+1:end]

    p.Δ = sqrt(norm((x - (par.Px\p.xref)[:]))^2 + norm((u - (par.Pu\p.uref)[:]))^2)
    p.Δσ = norm(σ - p.σref / par.Pσ)
    p.xref .= par.Px * reshape(x, (6, K))
    p.uref .= par.Pu * reshape(u, (3, K))
    p.σref .= par.Pσ * I(p.K - 1) * σ
    p.vc .= reshape(vc, (p.nx, (p.K - 1)))
    # p.vb .= vb
end
function pipg_vec_solve!(p::ptr, opts::PIPG_OPTS, P, q, H, h, zopt)
    stop = false
    k = 1

    a, b = compute_stepsizes(p, opts, H)

    z = zeros(length(q))
    w = zeros(length(h))
    xi = zeros(length(q))
    eta = zeros(length(h))

    for i = 1:size(H)[1]
        nrm = norm(H[i, :])
        H[i, :] /= nrm
        h[i] /= nrm
    end

    while (stop == false)
        z = xi - a * (P * xi + q + H' * eta)
        project_D!(p, z)
        w = eta + b * (H * (2 * z - xi) - h)
        xi = (1 - opts.rho) * xi + opts.rho * z
        eta = (1 - opts.rho) * eta + opts.rho * w

        if mod(k, opts.check_iter) == 0
            # r = p.wtr * (sum((par.Px \ p.xref)[:].^2) + sum((par.Pu \ p.uref)[:].^2) + sum((par.Pσ \ p.σref).^2))
            # @printf("%3d   %10.3e  %9.2e\n",
                # k, norm(0.5 * dot(xi, P * xi) + dot(q, xi) + r), norm(H * xi - h))
            stop = k >= opts.max_iters || (norm(xi - zopt) / norm(zopt) <= 0.01)
        end
        k += 1
    end
    println(k)
    return xi
end