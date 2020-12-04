function sol = ten(a, b, f, d,tol)
p=[1; -2; 5; -7];
a=1; b=2; tol=0.00001;
m = 4;
while(abs(f(m))) > tol
m = m - f(m)/d(m);
endwhile
sol = m;
endfunction