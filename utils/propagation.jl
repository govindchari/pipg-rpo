function single_shot(p::ptr, Nsub)
    N = (p.K - 1) * (Nsub - 1)
    Z = zeros(nx, N)
    t = zeros(N)
    dt = 1 / Nsub
    Z[:, 1] = p.xref[:, 1] + [0.0; 0.0; 0.0; p.uref[:, 1]]
    for i = 1:N-1
        k = floor(Int64, i / (Nsub + 1)) + 1
        u = [0.0; 0.0; 0.0]
        if mod(i, (Nsub + 1)) == 0
            u = p.uref[:, k]
        end
        σ = p.σref[k]
        df(t, x, p) = σ * p.f(x, [0.0; 0.0; 0.0])
        Z[:, i+1] = RK4(df, Z[:, i] + [0.0; 0.0; 0.0; u], dt * (i - 1), dt, 1, p)
        t[i+1] = dt * σ + t[i]
    end
    return Z, t
end