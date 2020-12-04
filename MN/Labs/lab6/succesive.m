f =[1,-2,5,-7]
tol = 1e-4
x0 = 0
function sol = succesive(f, x0, tol)
sol=0; 
 while(1)
    sol = (-x0^3+2*x0^2+7)/5;
    if(abs(sol-x0)<tol && polyval(f,sol)<tol)
      break;
    endif;
    x0 = sol;
  endwhile
  disp(sol);
end
sol = succesive(f, x0, tol)