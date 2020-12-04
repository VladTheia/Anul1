function cerinta2()
  A_k = cerinta1('in/images/image1.gif', 25);
  A = imread('in/images/image1.gif');
  [m n] = size(A);
  [U, S, V] = svd(A);
  
  %1.
  figure;
  plot(diag(S));
  
  k = [1:19 20:20:99 100:30:200];
  info = zeros(1, 27);
  error = zeros(1, 27);
  rate = zeros(1, 27);
  
  %2.
  for j = 1:27
    s1 = 0;
    s2 = 0;
    for i = 1:k(j)
      s1 = s1 + S(i, i);
    endfor
    for i = 1:min(m,n)
      s2 = s2 + S(i, i);
    endfor
    info(j) = s1 / s2; 
  endfor
  figure;
  plot(k, info);
  
  %3.
  for h = 1:27
  s = 0;
  A_k = cerinta1('in/images/image1.gif', k(h));
  for i = 1:m
    for j = 1:n
      s = s + (A(i, j) - A_k(i, j))^2;      
    endfor
  endfor
  error(h) = s / (m * n);
  endfor
  figure;
  plot(k, error);
  
  %4.
  for i = 1:27
    rate(i) = (m * k(i) + n * k(i) + k(i)) / m * n;
  endfor
  figure;
  plot(k, rate);
endfunction