% Vlad, Theia-Madalin, 314CC

function B = GramSchmidt(A)
	[m,n]=size(A);
	R=zeros(m,n);
	Q=eye(m);
	%fata de algoritmul obisnuit, acesta este mai stabil numeric si calculeaza
  %matricea R pe linii
  for k=1:n
    R(k,k) = norm(A(:,k));
    Q(:,k) = A(:,k)/R(k,k);
    R(k,k+1:n) = Q(:,k)'*A(:,k+1:n);
    A(:,k+1:n) = A(:,k+1:n) - Q(:,k)*R(k,k+1:n);
  endfor
  B = linsolve(R, Q');
endfunction