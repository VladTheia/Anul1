Vlad Theia Madalin
Grupa 314CC

Pentru realizarea acestei teme am folosit 4 structuri. Structura "Cursor" 
reprezinta un cursor imaginar, avand componente intregii "linie" si "coloana".
Structura "List" este o lista dubla inlantuita. In fiecare nod al listei 
pastram cate un caracter din input, alaturi de pozitia sa (data de linie 
si coloana). Structura "ListOfLists" este o lista de liste, utilizata pentru 
a creea un stack de liste, folosit la implementarea comenzilor "undo" si 
"redo". Pentru a modifica stack-ul am folosit comenzile clasice de manipulare 
a acestuia: initStack, Push si Pop. Pentru modificare listei am folosit 
functiile clasice, la care am adaugat conditii pentru a adauga corect pozitia 
fiecarui caracter. Intrucat la aproape toate comenzile lista se schimba, avem 
nevoie de functia "refreshList" care parcurge lista si modifica linia si 
coloana fiecarui caracter astfel incat sa respecte implementarea abordata.
Functia "copyList" este necesara pentru "undo" si "redo". Aceasta face copii 
ale liste principale in alta zona de memorie. Aceasta functie este utilizata 
dupa fiecare modificare a listei, punand copia in stack-ul principal. Cand 
executam comanda "undo" punem top-ul stack-ului principal in stack-ul de 
redo si eliberam top-ul stack-ului principal. La executia comenzii "redo"
punem top-ul stack-ului de redo in stack-ul principal si apoi il eliberam.
Functia "putStringInList" pune fiecare caracter din string-ul primit ca 
input lista. Functia "backspace" trateaza diferite cazuri, in functie de 
unde se afla cursorul. Functiile "delete" si "delete line" se folosesc de
functia "backspace". Functia "save" trece prin toata lista si afiseaza
in fisierul dat ca argument fiecare caracter din lista. Functia "citire" 
este cea mai importanta din program. Aici are loc citirea inputului, schimbarea
din modul de input in cel de comanda si apelarea functiilor in functie de
comanda intalnita.