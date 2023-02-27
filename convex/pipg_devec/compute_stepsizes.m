function [alpha, beta] = compute_stepsizes(p)
    % Assumes P is diagonal
    HtH = sparse(p.H' * p.H);
    normP = max(diag(p.P));
    norm2H = max(eig(HtH));
    alpha = 2/(sqrt(normP^2+4*p.omega*norm2H)+normP);
    beta = p.omega * alpha;
end