clear;clc;close all

addpath pipg_devec/
addpath pipg_devec/projections/
addpath pipg_vec/
addpath utils/
addpath double_integrator/

%% Rendezvous Problem
% params = params();
% 
% % Solve with YALMIP/Gurobi
[X, U, solve_time, parse_time, solve_status] = ecos_trajopt(params);

fprintf("Solve Status: %s\n", solve_status)
fprintf("Parse Time: %4.1f ms\n", parse_time)
fprintf("Solve Time: %4.1f ms\n", solve_time)

plotall(X, U, params)

% Solve with Devectorized PIPG

% prob = pipg_devec_struct(params);
% [X_pipg, U_pipg, pc, dc, xcg, ucg] = pipg_devec_solver(params, prob);
% plotall(X_pipg', U_pipg', params)
% 
% figure
% semilogy(pc, "LineWidth",1)
% hold on
% semilogy(dc, "LineWidth",1)
% grid on
% 
% figure
% semilogy(xcg, "LineWidth",1)
% hold on
% semilogy(ucg, "LineWidth",1)
% grid on
% title('Convergence to Gurobi')

% Solve with Vectorized PIPG
prob = pipg_vec_struct(params);
opts = pipg_vec_opts();
tic
[Z_pipg, pc, dc] = pipg_vec_solver(params, prob, opts);
toc
[X_pipg, U_pipg] = devec_sol(Z_pipg, params);
plotall(X_pipg, U_pipg, params)

figure
semilogy(pc, "LineWidth",1)
hold on
semilogy(dc, "LineWidth",1)
grid on

figure(7)
plot(X(2,:),X(1,:),"LineWidth",2)
hold on
plot(X_pipg(2,:),X_pipg(1,:),"LineWidth",2)
title("Gurobi vs PIPG")
legend("Gurobi","PIPG")
grid on

%% Double Integrator Test
% params = double_integrator_params();
% prob = pipg_struct(params);
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

