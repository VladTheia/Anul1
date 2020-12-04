v = [0 : 0.1 : 1]
fid = fopen('valori.txt', 'w');
for i = v
   fprinf(fid, "%f \n", 2*i + 1)
endfor
fclose(fid);