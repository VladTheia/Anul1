function I = romberg(fx, a, b)
  lfx = length(fx);
  N = log2(lfx-1)+1;
  R = zeros(N,N);
  for i = 1 : N
    R(i,1) = Trapez(fx(1:2^(N-i):lfx), a, b);
  endfor

  pow4 = 1;
  for j = 2 : N
    pow4 = pow4*4;
    R(j:N,j) = (pow4*R(j:N) - R(j-1:N-1))/(pow4-1);
  endfor
  I = R(N,N);
endfunction