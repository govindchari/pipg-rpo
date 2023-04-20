using LinearAlgebra
using PyPlot

include("../utils/structs.jl")
include("../utils/discretize.jl")
include("../src/initialize.jl")
include("../src/dynamics.jl")
include("../src/solver.jl")
include("../src/subproblem.jl")

K = 23
n = 0.00113
x0 = [200.0;1000.0;0;0;0;0]
xT = zeros(6)
umax = 0.25
nx = 6
nu = 3

par = PARAMS(n, x0, xT, umax)
p = ptr(nx, nu, K, f, dfx, dfu, par)
solveTraj!(p)

# initialize!(p)
# tmesh = 0:0.01:1
# z = zeros(6, length(tmesh))
# for i = 1:length(tmesh)
#     z[:,i] = getState(tmesh[i],p)
#     # println(getState(tmesh[i],p))
# end

println(sum(p.uref[:].^2))
# display(z[1,:])

pygui(true)

figure(dpi=200)
plot(p.xref[2,:], p.xref[1,:])
plt.title("Rendezvous Trajectory")
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
