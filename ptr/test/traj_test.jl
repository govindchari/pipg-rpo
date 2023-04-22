using LinearAlgebra
using PyPlot

include("../utils/structs.jl")
include("../utils/discretize.jl")
include("../utils/plotting.jl")

include("../src/initialize.jl")
include("../src/dynamics.jl")
include("../src/solver.jl")
include("../src/subproblem.jl")

K = 26
n = 0.00113
x0 = [200.0;1000.0;0;0;0;0]
xT = zeros(6)
umax = 0.25
rc = [100.0;400.0;0.0]
rho = 100.0
nx = 6
nu = 3

Pu = umax * I(3)
Px = Diagonal([1000.0;1000.0;1.0;1;1;1])
Pσ = 4000.0

par = PARAMS(n, x0, xT, umax, rc, rho, Px, Pu, Pσ)
p = ptr(nx, nu, K, f, dfx, dfu, par)
solveTraj!(p)

# tmesh = 0:0.01:1
# z = zeros(6, length(tmesh))
# for i = 1:length(tmesh)
#     z[:,i] = getState(tmesh[i],p)
#     # println(getState(tmesh[i],p))
# end

println(sum(p.uref[:].^2))

pygui(true)

set_fonts()
set_fonts()

figure(dpi=200)
theta = range( 0 , stop=2 * pi , length=150 )
a = rc[1] .+ rho * cos.( theta )
b = rc[2] .+ rho * sin.( theta )

scatter(p.xref[2,:], p.xref[1,:], label="Trajectory")
plot(b, a, color="red", label="Keepout Zone")
legend()
plt.axis("equal")
title("Rendezvous Trajectory")
grid(true)

# figure(dpi=200)
# plot(z[2,:], z[1,:])
# plt.title("Rendezvous Trajectory")
# grid(true)

figure(dpi=200)
plot(p.uref[:,1:end-1]')
axhline(par.umax, color="red")
axhline(-par.umax, color="red")
grid(true)
title("Control over Time")
xlabel("Time Step")
ylabel("Control")

plt.show()
