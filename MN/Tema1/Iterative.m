% Vlad, Theia-Madalin, 314CC

function R = Iterative(nume, d, eps)
  output_precision(6);
  fileID = fopen(nume, 'r');
  N = fscanf(fileID, '%d', 1);
  A = zeros(N);
  %citirea fisierului
  for i = 1:N
    nr = fscanf(fileID, '%d', 1);
    L(i) = fscanf(fileID, '%d', 1);
    for j = 1:L(i)
      x = fscanf(fileID, '%d', 1);
      A(i, x) = 1;
    endfor
  endfor
  %scaderea cu 1 din L(i) pentru paginile i care au link catre ele insele
  for i = 1:N
    if A(i, i) == 1
      A(i, i) = 0;
      L(i) = L(i) - 1;
    endif
  endfor
  val1 = fscanf(fileID, '%f', 1);
  val2 = fscanf(fileID, '%f', 1);
  
  for i = 1:N
    l(i) = 1;  
  endfor
  l = l';
  
  for i = 1:N
    for j = 1:N
      if A(j,i) == 1
        M(i,j) = 1/L(j);
      endif
      if A(j,i) != 1
        M(i,j) = 0;
      endif
    endfor
  endfor
  
  R1 = 1/N * l;
  R2 = d*M*R1 + (1 - d)/N * l;
  while norm(R2 - R1) > eps
    R1 = R2;
    R2 = d*M*R1 + (1 - d)/N * l;
  endwhile
  
  R = R1;
endfunction