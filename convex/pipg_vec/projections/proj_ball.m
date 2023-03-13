function x = proj_ball(x, r)
    if norm(x) > r
        x = (r / norm(x)) * x;
    end
end