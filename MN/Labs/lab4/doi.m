A = [1 2 3; 2 3 4; 0 5 6];
b = [6; 9; 11];
[A, b] = H_GPP(A, b);

disp(A);
printf('\n');

disp(b);
printf('\n');

x = SST(A, b);

disp(x);
printf('\n');

A = [1 2 3; 2 3 4; 0 5 6];
b = [6; 9; 11];
[A, b] = H_GPT(A, b);

disp(A);
printf('\n');

disp(b);
printf('\n');

A = [1 2 3; 2 3 4; 0 5 6];
b = [6; 9; 11];
[A, b] = H_GPT(A, b);

disp(A);
printf('\n');

disp(b);
printf('\n');