function p = double_integrator_params()
    % 1D Double Integrator

    p = struct;

    %%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Problem Parameters %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%
    nx = 2;
    p.nx = nx;
    nu = 1;
    p.nu = nu;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Discretization Parameters %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    dt = 0.1;    % Discretization time [s]
    p.dt = dt;
    T = 10;   % Time horizon [s]
    p.T = T;
    N = T/dt;    % Number of discretization intervals
    p.N = N;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Boundary Conditions %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%

    % x = [r v]'
    x0 = [10 0]';
    xT = [0 0]';
    p.x0 = x0;
    p.xT = xT;

    %%%%%%%%%%%%%%%%%%%
    %%% Constraints %%%
    %%%%%%%%%%%%%%%%%%%
    umax = 0.5;         % Max acceleration [m s^-2]
    p.umax = umax;

    %%%%%%%%%%%%%%%%%%%%%%%%
    %%% Scaling Matrices %%%
    %%%%%%%%%%%%%%%%%%%%%%%%
    Px = diag([10 1]);
    Pu = diag([0.5]);
    p.Px = Px;
    p.Pu = Pu;

    %%%%%%%%%%%%%%%%
    %%% Dynamics %%%
    %%%%%%%%%%%%%%%%
    p.A = [1 dt; 0 1];
    p.B = [0.5 * dt^2; dt];

    %%%%%%%%%%%%
    %%% Cost %%%
    %%%%%%%%%%%%
    p.Q = zeros(nx);
    p.R = eye(nu);

end