% Vlad, Theia-Madalin, 314CC

function [R1 R2] = PageRank(nume, d, eps)
	% Calculeaza indicii PageRank pentru cele 3 cerinte
	%citirea din fisierul nume
  fileID = fopen(nume, 'r');
  N = fscanf(fileID, '%d', 1);
  for i = 1:N
    nr = fscanf(fileID, '%d', 1);
    L(i) = fscanf(fileID, '%d', 1);
    for j = 1:L(i)
      x = fscanf(fileID, '%d', 1);
    endfor
  endfor
  val1 = fscanf(fileID, '%f', 1);
  val2 = fscanf(fileID, '%f', 1);
  fclose(fileID);
  %scrierea in fiserul cu numele fisierului de input concatenat cu 
  %stringul ".out"  
  fileID = fopen(strcat(nume,".out"), 'w');
  fprintf(fileID, "%d\n\n", N);
  R1 = Iterative(nume, d, eps);
  fprintf(fileID, "%.6f\n", R1);
  fprintf(fileID, "\n");
  R2 = Algebraic(nume, d);
  fprintf(fileID, "%.6f\n", R2);
  fprintf(fileID, "\n");
  %sortarea descendenta a lui R2
  A = sort(R2, "descend");
  for i = 1:N
    fprintf(fileID, "%d ", i);
    for j = 1:N
      if A(i) == R2(j)
        fprintf(fileID, "%d ", j);
        break;
      endif
    endfor
    fprintf(fileID, "%.6f\n", Apartenenta(A(i), val1, val2));
  endfor
  
  fclose(fileID);
endfunction