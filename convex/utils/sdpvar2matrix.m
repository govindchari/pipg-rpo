function X = sdpvar2matrix(x)
    N = size(x, 2);
    nv = size(value(x{1}),1);
    X = zeros(nv, N);
    for i = 1 : N
        X(:,i) = value(x{i});
    end
end