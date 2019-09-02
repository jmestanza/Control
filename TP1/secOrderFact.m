function [ pol_coeffs, factor ] = secOrderFact( secondOrderPol )
syms s;
pol_coeffs = coeffs(secondOrderPol,s); % conseguimos los a0 + a1 s + a2 s^2
factor = pol_coeffs(1); % conseguimos el a0
pol_coeffs = pol_coeffs/factor; % dividimos por a0
pol_coeffs = simplify(pol_coeffs);
pol_coeffs = fliplr(pol_coeffs);
end

