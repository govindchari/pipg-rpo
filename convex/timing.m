clear;clc;close all

addpath pipg_devec/
addpath pipg_vec/
addpath pipg_vec/projections/
addpath utils/

params = params();
prob = pipg_vec_struct(params);
opts = pipg_vec_opts();

N = 50;
ecos = zeros(N,1);
pipg = zeros(N,1);

for i = 1:N
    [~, ~, solve_time, ~, ~] = ecos_trajopt(params);
    [~, ~, ~, ~, pipg_time] = pipg_vec_solver_mex(params, prob, opts);
    ecos(i) = solve_time;
    pipg(i) = pipg_time;
    if mod(i, 1) == 0
        fprintf("On Run %d \n", i)
    end
end

fprintf("Mean ECOS Solve Time: %4.1f ms\n", mean(ecos))
fprintf("Mean PIPG Solve Time: %4.1f ms\n", mean(pipg))

