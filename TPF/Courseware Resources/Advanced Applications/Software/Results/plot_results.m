clear;

% PITCH OPEN-LOOP
% load('rsp_ol_p.mat');
% load('rsp_ol_y.mat');
% load('rsp_ol_vm.mat');
% YAW OPEN-LOOP
% load('rsp_ol_yaw_p.mat');
% load('rsp_ol_yaw_y.mat');
% load('rsp_ol_yaw_vm.mat');
% LQR: PITCH
% load('rsp_cl_lqr_p.mat');
% load('rsp_cl_lqr_y.mat');
% load('rsp_cl_lqr_vm.mat');
% LQR: YAW
% load('rsp_cl_lqr_yaw_p.mat');
% load('rsp_cl_lqr_yaw_y.mat');
% load('rsp_cl_lqr_yaw_vm.mat');
% LQR+I: PITCH
% load('rsp_cl_lqr_i_p.mat');
% load('rsp_cl_lqr_i_y.mat');
% load('rsp_cl_lqr_i_vm.mat');
% LQR+I: YAW
load('rsp_cl_lqr_i_yaw_p.mat');
load('rsp_cl_lqr_i_yaw_y.mat');
load('rsp_cl_lqr_i_yaw_vm.mat');
% MDL VAL: PITCH
% load('rsp_mdl_val_p.mat');
% load('rsp_mdl_val_y.mat');
% load('rsp_mdl_val_vm.mat');
% MDL VAL: PITCH
% load('rsp_mdl_val_yaw_p.mat');
% load('rsp_mdl_val_yaw_y.mat');
% load('rsp_mdl_val_yaw_vm.mat');
%
plot_ol_or_cl = 1;
%
t = plot_time;
%
if plot_ol_or_cl  == 2
    
subplot(2,1,1);
plot(plot_time,q_heli_2d_open_l_theta__deg__1_,'r',plot_time,q_heli_2d_open_loo_psi__deg__1_,'b--')
legend('pitch (deg)', 'yaw (deg');
axis([0 30 -50 50]);
grid;
subplot(2,1,2);
plot(plot_time,q_heli_2d_open_Vm_actual__V__0_,'r',plot_time,q_heli_2d_open_Vm_actual__V__1_,'b--');
legend('pitch (V)', 'yaw (V)');
axis([0 30 -15 15]);
grid;

else

subplot(3,1,1);
plot(t,q_heli_2d_ff_lqr_theta__deg__0_,'g',t,q_heli_2d_ff_lqr_theta__deg__1_,'r-',t,q_heli_2d_ff_lqr_theta__deg__2_,'b--')
%legend('ref (deg)', 'measured (deg)', 'simulated (deg)');
ylabel('Pitch Angle')
axis([0 30 -15 15]);
grid;
subplot(3,1,2);
plot(t,q_heli_2d_ff_lqr_i_psi__deg__0_,'g',t,q_heli_2d_ff_lqr_i_psi__deg__1_,'r-',t,q_heli_2d_ff_lqr_i_psi__deg__2_,'b--')
%legend('ref (deg)', 'measured (deg)', 'simulated (deg)');
ylabel('Yaw Angle')
axis([0 30 -100 100]);
grid;
subplot(3,1,3);
plot(t,q_heli_2d_ff_l_Vm_actual__V__0_,'r',t,q_heli_2d_ff_l_Vm_actual__V__1_,'b--');
%legend('V_{m,p} (V)', 'V_{m,y} (V)');
ylabel('Input Voltage');
axis([0 30 -25 25]);
grid;

end
