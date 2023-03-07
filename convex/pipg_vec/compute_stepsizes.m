function [alpha, beta] = compute_stepsizes(p, opts)
    % Assumes P is diagonal
    normP = full(max(diag(p.P)));
    norm2H = power_iteration(p.H, p.Ht, opts);
    alpha = 2 / (sqrt(normP^2 + 4*opts.omega*norm2H) + normP);
    beta = opts.omega * alpha;
end