% Vlad Theia Madalin, 314CC

Tema 1 MN - PageRank

Functia PageRank realizeaza citirea din fisierul primit ca parametru. Apeleaza
functiile Iterative si Algebraic pentru obtinerea lui R1 si R2, folosind 
argumentele primite. Folosim functia "sort", impreuna cu argumentul "descend" 
pentru a sorta vectorul si folosim si vectorul A pentru a scrie indexul 
unui vector, apoi elementul corespunzator acestuia. In final, apelam functia
Apartenenta pentru elementele din R2 si printam rezultatul.

Functiile Iterative si Algebraic realizeaza din nou citirea fisierului si
respecta formula ce foloseste forma matriceala. Stim ca A(i, i) = 0, asa ca
pentru paginile i care au link catre ele insele, L(i) scade cu 1.
Functia Apartenenta foloseste a si b potrivite pentru rezolvarea sistemului
a*x + b = 0 si a*x + b = 1, apoi urmam pasii din descrierea temei.