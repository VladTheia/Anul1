f = [1, -2, 5, -7]
tol = 1e-4;

a = 1;
b = 2;


function p = bisection(f, a, b, tol)
    p = (a+b) / 2;
    err = abs(polyval(f, p));
    while err > tol
        if polyval(f, a) * polyval(f, p) < 0
            b = p;
        else
            a = p
        endif
        p = (a + b) / 2;
        err = abs(polyval(f, p));
    endwhile
endfunction

bisection(f, a, b, tol)