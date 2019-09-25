close all
clc
% scoledata: lo que guarda simulink (scope -> ruedita -> logging)
v1sim = ScopeData.signals(1).values(103:1000,1);
v2sim = ScopeData.signals(2).values(103:1000,1);

% agrego la carpeta donde estan las mediciones al path
addpath('C:\Users\Marcelo\Documents\GitHub\Control\TP2\Mediciones');
% addpath('C:\repositories\Control\TP2\Mediciones');
f = csvread('faseNormal.csv',2,0); % ignoro los primeros 2 renglones 
v1med = f(1:999,5);
v2med = f(1:999,6);

plot(v2sim, v1sim);
hold on;
plot(v1med, v2med);


titlestr = '';
xlabelstr = '$X_1$';
ylabelstr = '$X_2$';
legendstr = {'Simulaci\''on', 'Medici\''on'};
ax = gca;
title(titlestr, 'interpreter', 'latex');
set(ax,'TickLabelInterpreter','latex');
grid on;

xlabel(xlabelstr,'interpreter','latex');
ylabel(ylabelstr,'interpreter','latex');
lgd = legend(legendstr);
lgd.Interpreter = 'latex';
