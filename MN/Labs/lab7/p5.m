A=[1 5 10 14; 2 9 4 1;10 13 5 3;15 4 12 9]

max_iteration = 100;

n  = length(A);

x_old = [3; 5; 1; 8];
x_old /= norm(x_old);
x_new = zeros(length(A), 1);


for k = 2:max_iteration
    z = A * x_old;
    x_new = z / norm(z);
    lambda = x_new'*A*x_new;
    x_old = x_new;
endfor

x_old
lambda
[V, x] = eig(A);

V