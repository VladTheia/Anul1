function [C] = FFT(m, y)
  [f, e] = log2(m)
  C = zeros(2*m,1)
  sum1 = 0;
  sum2 = 0;
  for k=1:m
    sum1 = 0;
    sum2 = 0;
    for j=1:m/2
      sum1 = sum1 + 2*y(2*j-1)*exp(i*pi*(k-1)*(j-1)/(m/4));
      sum2 = sum2 + 2*exp(i*pi*(k-1)/(m/2))*y(2*j)*exp(i*pi*(k-1)*(j-1)/(m/4))
    endfor
    C(k) = (sum1 + sum2)/2;
    C(k+m) = (sum1 - sum2)/2;
  endfor
endfunction