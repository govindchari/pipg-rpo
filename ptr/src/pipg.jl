using SparseArrays, IterativeSolvers

struct PIPG_OPTS
    omega::Float64
    rho::Float64
    max_iters::Int64
    check_iter::Int64
    eps_abs_pow::Float64
    eps_rel_pow::Float64
    max_iter_pow::Int64
    eps_buff::Float64
    function PIPG_OPTS()
        omega = 375.0
        rho = 1.65
        max_iters = 50
        check_iter = 1
        eps_abs_pow = 1e-3
        eps_rel_pow = 1e-3
        max_iter_pow = 25
        eps_buff = 0.01
        new(omega, rho, max_iters, check_iter, eps_abs_pow, eps_rel_pow, max_iter_pow, eps_buff)
    end
end
struct CACHE
    r1::Array{Float64,1}
    r2::Array{Float64,1}
    pwr1::Array{Float64,1}
    pwr2::Array{Float64,1}
    function CACHE(p::ptr)
        new(zeros(3), zeros(3), ones(p.nx * (3 * p.K - 2) + p.nu * (p.K - 1) + (2 * p.K - 1)), ones(p.nx * (p.K - 1)))
    end
end
function power_iteration(H, Ht, opts::PIPG_OPTS, c::CACHE)
    sig = 0
    sig_old = 1e6
    iter = 1
    while (abs(sig - sig_old) >= opts.eps_abs_pow + opts.eps_rel_pow * max(sig, sig_old) && iter < opts.max_iter_pow)
        sig_old = sig
        mul!(c.pwr2, H, c.pwr1)
        mul!(c.pwr1, Ht, c.pwr2)
        sig = norm(c.pwr1)
        c.pwr1 ./= sig
        iter += 1
    end
    sig *= (1 + opts.eps_buff)
    return sig
