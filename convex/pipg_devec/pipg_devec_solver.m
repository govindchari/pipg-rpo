function [X,U,primal_conv,dual_conv, X_conv_gurobi, U_conv_gurobi] = pipg_devec_solver(par, p)
    e = zeros(par.N, 1);
    fprintf("iter     objv     |Gx-g|\n")
    fprintf("-----------------------------\n")
    Xold = 1e6 * ones(par.N, par.nx);
    Uold = 1e6 * ones(par.N-1, par.nu);
    Phiold = 1e6 * ones(par.N, par.nx);
    eabs = 1e-4;
    erel = 1e-4;
    primal_conv = [];
    dual_conv = [];
    X_conv_gurobi = [];
    U_conv_gurobi = [];
    last_primal = 100;
    last_dual = 100;
    k = 1;
    [alpha, beta] = compute_stepsizes(p);
    [A,B,Q,R,umax] = prescale(par);

    while ~(norm((Xold(:)-p.Xt(:)), Inf) <= eabs + erel * max(norm(p.Xt(:), Inf), norm(Xold(:), Inf)) ...
         && norm((Uold(:)-p.Ut(:)), Inf) <= eabs + erel * max(norm(p.Ut(:), Inf), norm(Uold(:), Inf))...
         && norm((Phiold(:)-p.Phi(:)), Inf) <= eabs + erel * max(norm(p.Phit(:), Inf), norm(Phiold(:), Inf)))

        Uold = p.Ut;
        Xold = p.Xt;
        Phiold = p.Phit;

        obj = 0;

        if k>500
            break
        end

        % Primal Update
        p.X(1, :) = par.Px \ par.x0;
        p.U(1, :) = proj_ball(p.Ut(1, :)' - alpha * (R * p.Ut(1, :)' + B' * p.Phit(1, :)'), umax);
        for t = 2:par.N-1
            p.X(t, :) = p.Xt(t, :)' - alpha * (Q * p.Xt(t, :)' + A' * p.Phit(t, :)' - p.Phit(t-1, :)');
            p.U(t, :) = proj_ball(p.Ut(t, :)' - alpha * (R * p.Ut(t, :)' + B' * p.Phit(t, :)'), umax);

            e(t) = norm(p.X(t, :)' - A * p.X(t-1, :)' - B * p.U(t-1, :)')^2;
            obj = obj + p.X(t, :) * Q * p.X(t, :)' + p.U(t-1, :) * par.R * p.U(t-1, :)';
        end
        p.X(par.N, :) = par.Px \ par.xN;
        p.U(par.N, :) = p.U(par.N-1, :);

        % Dual Update
        for t = 1:par.N-1
            p.Phi(t, :) = p.Phit(t, :)' + beta * (-2*p.X(t+1, :)' + p.Xt(t+1, :)' + A * (2*p.X(t, :)' ...
            - p.Xt(t, :)') + B * (2*p.U(t, :)' - p.Ut(t, :)'));
        end

        % Extrapolation
        p.Xt = (1 - p.rho) * p.Xt + p.rho * p.X;
        p.Ut = (1 - p.rho) * p.Ut + p.rho * p.U;
        p.Phit = (1 - p.rho) * p.Phit + p.rho * p.Phi;

        if mod(k, 50) == 0
            fprintf("%d   %.3e  %.2e\n", k, obj, sqrt(sum(e)));
            primal_conv(end+1) = abs(max(norm((Xold(:)-p.X(:)), Inf), norm((Uold(:)-p.U(:)), Inf) ) - last_primal);
%             X_conv_gurobi(end+1) = norm(p.Xt(:)-p.Xg(:))/norm(p.Xg);
%             z = p.Ut(1:par.N-1,:);
%             U_conv_gurobi(end+1) = norm(z(:)-p.Ug(:))/norm(p.Ug);

            dual_conv(end+1) = abs(norm((Phiold(:)-p.Phi(:)), Inf) - last_dual);
            last_primal = max(norm((Xold(:)-p.X(:)), Inf), norm((Uold(:)-p.U(:)), Inf) );
            last_dual = norm((Phiold(:)-p.Phit(:)), Inf);
        end
        k = k + 1;
%         norm((Xold(:)-p.Xt(:)), Inf) / (eabs + erel * max(norm(p.Xt(:), Inf), norm(Xold(:), Inf)))
%         norm((Uold(:)-p.Ut(:)), Inf) / (eabs + erel * max(norm(p.Ut(:), Inf), norm(Uold(:), Inf)))
%         norm((Phiold(:)-p.Phit(:)), Inf) / (eabs + erel * max(norm(p.Phit(:), Inf), norm(Phiold(:), Inf)))
    end
    X = p.Xt;
    U = p.Ut;
end