function y = sist_ec_dif_ord1_Euler(a,b,n,y0,f)
  h = (b-a)/n;
  %x(1:n+1) = a + h*[0:n];
  x(1) = a;
  y(1) = y0;


  for i = 1:n
    x(i+1) = x(i) + h;
    xi1 = x(i) + h;
    yi1 = y(i) + h * feval(f,x(i),y(i));
    y(i+1) = y(i) + (h/2) * (feval(f,x(i),y(i)) + feval(f,xi1,yi1));
  endfor
endfunction