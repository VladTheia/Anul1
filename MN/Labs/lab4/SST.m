function [y] = SST(A,b)

  [n,n]=size(A);

  x=[1:n];
  
  for i=n:-1:1
    s=0;
    for j=i+1:n
      s=s+A(i,j)*x(j);
    endfor
    x(i)=(b(i)-s)/A(i,i);
    
  endfor
  y=transpose(x);
  
endfunction