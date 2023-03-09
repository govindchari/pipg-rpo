function p = params()

    p = struct;

    %%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Problem Parameters %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%
    nx = 6;
    p.nx = nx;
    nu = 3;
    p.nu = nu;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Discretization Parameters %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    dt = 50;    % Discretization time [s]
    p.dt = dt;
    T = 1000;   % Time horizon [s]
    p.T = T; 
    N = T/dt + 1;    % Number of discretization nodes
    p.N = N;

    %%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Gravity parameters %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%

    mu = 3.986e14;    % Standard graviational parameter [m^3 s^-2]
    a = 6793137;      % Reference semjax (m)
    n = sqrt(mu/a^3); % Mean motion (s^-1)
    p.n = n;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Boundary Conditions %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%

    % x = [r v]'
    x0 = [0 1000 0 0 0 0]';
    xN = [0 0 0 0 0 0]';
    p.x0 = x0;
    p.xN = xN;
    if x0(2) > 0
        leading = 1;
    else
        leading = -1;
    end
    p.leading = leading;
    
    %%%%%%%%%%%%%%%%%%%
    %%% Constraints %%%
    %%%%%%%%%%%%%%%%%%%

    p.th_ac = deg2rad(45); % Approach cone half-angle [rad]    
    p.umax = 0.25; % Max delta-v [m s^-1]
    p.vmax = 1.5; % Max speed [m s^-1]

    %%%%%%%%%%%%%%%%
    %%% Dynamics %%%
    %%%%%%%%%%%%%%%%
    [p.A, p.B] = dynamics(n, dt);

    %%%%%%%%%%%%
    %%% Cost %%%
    %%%%%%%%%%%%
    p.Q = zeros(nx);
    p.R = eye(nu);

    %%%%%%%%%%%%%%%%%%%%%%%%
    %%% Scaling Matrices %%%
    %%%%%%%%%%%%%%%%%%%%%%%%
%     Px = diag([140, 1000, 1, 1.6, 1.6, 1.6]);
    Px = diag([140, 140, 140, 1.6, 1.6, 1.6]);
    Pu = p.umax*eye(nu); % Must be some multiple of the identity
%     Px = eye(nx);
%     Pu = eye(nu);
    p.Px = Px;
    p.Pu = Pu;

    p.x0s = Px \ x0;
    p.xNs = Px \ xN;

end