function [x] = prb4 (filename)
  fid = fopen(filename, 'r');
  i = 0
  while 1
    linie = fgetl(fid);
    if ~ischar(linie), break, end
    i = i +1
  endwhile
  fclose(fid)
  x = i
endfunction
%GRESIT