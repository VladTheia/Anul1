function A_k = cerinta1(image, k)
  M = imread(image);
  [U, S, V] = svd(M);
  V = V';
  A_k = U(:, 1:k) * S(1:k, 1:k) * V(1:k, :);
endfunction