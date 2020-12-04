f1 = [1, 0, 0, 0, 0, 0, 0, -11];
f2 = [1, 0, 0, 0, 0, -0.85];

nthroot(11, 7)
nthroot(0.85, 5)

function p = bisection(f, a, b, tol)
    p = (a+b) / 2;
    err = abs(polyval(f, p));
    while err > tol
        if polyval(f, a) * polyval(f, p) < 0
            b = p;
        else
            a = p;
        endif
        p = (a + b) / 2;
        err = abs(polyval(f, p));
    endwhile
endfunction

bisection(f1, 0, 5, 1e-4)
bisection(f2, 0, 1, 1e-4)