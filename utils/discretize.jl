function discretize!(p::ptr)
    for k = 1:p.K-1
        idx = p.idx

        # Get integrator initial conditions
        # Integrator state is [x;phi;Bm;Bp;S;z]
        P0 = zeros(idx.N)
        if (p.disc == :impulsive)
            P0[idx.x] = p.xref[:, k] + [0; 0; 0; p.uref[:, k]]
        else
            P0[idx.x] = p.xref[:, k]
        end
        P0[idx.phi] = reshape(I(p.nx), (p.nx^2, 1))
        P0[idx.Bm] = zeros(p.nx * p.nu)
        P0[idx.Bp] = zeros(p.nx * p.nu)
        P0[idx.S] = zeros(p.nx)
        P0[idx.z] = zeros(p.nx)

        # Integrate continous time matrices to get exact discretization
        z = RK4(df, P0, (k - 1) * p.dτ, p.dτ, p.Nsub, p)

        # Package discrete time matrices
        p.xprop[:, k] .= z[idx.x]
        p.def[k] = norm(z[idx.x] - p.xref[:, k+1])
        Ak = reshape(z[idx.phi], (p.nx, p.nx))
        p.A[:, :, k] .= Ak
        p.Bm[:, :, k] .= Ak * reshape(z[idx.Bm], (p.nx, p.nu))
        p.Bp[:, :, k] .= Ak * reshape(z[idx.Bp], (p.nx, p.nu))
        p.S[:, k] .= Ak * z[idx.S]
        p.z[:, k] .= Ak * z[idx.z]
    end
end
function df(τ::Float64, P::Array{Float64,1}, p::ptr)
    # Differential equation for the state [x;phi;Bm;Bp;S;z]

    idx = p.idx
    k = Int(floor(τ / p.dτ)) + 1

    # Linearized Dynamics
    lm = (k * p.dτ - τ) / p.dτ
    lp = (τ - (k - 1) * p.dτ) / p.dτ
    u = u_interp(τ, p)

    Px = P[idx.x]
    Pphi = P[idx.phi]
    Pphi_mat = reshape(Pphi, (p.nx, p.nx))
    F = factorize(Pphi_mat)

    dP = zeros(idx.N)
    if (p.dilation == :single)
        dP[idx.x] = p.σref * p.f(Px, u)
    elseif (p.dilation == :multiple)

        # Artifact of ZOH on σ
        if (k == p.K)
            k -= 1
        end
        dP[idx.x] = p.σref[k] * p.f(Px, u)
    end
    A, B, S, z = getCTMatrices(τ, Px, u, p)
    dP[idx.phi] = reshape(A * Pphi_mat, (p.nx^2, 1))
    dP[idx.Bm] = reshape(F \ (lm * B), (p.nx * p.nu, 1))
    dP[idx.Bp] = reshape(F \ (lp * B), (p.nx * p.nu, 1))
    dP[idx.S] = F \ S
    dP[idx.z] = F \ z

    return dP
end
function getCTMatrices(τ::Float64, x, u, p::ptr)
    if (p.dilation == :single)
        A = p.σref * p.dfx(x, u)
        B = p.σref * p.dfu(x, u)
    elseif (p.dilation == :multiple)
        k = Int(floor(τ / p.dτ)) + 1

        # Artifact of ZOH on σ
        if (k == p.K)
            k -= 1
        end
        A = p.σref[k] * p.dfx(x, u)
        B = p.σref[k] * p.dfu(x, u)
    end
    S = p.f(x, u)
    z = -reshape(A, (p.nx, p.nx)) * x - reshape(B, (p.nx, p.nu)) * u
    return A, B, S, z
end
function u_interp(τ::Float64, p::ptr)
    if (p.disc == :foh)
        # Uses FOH to interpolate control between nodes
        # Get control input at τ
        k = Int(floor(τ / p.dτ)) + 1
        lm = (k * p.dτ - τ) / p.dτ
        lp = (τ - (k - 1) * p.dτ) / p.dτ
        if (k == p.K)
            return p.uref[:, k]
        else
            return lm * p.uref[:, k] + lp * p.uref[:, k+1]
        end
    elseif (p.disc == :impulsive)
        return zeros(p.nu, 1)
    end
end
function RK4(dz::Function, z0::Array{Float64,1}, t0::Float64, dt::Float64, Nsub::Int64, p::ptr)
    # Uses RK4 to propagate z0 according to dz from t0 to t0 + dt with Nsub steps
    h = dt / Nsub
    z = copy(z0)
    for i = 1:Nsub
        # Each loop propagates from τ to τ + h
        τ = t0 + (i - 1) * h
        k1 = dz(τ, z, p)
        k2 = dz(τ + 0.5 * h, z + 0.5 * h * k1, p)
        k3 = dz(τ + 0.5 * h, z + 0.5 * h * k2, p)
        k4 = dz(τ + h, z + h * k3, p)
        z += (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4)
    end
    return z
end
