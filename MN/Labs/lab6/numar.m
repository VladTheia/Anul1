function sol = numar(p);
p = [3, 0, 1, -2, 0, 0, 5];
nr=0;
real=0;
for i = 1:6
if( (p(i)>0 && p(i+1)<0) || (p(i)<0 && p(i+1)>0))
disp(p(i));
endif
endfor
real = nr;
p = [-3, 0, -1, 2, 0, 0, -5];
nr=0;
for i = 1:6
if( (p(i)>0 && p(i+1)<0) || (p(i)<0 && p(i+1)>0))
disp(p(i));
endif
endfor
disp('numarul de solutii negative:')
real=real+nr;
disp('numarul de solutii complexe:')
disp(sizeof(p)/8-1-real)
endfunction

