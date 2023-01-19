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
    
    dt = 2;    % Discretization time [s]
    p.dt = dt;
    T = 1000;   % Time horizon [s]
    p.T = T;
    N = T/dt;    % Number of discretization intervals
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
    xT = [0 0 0 0 0 0]';
    p.x0 = x0;
    p.xT = xT;
    if x0(2) > 0
        leading = 1;
    else
        leading = -1;
    end
    p.leading = leading;

    %%%%%%%%%%%%%%%%%%%
    %%% Constraints %%%
    %%%%%%%%%%%%%%%%%%%

    th_ac = deg2rad(45); % Approach cone half-angle [rad]
    p.th_ac = th_ac;
    umax = 0.01;         % Max acceleration [m s^-2]
    p.umax = umax;

end