
x = -1:0.1:1;
f1 = x.^3 + 4*x.^2 - 10;
plot(f1, x);

ec1 = x.^2;
ec2 = sqrt(1 - x.^2)


plot(x, ec1, '', x, ec2, '');