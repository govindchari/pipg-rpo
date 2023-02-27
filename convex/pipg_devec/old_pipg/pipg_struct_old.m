function p = pipg_struct_old(par)

    load gurobi_sol.mat X U

    %%%%%%%%%%%%%%%%%%%%%%%%
    %%% Objective Matrix %%%
    %%%%%%%%%%%%%%%%%%%%%%%%

    P = sparse(par.R);
    for i = 1:par.N-2
        P = blkdiag(P, sparse(par.Q), sparse(par.R));
    end
    % P = blockdiag(P, sparse(Q)); %Uncomment if not using xT
    p.P = P;

    %%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Constraint Matrix %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%

    H = kron(eye(par.N-1), [-par.B eye(par.nx)]);
    for k = 1:par.N-2
        H((k*par.nx)+(1:par.nx), (k*(par.nx+par.nu)-par.nx)+(1:par.nx)) = -par.A;
    end
    H(:,end-(par.nx-1):end) = []; % Comment if not using xT
    p.HtH = sparse(H' * H);
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Stepsize Parameter %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%
    p.omega = 1.0;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Optimizer Variables %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%

    p.X = zeros(par.N, par.nx);
    p.U = zeros(par.N-1, par.nu);
%     p.X = X;
%     p.U = U;
%     p.Xg = X;
%     p.Ug = U;
    p.V = zeros(par.N + 1, par.nx);
    p.W = zeros(par.N, par.nx);

    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Boundary Conditions %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    p.X(1, :) = par.Px \ par.x0;
    p.X(par.N, :) = par.Px \ par.xN;
end