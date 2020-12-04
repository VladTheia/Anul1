function [x] = newton(x0, f = @functie, J = @jacobiana, tol) 
N=100;
tol=0.00001;
x0=[2;1];
j = J(x0);
m = f(x0);
x = x0 - inv(j)*m;
c = x0;
while (norm(x-c) > tol)
j = J(x0);
m = f(x0);
x = x0 - inv(j)*m;
c = x0;
x0 = x;
endwhile
endfunction