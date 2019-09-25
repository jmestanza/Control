close all
clc
% scoledata: lo que guarda simulink (scope -> ruedita -> logging)
v1sim = ScopeData.signals(1).values(103:1000,1);
v2sim = ScopeData.signals(2).values(103:1000,1);

% agrego la carpeta donde estan las mediciones al path
addpath('C:\Users\Marcelo\Documents\GitHub\Control\TP2\Mediciones');
f = csvread('faseEspiral.csv',2,0); % ignoro los primeros 2 renglones 
v1med = f(1:999,2);
v2med = f(1:999,5);

plot(v2sim, v1sim);
hold on;
plot(v1med, v2med);