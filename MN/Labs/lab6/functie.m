function f = functie(x)
f = zeros(2,1);
f1 = x(1)^2 + x(2)^2 - 50;
f2 = x(1)*x(2) - 25;
f = [f1; f2];
endfunction