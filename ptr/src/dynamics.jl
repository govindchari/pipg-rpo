# Clohessy-Wiltshire Dynamics (x = [r v])
function f(x, u)
    return [x[4]; x[5]; x[6]; 3 * n^2 * x[1] + 2 * n * x[5]; -2 * n * x[4]; -n^2 * x[3]]
end
function dfx(x, u)
    A = [0 0 0 1 0 0;
        0 0 0 0 1 0;
        0 0 0 0 0 1;
        3*n^2 0 0 0 2*n 0;
        0 0 0 -2*n 0 0;
        0 0 -n^2 0 0 0]
    return A
end
function dfu(x, u)
    zeros(6, 3)
end