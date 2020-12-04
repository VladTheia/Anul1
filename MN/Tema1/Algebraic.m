% Vlad, Theia-Madalin, 314CC

function R = Algebraic(nume, d)
  output_precision(20);
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
  
  for i = 1:N
    if A(i, i) == 1
      A(i, i) = 0;
      L(i) = L(i) - 1;
    endif
  endfor
  val1 = fscanf(fileID, '%f', 1);
  val2 = fscanf(fileID, '%f', 1);
  fclose(fileID);
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
  
  I = eye(N);
  %obtinerea inversei
  B = GramSchmidt(I-d*M);
  R = B * (1-d) / N * l;
endfunction