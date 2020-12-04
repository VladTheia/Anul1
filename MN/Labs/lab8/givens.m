

function [Q R] = givens(A)
  n = size(A,1);
  Q = eye(n);
  R = Q;
  for j = 1:n-1
    if A(j+1,j) ~= 0
      G = rotor(A,j);
      Q = Q*G';
      R = G*A;
      A = R;
    end
  end
  
endfunction
[Q R] = givens(A);