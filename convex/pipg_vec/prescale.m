function [A,B,Q,R,umax] = prescale(p)
    % Scale H
    A = p.Px \ p.A*p.Px;
    B = p.Px \ p.B*p.Pu;

    % Scale P
    Q = p.Px'*p.Q*p.Px;
    R = p.Pu'*p.R*p.Pu;

    % Scale D
    umax = p.umax / max(p.Pu(:));
end