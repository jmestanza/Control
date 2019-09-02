function [ k,num,den ] = getTFFormat( tf )
[num,den] = numden(tf);
[numpol,numfact] = secOrderFact()
%numc = coeffs(num,s); % conseguimos los a0 + a1 s + a2 s^2
%numc = fliplr(numc); % a2 s^2 + a1 s + a0 
%numfactor = numc(1);
%numc = numc/numfactor;
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here


end

