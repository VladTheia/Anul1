f = [1, -2, 5, -7];
a = 1;
b = 2;
tol = 1e-4;

function sol = bisectie(a,b,f,tol)
    sol  = (a + b)/2;
    err = abs(f(sol));
    while err > tol
      if f(a)*f(sol) < 0
        b = sol;
      else
        a = sol;
      endif
    sol = (a + b)/2;
    err = abs(f(sol));
  endwhile
endfunction

bisectie(a, b, @ecuatie, tol)