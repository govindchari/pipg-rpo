function p = problem(par)

    %%%%%%%%%%%%%%%%%%%%%%%%
    %%% Objective Matrix %%%
    %%%%%%%%%%%%%%%%%%%%%%%%

    P = sparse(par.R);
    for i = 1:par.N-1
        P = blkdiag(P, sparse(par.Q), sparse(par.R));
    end
    % P = blockdiag(P, sparse(Q)); %Uncomment if not using xT
    p.P = P;

    %%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Constraint Matrix %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%

    H = kron(eye(par.N), [-par.B eye(par.nx)]);
    for k = 1:par.N-1
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

    p.X = zeros(par.N + 1, par.nx);
    p.U = zeros(par.N, par.nu);
    p.V = zeros(par.N + 2, par.nx);
    p.W = zeros(par.N + 1, par.nx);

    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Boundary Conditions %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    p.X(1, :) = par.x0;
    p.X(par.N+1, :) = par.xT;
end