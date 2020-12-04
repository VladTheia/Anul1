function [Q R] = Gram-Schmidt(A,w)
  [m, n] = size(A);
  Q = complex(zeros(m, n));
  R = complex(zeros(n, n));
  v = zeros(n, 1);
  
  for j = 1:n
    v = A(:,j);
    for i = 1:j-1
      R(i,j) = sum( v .* conj( Q(:,i) .* w) / 
      sum(Q(:, i) .* conj( Q(:,i) .* w);
      v = v - R(i, j) * Q(:, i);
    end
    R(j,j) = norm(v);
    Q(:,j) = v / R(j,j);
    end
endfunction
