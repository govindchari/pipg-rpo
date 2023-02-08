function plotall(X, U, p)
    t = 0:p.dt:p.T-p.dt;
    
    figure
    plot(X(2,:),X(1,:),'LineWidth',2)
    xlabel("Along Track [m]",'Interpreter','latex')
    ylabel("Radial [m]",'Interpreter','latex')
    title("Spacecraft Trajectory",'Interpreter','latex')
    grid on
    
    figure
    plot(t, U, 'LineWidth',2)
    hold on
    yline(p.umax,'--r','linewidth',2)
    yline(-p.umax,'--r','LineWidth',2)
    xlabel("Time [s]",'Interpreter','latex')
    ylabel("Control Input [$m s^-2$]",'Interpreter','latex')
    legend("$u_x$","$u_y$","$u_z$","$u_{max}$",'interpreter','latex','location','southeast')
    grid on
end