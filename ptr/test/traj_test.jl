using LinearAlgebra

include("../utils/structs.jl")
include("../utils/discretize.jl")
include("../utils/plotting.jl")

include("../src/initialize.jl")
include("../src/dynamics.jl")
include("../src/solver.jl")
include("../src/subproblem.jl")

K = 15
n = 0.00113
x0 = [200.0;1000.0;200.0;0;0;0]
xT = zeros(6)
σmax = 300.0
σmin = 100.0
umax = 0.1
vmax = 0.5
rc = [200.0;400.0;0.0]
rho = 100.0
nx = 6
nu = 3

Pu = umax * I(3)
Px = Diagonal([200.0;1000.0;200.0;vmax;vmax;vmax])
Pσ = 300.0

par = PARAMS(n, x0, xT, umax, vmax, σmin, σmax, rc, rho, Px, Pu, Pσ)
p = ptr(nx, nu, K, f, dfx, dfu, par, :impulsive, :multiple)
solveTraj!(p)

plot_all(p)