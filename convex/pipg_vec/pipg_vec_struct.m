function p = pipg_vec_struct(par)

    %%%%%%%%%%%%%%%%
    %%% Prescale %%%
    %%%%%%%%%%%%%%%%
    [A,B,Q,R,umax,vmax] = prescale(par);
    p.umax = umax;
    p.vmax = vmax;

    %%%%%%%%%%%%%%%%%%%%%%%%
    %%% Objective Matrix %%%
    %%%%%%%%%%%%%%%%%%%%%%%%
    sig = 5.4360;
    R = (1/sig)*eye(3);
    P = sparse(Q);
    for i = 2:par.N
        P = blkdiag(P, sparse(Q));
    end
    for i = 1:par.N
        P = blkdiag(P, sparse(R));
    end
    p.P = sparse(P);

    %%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Constraint Matrix %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%
    Hx = [kron(speye(par.N - 1),A) zeros(par.nx*(par.N - 1),par.nx)] ...
        - [zeros(par.nx*(par.N - 1),par.nx) speye(par.nx*(par.N - 1))];
    Hu = kron(eye(par.N - 1), B);

    % Zeros to account for no B_{N}^+ but state vector has u_{N}
    zros = zeros(par.nx * (par.N - 1), par.nu);
    H = [Hx,Hu,zros];
    for i = 1:size(H,1)
        H(i,:) = H(i,:)/norm(H(i,:), Inf);
    end
    H = sparse(H);

    p.H = H;
    p.Ht = H';

    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Optimizer Variables %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%

    p.z = zeros(par.N * (par.nx + par.nu), 1);
    p.w = zeros((par.N - 1) * par.nx, 1);
    p.xi = zeros(par.N * (par.nx + par.nu), 1);
    p.eta = zeros((par.N - 1) * par.nx, 1);

end