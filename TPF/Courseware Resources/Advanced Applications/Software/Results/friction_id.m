ID = 1 % YAW = 1, PITCH = 2

if ID == 1
    load('mu_id_psi_dot.mat');
    load('mu_id_vm.mat');
    varout = q_heli_2d_f_psi_dot__deg__s__0_;
    varin = [q_heli_2d_ff_l_Vm_actual__V__0_, q_heli_2d_ff_l_Vm_actual__V__1_];
else
    load('theta.mat');
    load('vm_pitch_test.mat');
    varout = q_heli_2d_ff_lqr_theta__deg__1_;
    varin = [q_heli_2d_ff_l_Vm_actual__V__0_, q_heli_2d_ff_l_Vm_actual__V__1_];    
end
%
t = plot_time(1:30000);
subplot(2,1,1)
plot(t, varout);
axis([0 30 -100 100])
ylabel('Yaw Rate (deg/s)')
grid;
subplot(2,1,2)
plot(plot_time, varin(:,1),'r-', plot_time, varin(:,2),'b-');
axis([0 30 -25 25])
ylabel('Input Voltage')
grid;
%
%
if ID == 1
    % Take average of the constant rotational speed from scope.
    psi_dot_cnst = mean(varout(1)) * pi / 180 % 14.5*pi/180;
    % Hover voltage of pitch.
    Vm_p = mean(q_heli_2d_ff_l_Vm_actual__V__0_)
    % Final yaw step voltage to reach constant speed
    Vm_y = max(q_heli_2d_ff_l_Vm_actual__V__1_)
    % Estimate the viscous friction of the bearing using the EOM.
    mu_y = (K_yy*Vm_y + K_yp*Vm_p ) / psi_dot_cnst
end