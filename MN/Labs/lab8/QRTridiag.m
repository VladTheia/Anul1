function QRTridiag(A)
	
	[n n] = size(A);
	eps = 0.00001;
	
	dim = n;
	sum = 0;
	
	while dim > 2

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

		sum += sigma;
		A = A - sigma * eye(dim);
		[Q R] = givens(A);
		A = R * Q + sigma*eye(dim);

		if abs(A(2, 1)) < eps
			A(1, 1) += sum;
			disp(A(1,1));
			A = A(2 : n, 2 :n);
		else
			if abs(A(n, n-1)) < eps
				A(n, n) += sum;
				disp (A(n, n));
				A = A(1 : n-1, 1 : n-1);
			endif
		endif

		dim = size(A);
		n = dim;

	endwhile


	w = eig(A);
	w += sum;
	disp(w);

endfunction





