function opts = pipg_vec_opts()

    %%%%%%%%%%%%%%%%%%%%%%
    %%% Stepsize Ratio %%%
    %%%%%%%%%%%%%%%%%%%%%%
    opts.omega = 1;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Extrapolation Parameter %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    opts.rho = 1.8;
    
    %%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Stopping Criteria %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%

    opts.check_iter = 50;
    opts.eps_rel = 8e-5;
    opts.eps_abs = 8e-5;
    opts.max_iter = 10000;

    %%%%%%%%%%%%%%%%%%%%%%%
    %%% Power Iteration %%%
    %%%%%%%%%%%%%%%%%%%%%%%

    opts.eps_rel_pow = 1e-3;
    opts.eps_abs_pow = 1e-3;
    opts.eps_buff = 0.05;
    opts.max_iter_pow = 25;

end
