function I = compTrapez(f, a, b, N)
  h = (b - a) / N;
  sum = 0;
  for i = 1 : N - 1
    sum = sum + f(a + i * h);
  endfor
  I = h / 2 * (f(a) + f(b) + 2 * sum);
endfunction