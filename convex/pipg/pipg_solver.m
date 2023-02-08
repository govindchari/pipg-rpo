function [X,U] = pipg_solver(par, p)
    function [alpha, beta] = compute_stepsizes(p)
        % Assumes P is diagonal
        normP = max(diag(p.P));
        norm2H = max(eig(p.HtH));
        alpha = 2/(sqrt(normP^2+4*p.omega*norm2H)+normP);
        beta = p.omega * alpha;
    end
    function xproj = proj_box(x, l, u)
        xproj = min(max(x, l), u);
    end
    function xproj = proj_ball(x, r)
        if norm(x) > r
            xproj = (r / norm(x)) * x;
        else
            xproj = x;
        end
    end

    e = zeros(par.N + 1);
    fprintf("iter     objv       |Gx-g|\n")
    fprintf("-----------------------------\n")
    Xold = 1e6 * ones(par.N + 1, par.nx);
    Uold = 1e6 * ones(par.N, par.nu);
    Wold = 1e6 * ones(par.N + 1, par.nx);
    eabs = 1e-3;
    erel = 1e-3;

    k = 1;
    [alpha, beta] = compute_stepsizes(p);
    while ~(norm((Xold(:)-p.X(:)), Inf) <= eabs + erel * max(norm(p.X(:), Inf), norm(Xold(:), Inf)) ...
         && norm((Uold(:)-p.U(:)), Inf) <= eabs + erel * max(norm(p.U(:), Inf), norm(Uold(:), Inf))...
         && norm((Wold(:)-p.W(:)), Inf) <= eabs + erel * max(norm(p.W(:), Inf), norm(Wold(:), Inf)))

        Uold = p.U;
        Xold = p.X;
        Wold = p.W;

        obj = 0;
        for t = 2:par.N+1
            p.V(t, :) = p.W(t, :)' + beta * (p.X(t, :)' - par.A * p.X(t-1, :)' - par.B * p.U(t-1, :)');
            p.U(t-1, :) = proj_ball(p.U(t-1, :)' - alpha * (par.R * p.U(t-1, :)' - par.B' * p.V(t, :)'), par.umax);
            if t ~= par.N + 1
                z = p.X(t, :)' - alpha * (par.Q * (p.X(t, :)') + p.V(t, :)' - par.A' * p.V(t+1, :)');
                p.X(t, :) = proj_box(z, [0;0;-Inf;-Inf;-Inf;-Inf], [Inf;Inf;Inf;Inf;Inf;Inf]);
            end
            p.W(t, :) = p.W(t, :)' + beta * (p.X(t, :)' - par.A * p.X(t-1, :)' - par.B * p.U(t-1, :)');
            e(t) = norm(p.X(t, :)' - par.A * p.X(t-1, :)' - par.B * p.U(t-1, :)')^2;
            obj = obj + p.X(t, :) * par.Q * p.X(t, :)' + p.U(t-1, :) * par.R * p.U(t-1, :)';
        end
%         if (mod(k, 50) == 0)
%             fprintf("%3d   %10.3e  %9.2e\n", k, obj, sqrt(sum(e)))
%         end
        k = k + 1;
        norm((Xold(:)-p.X(:)), Inf) / (eabs + erel * max(norm(p.X(:), Inf), norm(Xold(:), Inf)))
        norm((Uold(:)-p.U(:)), Inf) / (eabs + erel * max(norm(p.U(:), Inf), norm(Uold(:), Inf)))
        norm((Wold(:)-p.W(:)), Inf) / (eabs + erel * max(norm(p.W(:), Inf), norm(Wold(:), Inf)))
    end
    X = p.X;
    U = p.U;
end