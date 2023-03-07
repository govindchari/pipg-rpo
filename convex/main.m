clear;clc;close all

addpath pipg_devec/
addpath pipg_devec/projections/
addpath pipg_vec/
addpath utils/
addpath double_integrator/

%% Rendezvous Problem
params = params();

% % Solve with YALMIP/Gurobi
[X, U, solve_time, parse_time, solve_status] = ecos_trajopt(params);

fprintf("Solve Status: %s\n", solve_status)
fprintf("Parse Time: %4.1f ms\n", parse_time)
fprintf("Solve Time: %4.1f ms\n", solve_time)

[X, U] = unscale(X, U, params);
plotall(X, U, params)

% Solve with Vectorized PIPG
prob = pipg_vec_struct(params);
opts = pipg_vec_opts();
[Z_pipg, pc, dc, pipg_time] = pipg_vec_solver_mex(params, prob, opts);
[X_pipg, U_pipg] = devec_sol(Z_pipg, params);
[X_pipg, U_pipg] = unscale(X_pipg, U_pipg, params);

% Compute accuracy of Vectorized PIPG wrt ECOS
upipg = U_pipg(:);
acc = 100 * max(norm(X_pipg(:)-X(:))/norm(X(:)), norm(upipg(1:end-params.nu)-U(:))/norm(U(:)));

fprintf("PIPG Solve Time: %4.1f ms\n", pipg_time)
fprintf("Within %4.4f percent of ECOS\n", acc)

plotall(X_pipg, U_pipg, params)

% figure
% semilogy(pc, 'o', "LineWidth",1)
% hold on
% semilogy(dc, 'o', "LineWidth",1)
% grid on
% 
figure(7)
plot(X(2,:),X(1,:),"LineWidth",2)
hold on
plot(X_pipg(2,:),X_pipg(1,:),"LineWidth",2)
title("ECOS vs PIPG")
legend("ECOS","PIPG")
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

