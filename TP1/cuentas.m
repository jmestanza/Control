clear all;
close all;
clc;
syms Ko;
syms Kd;
syms s;
syms R5;
syms R6;
syms R9;
syms C6;
syms C7;

% cuentas para el punto 2
w1 = 1/(R5*C6);
F1 = 1/(1+s/w1);  
VfOverTheta1 = (s*Kd*F1)/(s+Ko*Kd*F1);
[num,den] = numden(VfOverTheta1);
%VfT1 = num/den

w2 = 1/(R6*C6);
weq = 1/((R5+R6)*C6);
F2 = (1+s/w2)/(1+s/weq);
VfOverTheta2 = (s*Kd*F2)/(s+Ko*Kd*F2);
[num,den] = numden(VfOverTheta2);
%VfT2 = num/den

% cuentas para el punto 3
wo = 1/(R9*C7);
Fo = 1/(1+s/wo);

T1 = Ko/s;
T2 = VfOverTheta2;
T3 = Fo;

Ttot = T1*T2*T3;
[num,den] = numden(Ttot);
Ttot = num/den
