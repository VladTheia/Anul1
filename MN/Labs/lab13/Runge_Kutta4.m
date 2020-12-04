function y = Runge_Kutta4(a, b, n, y0, f)
	h = (b-a)/n;	
	y(1) = y0;

	for i = 1 : n
		x = a+(i-1)*h;
		K1 = h*feval(f, x, y(i));
		K2 = h*feval(f, x+h/2, y(i)+K1/2);
		K3 = h*feval(f, x+h/2, y(i)+K2/2);
		K4 = h*feval(f, x+h, y(i)+K3);
		y(i+1) = y(i)+(K1+2*K2+2*K3+K4)/6;
 	endfor
endfunction


