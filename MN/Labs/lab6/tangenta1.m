function sol = tangenta1(a,f,deriv,tol)
  sol = a;
  i=0;
  while 1
    b = sol;
    sol = b - (f(b)/deriv(b));
    i = i + 1
    if abs(sol-b) < tol
       return
    endif
  endwhile
endfunction
