function plot_double_integrator(X, U, p)
    tx = 0:p.dt:p.T;
    tu = 0:p.dt:p.T-p.dt;
   
    figure
    plot(tx, X(1,:),'LineWidth',2)
    xlabel("Time [s]",'Interpreter','latex')
    ylabel("Position [m]",'Interpreter','latex')
    title("Position vs Time",'Interpreter','latex')
    grid on
    
    figure
    plot(tu, U(1:p.N-1), 'LineWidth',2)
    hold on
    yline(p.umax,'--r','linewidth',2)
    yline(-p.umax,'--r','LineWidth',2)
    xlabel("Time [s]",'Interpreter','latex')
    ylabel("Control Input [$m s^-2$]",'Interpreter','latex')
    legend("$u$","$u_{max}$",'interpreter','latex','location','southeast')
    title("Control vs Time",'Interpreter','latex')
    grid on
end