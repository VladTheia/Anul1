function [Q R] = QR(A)

	[n n] = size(A);
	G = eye(n);

	for k = 1 : n - 1
		for l = k + 1 : n
			r = sqrt(A(k, k)^2 + A(l, k)^2);
			c = A(k, k) / r;
			s = (-1) * A(l, k) / r;

			t = c * A(k, k : n) - s * A(l, k : n);
			A(l, k : n) = s * A(k, k : n) + c * A(l, k : n);
			A(k, k : n) = t;

			t = c * G(k, 1 : n) - s * G(l, 1 : n);
			G(l, 1 : n) = s * G(k, 1 : n) + c * G(l, 1 : n);
			G(k, 1 : n) = t;
		endfor
	endfor

	Q = G';
	R = A;

endfunction