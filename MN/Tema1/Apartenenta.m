% Vlad, Theia-Madalin, 314CC

function y = Apartenenta(x, val1, val2)
  %a si b necesare pentru rezolvarea sistemului a*x + b = 0 si a*x + b = 1
  a = 1 / (val2 -val1);
  b = -val1 / (val2 - val1);
  if x >= 0 && x < val1
    y = 0;
  endif
  if x >= val1 && x <= val2
    y = a * x + b;
  endif
  if x > val2 && x <= 1
    y = 1;
  endif
endfunction