clear all;
close all;
clc;
%----estos valores los cambiamos pero la frec del filtro es la misma
C7 = 1e-9; 
R9 = 560; 
%-------------------------

C6 = 1e-9; 
R6 = 0;
R5 = 10e3;
Ko = 1e6;
Vcc = 10;
Kd = 10 / pi;

% coef amortiguamiento con filtro 1er orden
xi = (C6*Kd*Ko*R6 + 1)/(2*C6^(1/2)*Kd^(1/2)*Ko^(1/2)*(R5 + R6)^(1/2));
% frecuencia natural de los polos complejos
wn = ((Kd*Ko)/(C6*(R5 + R6)))^(1/2);
s = tf('s');
sys = (Kd*Ko)/((C6*R5*s + 1)*(C7*R9*s + 1)*(s + (Kd*Ko)/(C6*R5*s + 1)));
step(sys);
stepinfo(sys)

