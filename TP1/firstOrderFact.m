function [ pol_coeffs, factor ] = secOrderFact( secondOrderPol )
syms s;
pol_coeffs = coeffs(secondOrderPol,s); % conseguimos los a0 + a1 s
factor = pol_coeffs(2); % conseguimos el a1
pol_coeffs = pol_coeffs/factor; % dividimos por a1
pol_coeffs = simplify(pol_coeffs);
pol_coeffs = fliplr(pol_coeffs);
end


