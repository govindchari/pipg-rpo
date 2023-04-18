struct IDX

    # Discretization integration state
    N::Int64                # Number of states in discretization integration state
    x::UnitRange{Int64}     # Indices of state
    phi::UnitRange{Int64}   # Indices of state transition matrix
    Bm::UnitRange{Int64}    # Indices of Bm
    Bp::UnitRange{Int64}    # Indices of Bp
    S::UnitRange{Int64}     # Indices of S
    z::UnitRange{Int64}     # Indices of z

    function IDX(nx, nu)
        idx_x = 1:nx
        idx_phi = (nx+1):(nx+nx^2)
        idx_Bm = (nx+nx^2+1):(nx+nx^2+nx*nu)
        idx_Bp = (nx+nx^2+nx*nu+1):(nx+nx^2+nx*nu+nx*nu)
        idx_S = (nx+nx^2+2*nx*nu+1):(nx+nx^2+2*nx*nu+nx)
        idx_z = (2*nx+nx^2+2*nx*nu+1):(2*nx+nx^2+2*nx*nu+nx)

        new(nx^2 + 3 * nx + 2 * nx * nu, idx_x, idx_phi, idx_Bm, idx_Bp, idx_S, idx_z)
    end

end
struct PARAMS
    # Initial Condition
    x0::Array{Float64,1}
    xT::Array{Float64,1}
    umax::Float64           # Max delta-v
    n::Float64              # Mean motion

    function PARAMS(n, x0, xT, umax)
        new(n, x0, xT, umax)
    end
end
mutable struct ptr

    # Problem paramters
    nx::Int64     # Number of states
    nu::Int64     # Number of controls
    K::Int64      # Number of PTR nodes
    dτ::Float64   # Normalized time per interval

    # PTR Hyperparameters
    Nsub::Int64   # Number of integration subintervals for discretization
    wD::Float64   # Weight on trust region
    wDσ::Float64  # Weight on time trust region
    wnu::Float64  # Virtual control weight

    # Dynamics and Jacobians
    f::Function   # CT Dynamics
    dfx::Function # State Jacobian
    dfu::Function # Control Jacobian

    # Reference Trajectories
    xref::Array{Float64,2} # Reference state trajectory
    uref::Array{Float64,2} # Reference control trajectory
    σref::Float64          # Reference time dilation

    # Integrated Trajectory
    xint::Array{Float64,2}

    # Virtual Control and Trust Region Size
    vc::Array{Float64,2}
    Δ::Array{Float64,1}
    Δσ::Float64

    # Discrete Dynamics

    idx::IDX
    xprop::Array{Float64,2}  # Propagated state
    def::Array{Float64,1}    # Defect
    A::Array{Float64,3}      # Discrete A matrices
    Bm::Array{Float64,3}     # Discrete Bm matrices
    Bp::Array{Float64,3}     # Discrete Bp matrices
    S::Array{Float64,2}      # Discrete S vectors
    z::Array{Float64,2}      # Discrete z vector 

    # Problem paramters
    par::PARAMS

    function ptr(K::Int64, f::Function, dfx::Function, dfu::Function, par::PARAMS)
        nx = 6
        nu = 3
        Nsub = 10
        wD = 1
        wDσ = 1
        wnu = 5e4
        dτ = 1 / (K - 1)

        new(nx, nu, K, dτ, Nsub, wD, wDσ, wnu, f, dfx, dfu, zeros(nx, K), zeros(nu, K), 0.0, zeros(nx, K + (K - 1) * (Nsub - 1)), zeros(nx, K), zeros(K), 0.0, IDX(nx, nu), zeros(nx, K - 1), zeros(K - 1), zeros(nx, nx, K - 1), zeros(nx, nu, K - 1), zeros(nx, nu, K - 1), zeros(nx, K - 1), zeros(nx, K - 1), par)
    end
end
