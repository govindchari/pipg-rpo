function plotall(X, U, p)
    t = 0:p.dt:p.T-p.dt;
    
    figure
    plot(X(2,:),X(1,:),'LineWidth',2)
    hold on
%     plot(0:140,(0:140)*tan(p.th_ac), 'LineWidth',2, 'Color','red')
%     plot(0:140,-(0:140)*tan(p.th_ac), 'LineWidth',2, 'Color','red')
    xlabel("Along Track [m]",'Interpreter','latex')
    ylabel("Radial [m]",'Interpreter','latex')
    title("Spacecraft Trajectory",'Interpreter','latex')
    grid on

    for i = 1 : p.N - 1
        unorm(i) = norm(U(:,i));
    end
    
    figure
    plot(t, U(:,1:p.N-1), 'LineWidth',2)
    hold on
    yline(p.umax,'--r','linewidth',2)
    yline(-p.umax,'--r','LineWidth',2)
    xlabel("Time [s]",'Interpreter','latex')
    ylabel("Control Input [$m s^-2$]",'Interpreter','latex')
    legend("$u_x$","$u_y$","$u_z$","$u_{max}$",'interpreter','latex','location','southeast')
    title("Control Input over Time", 'Interpreter','latex')
    grid on

    figure
    plot(t, unorm, 'LineWidth',2)
    hold on
    yline(p.umax,'--r','linewidth',2)
    xlabel("Time [s]",'Interpreter','latex')
    ylabel("Control Input [$m s^-2$]",'Interpreter','latex')
    legend("$u_{norm}$","$u_{max}$",'interpreter','latex','location','southeast')
    title("Control Input Norm over Time", 'Interpreter','latex')

    grid on

end