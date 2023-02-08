clear;clc;close all

% addpath 'convex'
addpath pipg/
addpath utils/
params = params();

%% Solve with YALMIP/ECOS
[X, U, solve_time, parse_time, solve_status] = ecos_trajopt(params);

fprintf("Solve Status: %s\n", solve_status)
fprintf("Parse Time: %4.1f ms\n", parse_time)
fprintf("Solve Time: %4.1f ms\n", solve_time)

plotall(X, U, params)

%% Solve with PIPG

prob = problem(params);
[X, U] = pipg_solver(params, prob);
plotall(X', U', params)
