function xproj = proj_ball(x, r)
    if norm(x) > r
        xproj = (r / norm(x)) * x;
    else
        xproj = x;
    end
end