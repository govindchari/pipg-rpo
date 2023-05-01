function initialize!(p::ptr)
    par = p.par

    p.xref[:, 1] = par.x0
    p.xref[:, p.K] = par.xT

    p.uref[:, 1] = [0.0; 0.0; 0.0]
    p.uref[:, p.K] = [0.0; 0.0; 0.0]

    idx_r = 1:3
    idx_v = 4:6

    # Initialize State and Control
    for k = 2:p.K-1
        p.xref[idx_r, k] = par.x0[idx_r] + ((p.xref[idx_r, p.K] - par.x0[idx_r]) / (p.K - 1)) * (k - 1)
        p.xref[idx_v, k] = par.x0[idx_v] + ((p.xref[idx_v, p.K] - par.x0[idx_v]) / (p.K - 1)) * (k - 1)
        p.uref[:, k] = [1.0; 1.0; 1.0] * 1
    end
    if (p.disc == :single)
        p.σref = 2 * norm(par.x0 - par.xT) / (par.umax * p.K)
    elseif(p.disc == :multiple)
        p.σref = 2 * norm(par.x0 - par.xT) / (par.umax * p.K) * ones(p.K - 1)
    end
end