function plotall(X, U, p)
    t = 0:p.dt:p.T;
    tu = 0:p.dt:p.T-p.dt;

    r_cone = linspace(0,1000) ;
    th_cone = linspace(0,2*pi) ;
    [R_cone,Th_cone] = meshgrid(r_cone,th_cone) ;
    X_cone = R_cone;
    Y_cone = tan(p.th_ac)*R_cone .* cos(Th_cone);
    Z_cone = tan(p.th_ac)*R_cone .* sin(Th_cone);
    C_cone = zeros(100,100,3);
    th = deg2rad(90);
    DCM = [cos(th) -sin(th) 0;sin(th) cos(th) 0;0 0 1];
    for i = 1:100
        for j = 1:100
            x_cone = X_cone(i,j);
            y_cone = Y_cone(i,j);
            z_cone = Z_cone(i,j);
            rot_pos = DCM*[x_cone;y_cone;z_cone];
            X_cone(i,j) = rot_pos(1);
            Y_cone(i,j) = rot_pos(2);
            Z_cone(i,j) = rot_pos(3);
            C_cone(i,j,:) = [0.8,0.4,0.4]; 
        end
    end
    
    figure
    plot(X(2,:),X(1,:),'LineWidth',2)
    hold on
    surf(Y_cone,X_cone,Z_cone,C_cone,'EdgeColor','none','FaceColor','flat','FaceAlpha',0.3)
    xlabel("Along Track [m]",'Interpreter','latex')
    ylabel("Radial [m]",'Interpreter','latex')
    legend("Trajectory", "Approach Cone")
    title("Spacecraft Trajectory",'Interpreter','latex')
    grid on
    axis equal

    figure
    plot3(X(1,:),X(2,:),X(3,:),'LineWidth',2)
    hold on
    surf(X_cone,Y_cone,Z_cone,C_cone,'EdgeColor','none','FaceColor','flat','FaceAlpha',0.3)

    ylabel("Along Track [m]",'Interpreter','latex')
    xlabel("Radial [m]",'Interpreter','latex')
    zlabel("Cross Track [m]",'Interpreter','latex')
    legend("Trajectory", "Approach Cone")
    title("Spacecraft Trajectory",'Interpreter','latex')
    grid on
    axis equal

    figure
    plot(t, X(4:6,:), 'LineWidth',2)
    hold on
    yline(p.vmax,'--r','linewidth',2)
    yline(-p.vmax,'--r','LineWidth',2)
    xlabel("Time [s]",'Interpreter','latex')
    ylabel("Velocity [$m s^-2$]",'Interpreter','latex')
    legend("$v_x$","$v_y$","$v_z$","$v_{max}$",'interpreter','latex','location','southeast')
    title("Velocity over Time", 'Interpreter','latex')
    grid on

    for i = 1 : p.N
        vnorm(i) = norm(X(4:6,i));
    end

    for i = 1 : p.N - 1
        unorm(i) = norm(U(:,i));
    end

    figure
    plot(t, vnorm, 'LineWidth',2)
    hold on
    yline(p.vmax,'--r','linewidth',2)
    xlabel("Time [s]",'Interpreter','latex')
    ylabel("Speed [$m s^-2$]",'Interpreter','latex')
    legend("$v_{norm}$","$u_{max}$",'interpreter','latex','location','southeast')
    title("Speed over Time", 'Interpreter','latex')
    grid on

    
    figure
    plot(tu, U(:,1:p.N-1), 'LineWidth',2)
    hold on
    yline(p.umax,'--r','linewidth',2)
    yline(-p.umax,'--r','LineWidth',2)
    xlabel("Time [s]",'Interpreter','latex')
    ylabel("Control Input [$m s^-2$]",'Interpreter','latex')
    legend("$u_x$","$u_y$","$u_z$","$u_{max}$",'interpreter','latex','location','southeast')
    title("Control Input over Time", 'Interpreter','latex')
    grid on

    figure
    plot(tu, unorm, 'LineWidth',2)
    hold on
    yline(p.umax,'--r','linewidth',2)
    xlabel("Time [s]",'Interpreter','latex')
    ylabel("Control Input [$m s^-2$]",'Interpreter','latex')
    legend("$u_{norm}$","$u_{max}$",'interpreter','latex','location','southeast')
    title("Control Input Norm over Time", 'Interpreter','latex')
    grid on

end