function G = rotor(A, p)
  G = eye(size(A,1));
  sin = -A(p+1,p)/sqrt(A(p+1,p)^2 + A(p,p)^2);
  cos = A(p,p)/sqrt(A(p+1,p)^2 + A(p,p)^2);
  G(p,p) = cos;
  G(p,p+1) = -sin;
  G(p+1,p) = sin;
  G(p+1,p+1) = cos;
endfunction