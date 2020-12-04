
x = [0, 0];

function F = func(x)
    F(1, 1) = x(1).^2 + x(2).^2 -50;
    F(2, 1) = x(1) - x(2).^2 -25;
endfunction

function J = jacobian(f, x)
    J(1, 1) = 2*x(1);
    J(1, 2) = 2*x(2);
    J(2, 1) = -2*x(1);
    J(2, 2) = 1;
    
endfunction


function p = solve(f, n, tol)
    
    err = Inf
    
    x = ones([1, n])
    while abs(err) > tol
        temp = x;
        x = x - inv(jacobian(f, x)) * f(x);
        err = x - temp
    endwhile
    
endfunction


solve(@func, 10, 1e-4)