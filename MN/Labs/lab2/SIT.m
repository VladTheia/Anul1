function x = SIT(A, b)
  [n n] = size(A);
  x = zeros(n, 1);
  for i = 1:n
    S = A(i, 1:i-1) *x(1:i-1);
    x(i) = (b(i) -S)/A(i,i);
  endfor 
endfunction