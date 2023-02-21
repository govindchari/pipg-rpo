clear;clc;close all

addpath pipg/
addpath pipg/projections/
addpath utils/
addpath double_integrator/

%% Rendezvous Problem
params = params();

% Solve with YALMIP/Gurobi
[X, U, solve_time, parse_time, solve_status] = ecos_trajopt(params);

fprintf("Solve Status: %s\n", solve_status)
fprintf("Parse Time: %4.1f ms\n", parse_time)
fprintf("Solve Time: %4.1f ms\n", solve_time)

plotall(X, U, params)

% Solve with PIPG

prob = problem(params);
[X, U, pc, dc, xcg, ucg] = pipg_solver(params, prob);
plotall(X', U', params)

figure
semilogy(pc, "LineWidth",1)
hold on
semilogy(dc, "LineWidth",1)
grid on

figure
semilogy(xcg, "LineWidth",1)
hold on
semilogy(ucg, "LineWidth",1)
grid on
title("Distance to Optimal")

%% Double Integrator Test
% params = double_integrator_params();
% prob = problem(params);
% 
% [X, U, solve_time, parse_time, solve_status] = double_integrator_test(params);
% fprintf("Solve Status: %s\n", solve_status)
% fprintf("Parse Time: %4.1f ms\n", parse_time)
% fprintf("Solve Time: %4.1f ms\n", solve_time)
% plot_double_integrator(X, U, params)
% 
% [X_pipg, U_pipg, pc, dc] = pipg_solver(params, prob);
% 
% figure
% plot(X_pipg(:,1))
% hold on
% plot(X(1,:))
% 
% plot_double_integrator(X_pipg', U_pipg, params)
% figure
% semilogy(pc, "LineWidth",1)
% hold on
% semilogy(dc, "LineWidth",1)
% grid on

