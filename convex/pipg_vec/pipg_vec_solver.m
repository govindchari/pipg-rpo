function [Z,primal_conv,dual_conv] = pipg_vec_solver(par, p, opts)
    function zproj = project_D(z, par, p)
        zproj = z;

        % Project onto boundary conditions
        zproj(1:par.nx) = par.Px \ par.x0;
        zproj(( (par.N - 1) * par.nx) + 1 : par.N * par.nx) = par.Px \ par.xN;
%         for i = 1 : par.N
%             idx = par.N * par.nx + (i-1) * par.nu + 1 : par.N * par.nx + i * par.nu;
%             zproj(idx) = proj_ball(z(idx), p.umax);
%         end
    end
    stop = false;
    fprintf("iter     objv     |Gx-g|\n")
    fprintf("-----------------------------\n")
    xiold = 1e6 * ones(par.N * (par.nx + par.nu), 1);
    etaold = 1e6 * ones((par.N - 1) * par.nx, 1);
    primal_conv = [];
    dual_conv = [];
    last_primal = 100;
    last_dual = 100;
    k = 1;
    [alpha, beta] = compute_stepsizes(p, opts);
    
    while (stop == false)

        % Primal Update
        p.z = project_D(p.xi - alpha * (p.P * p.xi + p.Ht * p.eta), par, p);

        % Dual Update
        p.w = p.eta + beta* (p.H * (2 * p.z - p.xi));

        % Extrapolation
        p.xi = (1 - opts.rho) * p.xi + opts.rho * p.z;
        p.eta = (1 - opts.rho) * p.eta + opts.rho * p.w;
        if mod(k, opts.check_iter) == opts.check_iter - 1
            xiold = p.xi;
            etaold = p.eta;
        end
        if mod(k, opts.check_iter) == 0
            fprintf("%d   %.3e  %.2e\n", k, 0.5 * p.xi' * p.P * p.xi, norm(p.H * p.xi));
            primal_conv(end+1) = abs(norm((xiold-p.xi), Inf) - last_primal);
            dual_conv(end+1) = abs(norm((etaold-p.eta), Inf) - last_dual);
            last_primal = norm((xiold-p.xi), Inf);
            last_dual = norm((etaold-p.eta), Inf);

            stop = (norm((xiold-p.xi), Inf) <= opts.eps_abs + opts.eps_rel * max(norm(p.xi, Inf), norm(xiold, Inf)) ...
         && norm((etaold-p.eta), Inf) <= opts.eps_abs + opts.eps_rel * max(norm(p.eta, Inf), norm(etaold, Inf))) || ...
         k >= opts.max_iter;
        end
        k = k + 1;
    end
    Z = p.xi;
end