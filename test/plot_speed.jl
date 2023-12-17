using PyPlot, JLD2, Statistics
include("../utils/set_plot.jl")

ecos = load_object("data/ecos_times.jld2")
pipg = load_object("data/pipg_times.jld2")
ecos *= 1000
pipg *= 1000


emed = median(ecos)
emean = mean(ecos)
estd = std(ecos)

pmed = median(pipg)
pmean = mean(pipg)
pstd = std(pipg)

println("ECOS Median: ", emed)
println("ECOS Mean: ", emean)
println("ECOS STD: ", estd)

println("PIPG Median: ", pmed)
println("PIPG Mean: ", pmean)
println("PIPG STD: ", pstd)

println("Performance: ", emean/pmean)

pygui(true)
figure(dpi=200)
set_fonts()
set_fonts()
count, bin_ecos = hist(ecos, 80, label="ECOS", color="mediumseagreen")
count, bin_pipg = hist(pipg, label="PIPG", color="coral")
xlim(0, 350)
title("Solve Time Histogram")
xlabel("Solve Time (ms)")
ylabel("Frequency")
legend()
grid()
savefig("../../doc/img/solve_speed.png")

show()