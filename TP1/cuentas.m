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


[num,den] = numden(VfOverTheta2)

[numpol, numfactor] = secOrderFact(num);
[denpol, denfactor] = secOrderFact(den);
numpol(end+1) = 0; % habia un bug con una s que no aparecia (coeffs da lo mismo con
% s^2 + s que con s + 1)
Constant = simplify(numfactor/denfactor);

denpol;
wn = sqrt(1/(denpol(1)));
% 2 xi / wn =  denpol(2); entonces
xi = denpol(2)*wn/2;
xi = simplify(xi,'IgnoreAnalyticConstraints',true);

% cuentas para el punto 3
wo = 1/(R9*C7);
Fo = 1/(1+s/wo);

