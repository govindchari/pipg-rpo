function [X, U] = devec_sol(Z, par)
    X = Z(1 : par.N * par.nx);
    U = Z(par.N * par.nx + 1 : end);

    X = reshape(X, par.nx, par.N);
    U = reshape(U, par.nu, par.N);
end
