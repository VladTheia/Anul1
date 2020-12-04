function yc = PC(a,b,n,alpha,f)
  yc = RungeKutta(a,b,4,alpha,f);
  h = (b-a)/n;
  x = a;
  for i = 5:n
    yp = y(i-1) + h/24*(55*f(x + (i-1)*h,y(i-1)) - 59*f(x + (i-2)*h,y(i-2)) + 37*f(x + (i-3)*h,y(i-3))); 
    
    yc(i) = y(i-1) + h/24*(9*f(x + i*h,yp) + 19*f(x + (i-1)*h,y(i-1)) - 5*f(x + (i-2)*h,y(i-2)) + f(x + (i-3)*h,y(i-3)));
    x  = x + i*h;
   endfor
   
   
endfunction
