function F = Trapez(fx, a, b)
  N = length(fx)-1;
  h = (b-a)/N;
  F = (h/2) * (fx(1) + fx(N+1) + 2*sum(fx(2:N)));
endfunction