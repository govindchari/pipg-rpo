function p = pipg_devec_struct(par)

    load gurobi_sol.mat X U

    %%%%%%%%%%%%%%%%%%%%%%%%
    %%% Objective Matrix %%%
    %%%%%%%%%%%%%%%%%%%%%%%%

    P = sparse(par.R);
    for i = 1:par.N-1
        P = blkdiag(P, sparse(par.Q), sparse(par.R));
    end
    P = blkdiag(P, sparse(par.Q));
    p.P = P;

    %%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Constraint Matrix %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%

    H = kron(eye(par.N-1), [-par.B eye(par.nx)]);
    for k = 1:par.N-2
        H((k*par.nx)+(1:par.nx), (k*(par.nx+par.nu)-par.nx)+(1:par.nx)) = -par.A;
    end
    Hleft = [-par.A;zeros((par.N-2)*par.nx, par.nx)];
    H = [Hleft, H];
    p.H = sparse(H);
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Stepsize Parameter %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%
    p.omega = 1.0;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Extrapolation Parameter %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    p.rho = 1.4;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Optimizer Variables %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%

    p.X = zeros(par.N, par.nx);
    p.U = zeros(par.N, par.nu);
    p.Xt = zeros(par.N, par.nx);
    p.Ut = zeros(par.N, par.nu);
    p.Phi = zeros(par.N, par.nx);
    p.Phit = zeros(par.N, par.nx);

%     p.Xt = X';
%     p.Ut = [U'; 0 0 0];
    p.Xg = X;
    p.Ug = U';
    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Boundary Conditions %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    p.X(1, :) = par.Px \ par.x0;
    p.X(par.N, :) = par.Px \ par.xN;
end