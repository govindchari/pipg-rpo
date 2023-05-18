using SparseArrays

struct PIPG_OPTS end

function vectorize(p::ptr)
    par = p.par
    nx = 6
    nu = 3
    nc = nx * (p.K - 1)   # Number of equality constraints in vectorized problem

    # Construct P
    Pvec = [2.0 * p.wtr * ones(nx * p.K); 2.0 * (1 + p.wtr) * ones(nu * (p.K - 1)); 2.0 * p.wtr * ones(p.K - 1); zeros(nx * (p.K - 1)); zeros(nx * (p.K - 1)); zeros(p.K)]
    # Pvec = [2.0 * p.wtr * ones(nx * p.K); 2.0 * (1 + p.wtr) * ones(nu * (p.K - 1)); 2.0 * p.wtr * ones(p.K - 1);zeros(nx * (p.K - 1)); zeros(nx * (p.K - 1))]
    P = Diagonal(Pvec)

    # Construct q
    q = [-2.0 * (par.Px \ p.xref)[:];-2.0 * (par.Pu \ p.uref)[:][1:end-nu];-2.0 * (p.σref ./ par.Pσ)[:];zeros(nx * (p.K - 1));p.wvc*ones(nx * (p.K - 1));p.wvb*ones(p.K)]
    # q = [-2.0 * (par.Px \ p.xref)[:];-2.0 * (par.Pu \ p.uref)[:][1:end-nu];-2.0 * (p.σref ./ par.Pσ)[:];zeros(nx * (p.K - 1));p.wvc*ones(nx * (p.K - 1))]


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
    # H = sparse([Hx Hu Hs Hvc HG])

    # Construct h
    h = -(par.Px \ p.z)[:]

    return P, q, H, h
end
function project_D(z::Vector{Float64})
end
function compute_stepsizes(P, H)
end
function pipg_vec_solve!(p::ptr, opts::PIPG_OPTS, P, q, H, h)
    stop = false
    k = 1

    a, b = compute_stepsizes(P, H)

    z = zeros(length(q))
    w = zeros(length(h))
    xi = zeros(length(q))
    eta = zeros(length(h))

    while (stop == false)
        z = project_D(xi - a * (P * xi + q + H' * eta))
        w = eta + b * (H * (2 * z - xi) - h)
        xi = (1 - opts.rho) * xi + opts.rho * z
        eta = (1 - opts.rho) * eta + opts.rho * w

        stop = k >= opts.max_iters
        k += 1
    end

    # Package z back into ptr struct
end