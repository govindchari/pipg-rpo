clc;clear;close all

%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Problem Parameters %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%
nx = 6;
nu = 3;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Discretization Parameters %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

dt = 2;    % Discretization time [s]
T = 100;   % Time horizon [s]
N = T/dt + 1;    % Number of discretization nodes

mu = 3.986e14;    % Standard graviational parameter [m^3 s^-2]
a = 6793137;      % Reference semjax (m)
n = sqrt(mu/a^3); % Mean motion (s^-1)


[A, B] = dynamics(n, dt);

% nx = 1;
% nu = 1;
% A = [2];
% B = [3];
% N = 3;

Hx = [kron(speye(N - 1),A) zeros(nx*(N - 1),nx)] ...
    - [zeros(nx*(N - 1),nx) speye(nx*(N - 1))];
Hu = kron(eye(N - 1), B);
zros = zeros(nx * (N-1), nu);
H1 = [Hx,Hu,zros];

H2 = kron(speye(N-1), [-B speye(nx)]);
for k = 1:N-2
    H2((k*nx)+(1:nx), (k*(nx+nu)-nx)+(1:nx)) = -A;
end
Hleft = [-A;zeros((N-2)*nx, nx)];
H2 = [Hleft,H2];

figure
spy(H1)
title("Sparsity Pattern of H", "Interpreter","latex", FontSize=32)
set(gca,'XTick',[], 'YTick', [])

% figure
% spy(H2)

[Q,R] = qr(H1',"econ");
figure
spy(Q')
title("Sparsity Pattern of $Q^\top$", "Interpreter","latex", FontSize=32)
set(gca,'XTick',[], 'YTick', [])




% norm(eig(H1'*H1)-eig(H2'*H2))