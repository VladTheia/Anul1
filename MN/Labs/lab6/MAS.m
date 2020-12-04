# MAS

f = [0.5, -2, 1]
tol = 1e-4;
a = 0;
b = 1;

function x = MAS(f, a, b, tol)
    z = zeros([1, length(f)]);
    z(length(z) - 1) = 1
    f2 = f + z
    
    err = Inf;
    x = (a+b) / 2; # initial guess
    while abs(err) > tol
        temp = x;
        x = polyval(f2, x);
        err= x - temp
    endwhile
    
endfunction

MAS(f, a, b, tol)