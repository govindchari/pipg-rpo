using PyPlot, JLD2, Statistics, UnPack

include("../utils/set_plot.jl")

file = jldopen("test/data/ecos_times.jld2")
@unpack ecos = file
close(file)

file = jldopen("test/data/pipg_times.jld2")
@unpack pipg = file
close(file)

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
count, bin_ecos = hist(ecos, label="ECOS", bins=17, color="mediumseagreen")
count, bin_pipg = hist(pipg, label="PIPG", color="coral")
xlim(0, 200)
xlabel("Solve Time (ms)")
ylabel("Frequency")
legend()
savefig("test/data/solve_speed.pdf")

show()