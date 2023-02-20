function [X,U] = pipg_solver(par, p)
    e = zeros(par.N + 1, 1);
    fprintf("iter     objv     |Gx-g|\n")
    fprintf("-----------------------------\n")
    Xold = 1e6 * ones(par.N + 1, par.nx);
    Uold = 1e6 * ones(par.N, par.nu);
    Wold = 1e6 * ones(par.N + 1, par.nx);
    eabs = 1e-5;
    erel = 1e-5;

    k = 1;
    [alpha, beta] = compute_stepsizes(p);
    [A,B,Q,R,umax] = prescale(par);

    while ~(norm((Xold(:)-p.X(:)), Inf) <= eabs + erel * max(norm(p.X(:), Inf), norm(Xold(:), Inf)) ...
         && norm((Uold(:)-p.U(:)), Inf) <= eabs + erel * max(norm(p.U(:), Inf), norm(Uold(:), Inf))...
         && norm((Wold(:)-p.W(:)), Inf) <= eabs + erel * max(norm(p.W(:), Inf), norm(Wold(:), Inf)))

        Uold = p.U;
        Xold = p.X;
        Wold = p.W;

        obj = 0;
        for t = 2:par.N+1
            p.V(t, :) = p.W(t, :)' + beta * (p.X(t, :)' - A * p.X(t-1, :)' - B * p.U(t-1, :)');
            p.U(t-1, :) = proj_ball(p.U(t-1, :)' - alpha * (R * p.U(t-1, :)' - B' * p.V(t, :)'), umax);
            if t ~= par.N + 1
                p.X(t, :) = p.X(t, :)' - alpha * (Q * (p.X(t, :)') + p.V(t, :)' - A' * p.V(t+1, :)');
            end
            p.W(t, :) = p.W(t, :)' + beta * (p.X(t, :)' - A * p.X(t-1, :)' - B * p.U(t-1, :)');
            e(t) = norm(p.X(t, :)' - A * p.X(t-1, :)' - B * p.U(t-1, :)')^2;
            obj = obj + p.X(t, :) * Q * p.X(t, :)' + p.U(t-1, :) * par.R * p.U(t-1, :)';
        end
        if mod(k, 50) == 0
            fprintf("%d   %.3e  %.2e\n", k, obj, sqrt(sum(e)));
        end
        k = k + 1;
%         norm((Xold(:)-p.X(:)), Inf) / (eabs + erel * max(norm(p.X(:), Inf), norm(Xold(:), Inf)))
%         norm((Uold(:)-p.U(:)), Inf) / (eabs + erel * max(norm(p.U(:), Inf), norm(Uold(:), Inf)))
%         norm((Wold(:)-p.W(:)), Inf) / (eabs + erel * max(norm(p.W(:), Inf), norm(Wold(:), Inf)))
    end
    X = p.X;
    U = p.U;
end