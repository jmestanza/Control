close all

% scoledata: lo que guarda simulink (scope -> ruedita -> logging)
tsim = ScopeData.time;
vosim = ScopeData.signals.values(:,2);
visim = ScopeData.signals.values(:,1);

% agrego la carpeta donde estan las mediciones al path
addpath('C:\repositories\Control\TP2\Mediciones');
f = csvread('escalon1.csv',2,0); % ignoro los primeros 2 renglones 
tmed = f(:,1);
vimed = f(:,2);
vomed = f(:,3);

medstart = find(vimed == 3.97, 1, 'first') - 1; % de mirar la medicion esto da
simstart = find(visim == 4, 1, 'first');

tsim = tsim(simstart:end);
tmed = tmed(medstart:end);

tsim = tsim - tsim(1);
tmed = tmed - tmed(1);

simend = find(tsim>=1, 1, 'first');
medend = find(tmed>=1, 1, 'first');

tsim = tsim(1:simend);
tmed = tmed(1:medend);

vosim = vosim(simstart:end);
vomed = vomed(medstart:end);
vosim = vosim(1:simend);
vomed = vomed(1:medend);


plot(tsim, vosim);
hold on;
plot(tmed, vomed);


titlestr = '';
xlabelstr = 'Tiempo (s)';
ylabelstr = 'Tensi\''on (V)';
legendstr = {'Simulaci\''on', 'Medici\''on'};
ax = gca;
title(titlestr, 'interpreter', 'latex');
set(ax,'TickLabelInterpreter','latex');
grid on;

xlabel(xlabelstr,'interpreter','latex');
ylabel(ylabelstr,'interpreter','latex');
lgd = legend(legendstr);
lgd.Interpreter = 'latex';
