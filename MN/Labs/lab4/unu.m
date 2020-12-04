A = [5.2 7.1; 2.4 3.2];
b= [19.8; 4.1];
[A, b] = GPPS(A, b)
x = SST(A, b);
disp(x);