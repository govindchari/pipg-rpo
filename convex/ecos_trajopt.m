function [X, U, solve_time, parse_time, solve_status] = ecos_trajopt(p)
    [Ad,Bd,~,R,umax] = prescale(p);
    u = sdpvar(repmat(p.nu,1,p.N-1), ones(1,p.N-1));
    x = sdpvar(repmat(p.nx,1,p.N), ones(1,p.N));
    constraints = [x{1} == p.Px \ p.x0];
    constraints = [constraints, x{p.N} == p.Px \ p.xN];
    objective = 0;
    S = [1 0 0 0 0 0;0 0 1 0 0 0];
    c = [0 tan(p.th_ac) 0 0 0 0];
    for k = 1 : p.N-1
        objective = objective + u{k}'*R*u{k};
        constraints = [constraints, x{k+1} == Ad*x{k} + Bd*u{k}];
%         constraints = [constraints, norm(u{k},2) <= umax];
%         constraints = [constraints, norm(S*x{k}) <= p.leading * c*x{k}];
    end
    options = sdpsettings('solver', 'gurobi', 'verbose', 0, 'debug', 0);
    sol = optimize(constraints, objective, options);

    %%%%%%%%%%%%%%%%%%%%%%%%
    %%% Extract solution %%%
    %%%%%%%%%%%%%%%%%%%%%%%%
    U = sdpvar2matrix(u);
    X = sdpvar2matrix(x);

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Extract solve and parse times %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    solve_time = sol.solvertime*1000;
    parse_time = sol.yalmiptime*1000;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% Extract solve status %%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%

    switch sol.problem
    case 0
       solve_status = 'OPTIMAL';
    case {1,12,15}
       % 1 Infeasible problem
       % 12 Infeasible or unbounded
       % 15 Problem either infeasible or unbounded
       solve_status  = 'INFEASIBLE';
    case 3
       solve_status = 'MAX ITERS REACHED';
    case 4
       solve_status = 'NUMERICAL PROBLEMS';
    otherwise
        display(sol.problem);
        error('Unsupported exit flag.');
    end

end