end
function compute_stepsizes(p::ptr, opts::PIPG_OPTS, c::CACHE, H)
    normP = 2.0 * (1.0 + p.wtr)
    norm2H = power_iteration(H, H', opts, c)
    alpha = 2 / (sqrt(normP^2 + 4 * opts.omega * norm2H) + normP)
    beta = opts.omega * alpha
    return alpha, beta
end
function vectorize(p::ptr)
    par = p.par
    nx = 6
    nu = 3
    nc = nx * (p.K - 1)   # Number of equality constraints in vectorized problem

    # Construct P
    Pvec = [2.0 * p.wtr * ones(nx * p.K); 2.0 * (1.0 + p.wtr) * ones(nu * (p.K - 1)); 2.0 * p.wtr * ones(p.K - 1); zeros(nx * (p.K - 1)); zeros(nx * (p.K - 1)); zeros(p.K)]
    P = Diagonal(Pvec)

    # Construct q
    q = [-2.0 * p.wtr * (par.Px\p.xref)[:]; -2.0 * p.wtr * (par.Pu\p.uref)[:][1:end-nu]; -2.0 * p.wtr * (p.σref./par.Pσ)[:]; zeros(nx * (p.K - 1)); p.wvc * ones(nx * (p.K - 1)); p.wvb * ones(p.K)]

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
    H = sparse([Hx Hu Hs Hvc HG Hvb])

    # Construct h
    h = -(par.Px\p.z)[:]

    return P, q, H, h
end
function proj_ball!(x::SubArray{Float64,1,Vector{Float64},Tuple{UnitRange{Int64}},true}, r::Float64)
    nrm = norm(x)
    if (nrm > r)
        x .= (r / nrm) .* x
    end
end

function proj_box!(x::SubArray{Float64,1,Vector{Float64},Tuple{UnitRange{Int64}},true}, l::Float64, u::Float64)
    x .= min.(max.(x, l), u)
end
function proj_inter_halfspaces!(c, u1::Vector{Float64}, u2::Vector{Float64}, eta1::Float64, eta2::Float64)
    # eps = 1e-9
    a1 = dot(c, u1)
    a2 = dot(c, u2)
    b = dot(u1, u2)
    # if (max(abs(norm(u1) - 1), abs(norm(u2) - 1)) >= eps)
    #     error("u1 and u2 must be unit vectors")
    # end
    # if abs(b - 1) <= eps
    #     eta = min(eta1, eta2)
    #     if a1 <= eta
    #         c .= c
    #     else
    #         c .= c + (eta - a1) * u1
    #     end
    # elseif abs(b + 1) <= eps
    #     if eta2 <= -eta1
    #         error("Empty Intersection of Halfspaces")
    #     else
    #         if a1 < -eta2
    #             c .= c - (a1 + eta2) * u1
    #         elseif (-eta2 <= a1 && a1 <= eta1)
    #             c .= c
    #         else
    #             c .= c - (a1 - eta1) * u1
    #         end
    #     end
    # else
    nu1 = 0.0
    nu2 = 0.0
    # if a1 <= eta1 && a2 <= eta2
    # nu1 = 0.0
    # nu2 = 0.0
    case1 = a1 - eta1 - b * (a2 - eta2)
    case2 = a2 - eta2 - b * (a1 - eta1)
    if case1 > 0 && case2 > 0
        den = (1 - b^2)
        nu1 = case1 / den
        nu2 = case2 / den
    elseif a2 > eta2 && a1 - eta1 <= b * (a2 - eta2)
        # nu1 = 0.0
        nu2 = a2 - eta2
    else
        nu1 = a1 - eta1
        # nu2 = 0.0
    end
    @. c = c - nu1 * u1 - nu2 * u2
    # end
end
function project_D!(p::ptr, z::Vector{Float64}, c::CACHE)

    c.r1 .= 0
    c.r2 .= 0

    vmax_sc = p.par.vmax / maximum(diag(p.par.Px[4:6, 4:6]))
    umax_sc = p.par.umax / maximum(diag(p.par.Pu))

    # State Constraints
    u2 = [0.0; 0.0; 0.0; -1.0]
    u1 = [0.0; 0.0; 0.0; -1.0]

    @inbounds for k = 1:p.K
        idx_r = p.nx * (k - 1) + 1
        idx_v = p.nx*(k-1)+4:p.nx*k
        idx_vb = p.nx * (3 * p.K - 2) + p.nu * (p.K - 1) + (p.K - 1) + k
        # Keepout Zone
        @. c.r1 = (@view p.xref[1:3, k]) - p.par.rc

        nxref = norm(c.r1)
        @. c.r1 = c.r1 / nxref

        mul!(c.r2, (@view p.par.Px[1:3, 1:3]), -c.r1)
        u1[1:3] .= c.r2
        eta1 = nxref - p.par.rho - dot(c.r1, (@view p.xref[1:3, k]))

        nrm = norm(u1)
        u1 ./= nrm
        eta1 /= nrm

        proj_inter_halfspaces!((@view z[[idx_r, idx_r + 1, idx_r + 2, idx_vb]]), u1, u2, eta1, 0.0)
        # Max Speed
        proj_ball!((@view z[idx_v]), vmax_sc)
    end

    # Control Constraint
    @inbounds @simd for k = 1:p.K
        idx_u = (p.nx*K)+p.nu*(k-1)+1:(p.nx*K)+p.nu*k
        proj_ball!((@view z[idx_u]), umax_sc)
    end
    # L1 Norm Reformulation for virtual control
    base = p.nx * p.K + p.nu * (p.K - 1) + (p.K - 1)
    shift = p.nx * (p.K - 1)
    u1 = [-1.0; -1.0] / sqrt(2)
    u2 = [1.0; -1.0] / sqrt(2)
    @inbounds @simd for k = 1:p.nx*(p.K-1)
        proj_inter_halfspaces!((@view z[[base + k, base + shift + k]]), u1, u2, 0.0, 0.0)
    end

    # Dilation Constraints
    idx_σ = p.nx*p.K+p.nu*(p.K-1)+1:p.nx*p.K+p.nu*(p.K-1)+p.K-1
    proj_box!((@view z[idx_σ]), p.par.σmin / p.par.Pσ, p.par.σmax / p.par.Pσ)

    # Boundary Conditions
    z[1:p.nx] = p.par.Px \ p.par.x0
    z[p.K*p.nx-p.nx+1:p.K*p.nx] = p.par.Px \ p.par.xT
end

function package_solution(p::ptr, xi::Vector{Float64}, eta::Vector{Float64})
    # Package z back into ptr struct
    x = xi[1:p.nx*p.K]
    u = [xi[p.nx*p.K+1:p.nx*p.K+p.nu*(p.K-1)]; 0; 0; 0]
    σ = xi[p.nx*p.K+p.nu*(p.K-1)+1:p.nx*p.K+p.nu*(p.K-1)+p.K-1]
    vc = xi[p.nx*p.K+p.nu*(p.K-1)+p.K:p.nx*p.K+p.nu*(p.K-1)+p.K-1+p.nx*(K-1)]
    # G = xi[3*(K-1)+(K-1)+6*(2*K-1)+1:3*(K-1)+(K-1)+6*(3*K-2)]
    vb = xi[p.nu*(p.K-1)+(p.K-1)+p.nx*(p.nu*p.K-2)+1:end]

    p.Δ = sqrt(norm((x - (p.par.Px\p.xref)[:]))^2 + norm((u - (p.par.Pu\p.uref)[:]))^2)
    p.Δσ = norm(σ - p.σref / par.Pσ)
    p.xref .= p.par.Px * reshape(x, (6, K))
    p.uref .= p.par.Pu * reshape(u, (3, K))
    p.σref .= p.par.Pσ * I(p.K - 1) * σ
    p.vc .= reshape(vc, (p.nx, (p.K - 1)))
    p.vb .= vb
    p.zws .= xi
    p.wws .= eta
    p.ws = true
end
function pipg_vec_solve!(p::ptr, opts::PIPG_OPTS, c::CACHE, P, q, H, h)
    t = @elapsed begin

        a, b = compute_stepsizes(p, opts, c, H)

        z = p.zws
        w = p.wws
        xi = p.zws
        eta = p.wws

        @inbounds for k = 1:opts.max_iters
            z = xi - a * (P * xi + q + H' * eta)
            project_D!(p, z, c)
            w = eta + b * (H * (2 * z - xi) - h)
            xi .= (1 - opts.rho) .* xi .+ opts.rho .* z
            eta = (1 - opts.rho) .* eta .+ opts.rho .* w
        end
    end
    return xi, eta, opts.max_iters, t
end