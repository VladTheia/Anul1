
function [ready] = isZeros(A, tol)
	[n n] = size(A);

	ready = 1;
    for i = 1:n
      for j = 1:i-1
        if abs(A(i,j)) > tol
          ready = 0;
          return;
        end
      end
    end

end
