function I = simpsoncomp(N, a, b, f)
  h = (b - a) / N;
  s1 = 0;
  s2 = 0;
  for i = 1 : N / 2
    s1 = s1 + f(a + (2 * i - 1) * h);
  endfor
  for i = 1 : N / 2 - 1
    s2 = s2 + f(a + 2 * i * h);
  endfor
  I = h / 3 * (f(a) + f(b) + 4 * s1 + 2 * s2);
endfunction