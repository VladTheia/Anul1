A = [1, 2, 0, 0, 0, 0, 0;
    3, -1, 3, 0, 0, 0, 0;
    0, 3, 2, 1, 0, 0, 0;
    0, 0, 1, 2, 1, 0, 0;
    0, 0, 0, 2, -1, 0, 0;
    0, 0, 0, 0, 3, 1, 0;
    0, 0, 0, 0, 0, -1, -3;
];


function P = poliOrtogonalGeneral(n, P0, P1, C1, C2, A)

  if n == 0
    P = P0;
  endif
  
  if n == 1
    P = P1;
  endif
  

  for i=2:n
    Paux1 = conv(P0, C1(i, A));
    Paux2 = conv(P1, C2(i, A));
    
    m = length(Paux1);
    n = length(Paux2);
    r = max(m, n);
    
    Paux1(r-m+1:r) = Paux1(1:m);
    Paux1(1:r-m) = zeros(1,r-m);

    Paux2(r-n+1:r) = Paux2(1:n);
    Paux2(1:r-n) = zeros(1,r-n);
    
    Paux = Paux1 + Paux2;
    
    P0 = P1;
    P1 = Paux;
  endfor
  
  P = P1;
endfunction



n = length(A);

P0 = [0, 1];
P1 = [1, -A(1, 1)];


function val =  C1_func(n, A)
    val = [1, -A(n, n)];
endfunction

function val = C2_func(n, A)
    val = [-A(n, n-1) * A(n-1, n)];
endfunction

C1 = @C2_func
C2 = @C1_func

P = poliOrtogonalGeneral(n, P0, P1, C1, C2, A)
roots(P)
[V, lambda] = eig(A)