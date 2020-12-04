function [lambda y iter]=PutereInv(A,y,lambda,maxIter,eps)
  
  n=size(A, 1);
  iter=maxIter;
  while maxIter > 0
    maxIter--;
    z=inv(A-lambda*eye(n))*y;
    y=z/norm(z);
    lambda=y'*A*y;
    
    if norm(A*y-lambda*y)<eps
      break
    endif
  endwhile
  iter=iter-maxIter
endfunction
A=[1 5 10 14; 2 9 4 1;10 13 5 3;15 4 12 9]
y=[3;5;1;8]
maxIter=100
eps=0.0001
lambda=7;
[lambda y iter]=PutereInv(A,y,lambda,maxIter,eps)