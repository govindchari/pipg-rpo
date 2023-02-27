clc
close all
clearvars

n = 14;
m = 3;
N = 50;
A = randn(n);
B = randn(n,m);

Hu = kron(speye(N),B);
Hx = [kron(speye(N),A) zeros(n*N,n)] - [zeros(n*N,n) speye(n*N)];
H = sparse([Hx,Hu]);
spy(H,2)
title(horzcat('\% non-zero = ',num2str(100*nnz(H)/numel(H),2)),'Interpreter','latex','FontSize',26)
xlabel("$H$",'FontSize',40,'Interpreter','latex');

P = speye(n*N+m*(N-1));
figure
spy(P,7)
xlabel("");
title(horzcat('\% non-zero = ',num2str(100*nnz(P)/numel(P),2)),'Interpreter','latex','FontSize',26)
xlabel("$P$",'FontSize',40,'Interpreter','latex');

