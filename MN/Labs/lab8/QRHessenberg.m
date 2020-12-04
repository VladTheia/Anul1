

function QRHessenberg(A)
	
	[n n] = size(A);
	eps = 0.00001;
	
	dim = n;
	
	while ~ isZeros(A, 0.00001)

		littleA = [A(n-1, n-1), A(n-1, n); A(n, n-1), A(n, n)];
		v = eig(A);
		lambda1 = v(1);
		lambda2 = v(2);

		if lambda1 == lambda2
			sigma = lambda1;
		else
			if abs(A(n, n) - lambda1) < abs(A(n, n) - lambda2)
				sigma = lambda1;
			else
				sigma = lambda2;
			endif
		endif

		A = A - sigma * eye(n);
		[Q R] = givens(A);
		A = R * Q + sigma * eye(n)

	endwhile

    
	diag(A)
  %  disp(v)

endfunction





