function [y1 y2] = Runge_Kutta_4_pb5(a, b, n, y10, y20, f1, f2)
	h = (b-a)/n;	
	y1(1) = y10;
  y2(1) = y20;

	for i = 1 : n
		x = a+(i-1)*h;
		K1 = h*feval(f1, x, y1(i), y2(i));
    L1 = h*feval(f2, x, y1(i), y2(i));
    
		K2 = h*feval(f1, x+h/2, y1(i)+K1/2, y2(i)+L1/2);
    L2 = h*feval(f2, x+h/2, y1(i)+K1/2, y2(i)+L1/2);
    
		K3 = h*feval(f1, x+h/2, y1(i)+K2/2, y2(i)+L2/2);
    L3 = h*feval(f2, x+h/2, y1(i)+K2/2, y2(i)+L2/2);
    
		K4 = h*feval(f1, x+h, y1(i)+K3, y2(i)+L3);
    L4 = h*feval(f2, x+h, y1(i)+K3, y2(i)+L3);
    
		y1(i+1) = y1(i)+(K1+2*K2+2*K3+K4)/6;
		y2(i+1) = y2(i)+(L1+2*L2+2*L3+L4)/6;
 	endfor
  
endfunction