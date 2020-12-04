function [Ak S] = cerinta3(image, k)
  A = imread(image);
  [m, n] = size(A);
  A = double(A);
  miu = zeros(m, 1);
  for i = 1:m
    for j = 1:n
      miu(i) = miu(i) + A(i,j);     
    endfor
    miu(i) = miu(i) / n;
  endfor
  for i = 1:m
    A(i, 1:n) = A(i, 1:n) - miu(i);
  endfor
  Z = A' /(sqrt(n -1));
  [U, S, V] = svd(Z);
  for i = 1:k
    W(:, i) = V(:, i);
  endfor
  Y = W' * A;
  Ak = W * Y + miu;
endfunction