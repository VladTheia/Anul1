function f = ecuatie(x)
  f = x^3 - 2*x^2 + 5*x -7;
endfunction

function d = deriv(x)
   d = 3*x^2-4*x+5;
endfunction

function sol = tangenta(a,f,deriv,tol)
  sol = a;
  i=0;
  while 1
    b = sol;
    sol = b - (f(b)/deriv(b));
    i = i + 1;
    if abs(sol-b) < tol
       return
    endif
  endwhile
endfunction

a=1;
tol=0.00001;
x = tangenta(a,@ecuatie,@deriv,tol)
