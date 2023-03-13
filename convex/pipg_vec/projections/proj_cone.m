function x = proj_cone(c, g, u)
    if g*norm(c) <= dot(c,u)
        x = c;
    elseif sqrt(1-g^2)*norm(c) <= -dot(c,u)
        x = zeros(size(u,1),1);
    else
        y = g*u + sqrt(1-g^2)*(c-dot(c,u)*u)/norm((c-dot(c,u)*u));
        x = dot(c,y)*y;
    end
end