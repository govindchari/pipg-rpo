clear;clc;close all

addpath pipg_vec/
addpath pipg_vec/projections/
addpath utils/

%% Rendezvous Problem
params = params();

% % Solve with YALMIP/Gurobi
[X, U, solve_time, parse_time, solve_status] = ecos_trajopt(params);

fprintf("ECOS Solve Status: %s\n", solve_status)
fprintf("YALMIP Parse Time: %4.1f ms\n", parse_time)
fprintf("ECOS Solve Time: %4.1f ms\n", solve_time)

[X, U] = unscale(X, U, params);
% plotall(X, U, params)

% Solve with Vectorized PIPG
prob = pipg_vec_struct(params);
opts = pipg_vec_opts();
[Z_pipg, W_pipg, pc, dc, pipg_time] = pipg_vec_solver_mex(params, prob, opts);
W_pipg = reshape(W_pipg, params.nx, params.N-1);

[X_pipg, U_pipg] = devec_sol(Z_pipg, params);
[X_pipg, U_pipg] = unscale(X_pipg, U_pipg, params);

% Compute accuracy of Vectorized PIPG wrt ECOS
upipg = U_pipg(:);
acc = 100 * max(norm(X_pipg(:)-X(:))/norm(X(:)), norm(upipg(1:end-params.nu)-U(:))/norm(U(:)));

fprintf("PIPG Solve Time: %4.1f ms\n", pipg_time)
fprintf("Within %4.4f percent of ECOS\n", acc)

plotall(X_pipg, U_pipg, params)

figure
plot(X(2,:),X(1,:),"LineWidth",2)
hold on
plot(X_pipg(2,:),X_pipg(1,:),"LineWidth",2)
title("ECOS vs PIPG")
legend("ECOS","PIPG")
axis equal
grid on

% figure
% semilogy(pc, 'o', "LineWidth",1)
% hold on
% semilogy(dc, 'o', "LineWidth",1)
% grid on


