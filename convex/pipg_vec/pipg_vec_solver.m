function [Z,primal_conv,dual_conv] = pipg_vec_solver(par, p)
    function zproj = project_D(z, par, p)
        zproj = z;
        zproj(1:par.nx) = par.Px \ par.x0;
        zproj(( (par.N - 1) * par.nx) + 1 : par.N * par.nx) = par.Px \ par.xN;
%         for i = 1 : par.N
%             idx = par.N * par.nx + (i-1) * par.nu + 1 : par.N * par.nx + i * par.nu;
%             zproj(idx) = proj_ball(z(idx), p.umax);
%         end
    end
    fprintf("iter     objv     |Gx-g|\n")
    fprintf("-----------------------------\n")
    xiold = zeros(par.N * (par.nx + par.nu), 1);
    etaold = zeros((par.N - 1) * par.nx, 1);
    eabs = 1e-4;
    erel = 1e-4;
    primal_conv = [];
    dual_conv = [];
    last_primal = 100;
    last_dual = 100;
    k = 1;
    [alpha, beta] = compute_stepsizes(p);

%     while ~(norm((xiold-p.xi), Inf) <= eabs + erel * max(norm(p.xi, Inf), norm(xiold, Inf)) ...
%          && norm((etaold-p.eta), Inf) <= eabs + erel * max(norm(p.eta, Inf), norm(etaold, Inf)))
    while (1==1)

        xiold = p.xi;
        etaold = p.eta;

        if k>100000
            break
        end

        % Primal Update
        p.z = project_D(p.xi - alpha * (p.P * p.xi + p.H' * p.eta), par, p);

        % Dual Update
        p.w = p.eta + beta* (p.H * (2 * p.z - p.xi));

        % Extrapolation
        p.xi = (1 - p.rho) * p.xi + p.rho * p.z;
        p.eta = (1 - p.rho) * p.eta + p.rho * p.w;

        if mod(k, 50) == 0
            fprintf("%d   %.3e  %.2e\n", k, 0.5 * p.xi' * p.P * p.xi, norm(p.H * p.xi));
            primal_conv(end+1) = abs(norm((xiold-p.xi), Inf) - last_primal);
            dual_conv(end+1) = abs(norm((etaold-p.eta), Inf) - last_dual);
            last_primal = norm((xiold-p.xi), Inf);
            last_dual = norm((etaold-p.eta), Inf);
        end
        k = k + 1;
%         norm((Xold(:)-p.Xt(:)), Inf) / (eabs + erel * max(norm(p.Xt(:), Inf), norm(Xold(:), Inf)))
%         norm((Uold(:)-p.Ut(:)), Inf) / (eabs + erel * max(norm(p.Ut(:), Inf), norm(Uold(:), Inf)))
%         norm((Phiold(:)-p.Phit(:)), Inf) / (eabs + erel * max(norm(p.Phit(:), Inf), norm(Phiold(:), Inf)))
    end
    Z = p.xi;
end