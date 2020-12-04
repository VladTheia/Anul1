function y = Heun(a,b,n,y0,f)
  h = (b-a)/n;
  x(1:n+1) = a + (2 *h/3)*[0:n];
  y(1) = y0;


  for i = 1:n
    x(i+1) = x(i) + h;
    xi1 = x(i) + (2 * h) / 3;
    yi1 = y(i) + ((2 * h) / 3) * feval(f, x(i), y(i));
    y(i+1) = y(i) + (h/4) * feval(f, x(i), y(i)) + (3 * h / 4) * feval(f, xi1, yi1);
  endfor
endfunction