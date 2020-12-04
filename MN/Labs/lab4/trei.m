a = [0 0 1 1 1 1];
b = [1 1 3 3 1 1];
c = [1 1 1 1 0 0];
d = [1 1 1 1 1 1];
n = size(d);
A = zeros(n);

for i = 1:2
  A(i,i) = b(i);
end

for i = 3:n
  A(i, i-2) = a(i-2);
  A(i,i) = b(i);
  A(i-2, i) = c(i-2);
end

Thomas(a, b, c, d)