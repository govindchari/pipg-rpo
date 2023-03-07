function [X, U] = unscale(X, U, params)
    for i = 1 : size(X, 2)
        X(:, i) = params.Px * X(:,i);
    end
    for i = 1 : size(U, 2)
        U(:, i) = params.Pu * U(:,i);
    end
end