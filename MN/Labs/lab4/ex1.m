 function x=ex1(A,b)
  [n,n]=size(A); 
  p = (1:n)';
  s = max(abs(A'));
  for k = 1:(n-1)
    r = abs(A(p(k),k)/s(p(k)));
    kp = k;
    for i = (k+1):n
      t = abs(A(p(i),k)/s(p(i))); 
      if t > r,  r = t;  kp = i;  end
    end
    l = p(kp);  p(kp) = p(k);  p(k) = l;
    for i = (k+1):n
      A(p(i),k) = A(p(i),k)/A(p(k),k);
      for j = (k+1):n
        A(p(i),j) = A(p(i),j)-A(p(i),k)*A(p(k),j);
      end
    end
  end
  p     
  A              

  y = zeros(n,1);    
  y(1) = b(p(1));
  for i = 2:n
    y(i) = b(p(i));
    for j = 1:(i-1)
      y(i) = y(i)-A(p(i),j)*y(j);
    end
  end
  y       

  x = zeros(n,1);   
  x(n) = y(n)/A(p(n),n);
  for i = (n-1):-1:1
    x(i) = y(i);
    for j = (i+1):n
      x(i) = x(i)-A(p(i),j)*x(j);
    end
    x(i) = x(i)/A(p(i),i);
  end                 