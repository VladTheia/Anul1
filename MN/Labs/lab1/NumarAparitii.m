function y = NumarAparitii(numefisier, sir)
  fid = fopen(numefisier);
  while 1
    line = fgetl(fid);
    ind = findstr(line, sir);
    if ~ischar(line), break, end
    disp(line(ind));
  endwhile
  fclose(fid);
endfunction