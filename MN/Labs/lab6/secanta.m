f = [1, -2, 5, -7];
a = 1;
b = 2;
tol = 1e-4;

function a = secanta(f, a, b, tol)
    err = Inf;
    while abs(err) > tol
        temp = b;
        b = b - polyval(f, b) * (b - a) / (polyval(f, b) - polyval(f, a));
        a = temp;
        err = b - a;
    endwhile    
    
endfunction

secanta(f, a, b, tol)