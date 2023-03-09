function [A,B,Q,R,umax,vmax] = prescale(p)
    % Scale H
    A = p.Px \ p.A*p.Px;
    B = p.Px \ p.B*p.Pu;

    % Scale P
    Q = p.Px'*p.Q*p.Px;
    R = p.Pu'*p.R*p.Pu;

    % Scale D
    vmax = p.vmax / p.Px(4,4);
    umax = p.umax / max(p.Pu(:));
end