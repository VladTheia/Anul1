function x = SST(A, b)
  [n n] = size(A);
  x = zeros(n, 1);
  for i = n:-1:1
    S = A(i, i + 1:n) *x(i+1: n);
    x(i) = (b(i) -S)/A(i,i);
  endfor 
endfunction