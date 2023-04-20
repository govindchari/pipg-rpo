using LinearAlgebra
using PyPlot

include("../utils/structs.jl")
include("../utils/discretize.jl")
include("../src/initialize.jl")
include("../src/dynamics.jl")

K = 15
n = 0.00113
x0 = [0.01;1000;0;0;0;0]
xT = zeros(6)
umax = 0.25
nx = 6
nu = 3

par = PARAMS(n, x0, xT, umax)
p = ptr(nx, nu, K, f, dfx, dfu, par)
initialize!(p)
p.σref = 1000.0
p.xref = zeros(p.nx, p.K)
FOH_discretize!(p)

x = zeros(6, K)
x[:,1] = x0

for k = 1:K-1
    x[:,k+1] = p.A[:,:,k] * x[:,k] + p.S[:,k] * p.σref + p.z[:,k]
end

pygui(true)

figure(dpi=200)
plot(x[2,:], x[1,:])
plt.show()
