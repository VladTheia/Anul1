function rez = ex1(func, a, b, N)
  step = (b-a)/2^(N-1);
  xi = a:step:b;
  fxi = func(xi);
  rez = romberg(fxi, a, b);
endfunction