function sol = aproximare(xi,g,tol)
  sol=g(xi);
  a = xi;
  while(abs(sol-a) > tol)
    a = sol;
    sol = g(a);
  endwhile
endfunction