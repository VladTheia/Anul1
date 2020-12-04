#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFSIZE 10000

typedef struct cursor {
    int linie;
    int coloana;
}* Cursor;

//Lista in care vom retine caracterele, impreuna cu pozitia lor
typedef struct list {
    char c;
    int linie;
    int coloana;
    struct list* next;
    struct list* prev;
}* List;

typedef struct listOfLists {
    List list;
    int linie;
    int coloana;
    struct listOfLists* next;
}* ListOfLists;

/*Stack de liste folosit pentru copierea unei liste dupa aplicarea unei
 comenzi asupra acesteia. Util pentru comenzile undo si redo.*/
typedef struct stack {
    ListOfLists top;
    int size;
}* Stack;

//Comenzi pentru manipularea stack-ului
Stack initStack(List list) {
    Stack new = (Stack)malloc(sizeof(struct stack));
    new->top = (ListOfLists)malloc(sizeof(struct listOfLists));
    new->top->list = list;
    new->top->linie = 1;
    new->top->coloana = 1;
    new->size = 1;
    return new;
}

Stack push(Stack stack, List list, Cursor cursor) {
    if (stack != NULL) {
        ListOfLists listOfLists = (ListOfLists)malloc(sizeof(struct listOfLists));
        listOfLists->list = list;
        listOfLists->linie = cursor->linie;
        listOfLists->coloana = cursor->coloana;
        listOfLists->next = stack->top;
        stack->top = listOfLists;
        (stack->size)++;
        return stack;
    }
    Stack new = initStack(list);
    return new;
}

Stack pop(Stack stack) {
    if (stack != NULL && stack->top != NULL) {
        ListOfLists tmp = stack->top;
        stack->top = stack->top->next;
        free(tmp);
    }
    (stack->size)--;
    return stack;
}

//Comenzi pentru manipularea listelor
List initList(char c) {
    List l;
    l = (List)malloc(sizeof(struct list));
    l->c = c;
    l->linie = 1;
    l->coloana = 1;
    l->next = NULL;
    l->prev = NULL;
    return l;
}

//Functie pentru a reseta pozitia fiecarui caracter dupa editarea listei
List refreshList(List list) {
    List temp = list;
    int lin = 1;
    int col = 1;
    if (list != NULL) {
        while (temp->next != NULL) {
            if (temp->c != '\n') {
                temp->coloana = col;
                temp->linie = lin;
                col++;
            } else {
                temp->linie = lin;
                temp->coloana = col;
                col = 1;
                lin++;
            }
            temp = temp->next;
        }
        if (temp->c != '\n') {
            temp->coloana = col;
            temp->linie = lin;
            col++;
        } else {
            temp->linie = lin;
            temp->coloana = col;
            col = 1;
            lin++;
        }
    }
    return list;
}

Cursor incrementCursor(Cursor cursor, char c) {
    if (c != '\n')
        (cursor->coloana)++;
    else {
        (cursor->linie)++;
        cursor->coloana = 1;
    }
    return cursor;
}

List addFirst(List l, char c) {
    List new = initList(c);
    if (l != NULL) {
        new->next = l;
        return new;
    }
    else
        return initList(c);
}

List addLast(List l, char C) {
    List temp;
    if (l != NULL) {
        temp = l;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        List new = initList(C);
        new->prev = temp;
        temp->next = new;
        return l;
    }
    else
        return initList(C);
}

List addItem(List l, Cursor cursor, char c) {
    if (cursor->coloana == 1 && cursor->linie == 1) {
        if (l != NULL)
            l = addFirst(l, c);
        else
            l = initList(c);
    }
    if (cursor->coloana == 1 && cursor->linie != 1) {
        List temp = l;
        while ((temp->linie != cursor->linie - 1 || temp->c != '\n') 
                && temp->next != NULL) {
            temp = temp->next;
        }
        if (temp->next == NULL) {
            l = addLast(l, c);
        }
        else {
            List new = initList(c);
            new->prev = temp;
            new->next = temp->next;
            temp->next = new;
        }
    }
    if (cursor->coloana != 1) {
        List temp = l;
        while ((temp->linie != cursor->linie || 
                temp->coloana != cursor->coloana - 1) && temp->next != NULL) {
                temp = temp->next;
        }
        if (temp->next == NULL) {
            l = addLast(l, c);
        }
        else {
            List new = initList(c);
            new->prev = temp;
            new->next = temp->next;
            temp->next = new;
        }
    }
    l = refreshList(l);
    cursor = incrementCursor(cursor, c);
    return l;
}

//Copierea listei in alta zona de memorie(util pentru undo si redo)
List copyList(List list) {
    List auxlist = NULL;
    if (list != NULL) {
        List temp = list;
        while (temp->next != NULL) {
            auxlist = addLast(auxlist, temp->c);
            temp = temp->next;
        }
        auxlist = addLast(auxlist, temp->c);
    }
    refreshList(auxlist);
    return auxlist;
}

//Plasarea fiecarui caracter in lista
List putStringInList(List list, Cursor cursor, char *text) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        list = addItem(list, cursor, text[i]);
        }
    return list;
}

Cursor gotoChar(Cursor cursor, int a, int b) {
    if (b != 0) {
        cursor->coloana = a;
        cursor->linie = b;
    } else {
        cursor->coloana = a;
    }
    return cursor;
}

List backspace(List list, Cursor cursor) {
    if (list != NULL) {
        //In acest caz nu se schimba lista
        if (cursor->linie == 1 && cursor->coloana == 1)
            return list;
        //In acest caz stergem newline-ul
        if (cursor->coloana == 1) {
            List temp = list;
            while ((temp->linie != (cursor->linie - 1) || temp->c != '\n')
                    && temp->next != NULL) {
                temp = temp->next;
            }
            if (temp->next == NULL) {
                (cursor->linie)--;
                cursor->coloana = temp->coloana;     
                temp->prev->next = NULL;
                free(temp);
            }
            else {
                List aux1 = temp->next;
                List aux2 = temp->prev;
                aux1->prev = aux2;
                aux2->next = aux1;
                cursor->linie = aux2->linie;
                cursor->coloana = aux2->coloana + 1;
                free(temp);
            }
            list = refreshList(list);
            return list;
        }
        //Am tratat acest caz separat deoarece primul element din lista nu are prev
        if (cursor->linie == 1 && cursor->coloana == 2) {
            cursor->coloana = 1;
            List temp = list;

            if (list->next == NULL) {
                return NULL;
            }
            else {
                list = list->next;
                list->prev = NULL;
                free(temp);
                list = refreshList(list);
                return list;
            }
        }
        if (cursor->coloana != 1) {
            List temp = list;
            while ((temp->linie != cursor->linie ||
                    temp->coloana != cursor->coloana - 1) 
                    && temp->next != NULL) {
                temp = temp->next;
            }
            if (temp->next == NULL) {
                temp->prev->next = NULL;
                free(temp);                
                (cursor->coloana)--;
            }
            else {
                List aux1 = temp->next;
                List aux2 = temp->prev;
                aux1->prev = aux2;
                aux2->next = aux1;
                free(temp);
                (cursor->coloana)--;
            }
            list = refreshList(list);
            return list;        
        }
    }
    return NULL;    
}

/*Pentru a nu creea o noua functie, mut cursorul in fata caracterului,
  apoi dau backspace*/
List delete(List list, Cursor cursor, int arg) {
    if (list != NULL) {
        List temp = list;
        while ((temp->linie != cursor->linie || temp->coloana != cursor->coloana)
                && temp->next != NULL) {
            temp = temp->next;
        }
        if (temp->next == NULL) {
            return list;
        }
        if (arg == 0) {
            if (temp->c == '\n') {
                if (cursor->linie > temp->linie) {
                    return list;
                } else {
                    (cursor->linie)++;
                    cursor->coloana = 1;
                    list = backspace(list, cursor);
                }
            } else {
                if (cursor->coloana > temp->coloana) {
                    return list;
                } else {
                    (cursor->coloana)++;
                    list = backspace(list, cursor);
                }
            }
        } else {
            while (arg) {
                temp = list;
                while ((temp->linie != cursor->linie || 
                        temp->coloana != cursor->coloana) && temp->next != NULL){
                    temp = temp->next;
                }
                if (temp->c == '\n') {
                    if (cursor->linie == temp->linie) {
                        (cursor->linie)++;
                        cursor->coloana = 1;
                        list = backspace(list, cursor);
                    }
                } else {
                    if (cursor->coloana == temp->coloana) {
                        (cursor->coloana)++;
                        list = backspace(list, cursor);
                    }
                }
                arg--;
            }
        }       
    }
    return list; 
}

List deleteLine(List list, int arg, Cursor cursor) {
    int linie = cursor->linie;
    int i;

    if (list != NULL) {
        List temp = list;
        if (arg != 0) {
            while ((temp->linie != arg || temp->c != '\n') 
            && temp->next != NULL) {
                temp = temp->next;
            }
            int k = temp->coloana;
            if (temp->c == '\n') {
                cursor = gotoChar(cursor, 1, arg + 1);
                for (i = 0; i < k; i++)
                    list = backspace(list, cursor);
            }
            else {
                cursor = gotoChar(cursor, k + 1, arg);
                for (i = 0; i < k; i++)
                    list = backspace(list, cursor);
            }
        } else {
            while ((temp->linie != linie || temp->c != '\n') 
                    && temp->next != NULL) {
                temp = temp->next;
            }
            int k = temp->coloana;
            if (temp->c == '\n') {
                cursor = gotoChar(cursor, 1, linie + 1);
                for (i = 0; i < k; i++)
                    list = backspace(list, cursor);
            } else {
                cursor = gotoChar(cursor, k + 1, linie);
                for (i = 0; i < k; i++)
                    list = backspace(list, cursor);
            }
        }
    }
    return list;
}

List repalce(List list, char *old, char *new);

void save(List list, char* fname) {
    FILE* f;
    f = fopen(fname, "w+");
    while (list != NULL) {
        fprintf(f, "%c", list->c);
        list = list->next;
    }
    fclose(f);
}

List citire(List list, Cursor cursor, char* fname) {
    char *text = calloc(50, sizeof(char));
    char *comanda = calloc(50, sizeof(char));
    char *buffer = calloc(MAXBUFSIZE, sizeof(char));
    char *param1 = calloc(MAXBUFSIZE, sizeof(char));
    char *param2 = calloc(MAXBUFSIZE, sizeof(char));
    int arg1, arg2;
    int counter = 0;
    Stack mainStack = initStack(list);
    Stack redoStack = initStack(list);

    while (strcmp(comanda, "q") != 0) {
        size_t com = sizeof(comanda);
        memset(comanda, 0, com);
        fgets(text, MAXBUFSIZE, stdin);
    
        if (strcmp("::i\n", text) != 0)
            list = putStringInList(list, cursor, text);
        else {
            List auxlist = copyList(list);
            mainStack = push(mainStack, auxlist, cursor);
    
            while (strcmp(comanda, "::i") != 0) {
                fgets(buffer, MAXBUFSIZE, stdin);
                buffer[strlen(buffer) - 1] = 0;
                sscanf(buffer, "%s %s %s", comanda, param1, param2);
                if (strcmp(comanda, "u") == 0) {
                    List redoList = copyList(mainStack->top->list);
                    redoStack = push(redoStack, redoList, cursor);
                    mainStack = pop(mainStack);
                    List mainCopy = copyList(mainStack->top->list);
                    list = mainCopy;
                    cursor->linie = mainStack->top->linie;
                    cursor->coloana = mainStack->top->coloana;
                    counter++;                  
                } else
                if (strcmp(comanda, "r") == 0) {
                    List mainList = copyList(redoStack->top->list);
                    cursor->linie = redoStack->top->linie;
                    cursor->coloana = redoStack->top->coloana;
                    mainStack = push(mainStack, mainList, cursor);
                    redoStack = pop(redoStack);
                    List mainCopy = copyList(mainStack->top->list);
                    list = mainCopy;
                    counter++;
                } else
                if (strcmp(comanda, "s") == 0) {
                    save(list, fname);
                } else 
                if (strcmp(comanda, "q") == 0) {
                    break;
                } else
                if (strcmp(comanda, "b") == 0) {
                    list = backspace(list, cursor);
                    List tmp1list = copyList(list);
                    mainStack = push(mainStack, tmp1list, cursor);
                    counter++;
                } else
                if (strcmp(comanda, "dl") == 0) {
                    arg1 = atoi(param1);
                    list = deleteLine(list, arg1, cursor);
                    List tmp2list = copyList(list);
                    mainStack = push(mainStack, tmp2list, cursor);
                    counter++;
                } else
                if (strcmp(comanda, "gl") == 0) {
                    arg1 = atoi(param1);
                    cursor = gotoChar(cursor, 1, arg1);
                    mainStack = push(mainStack, list, cursor);
                    counter++;
                } else 
                if (strcmp(comanda, "gc") == 0) {
                    arg1 = atoi(param1);
                    arg2 = atoi(param2);
                    cursor = gotoChar(cursor, arg1, arg2);
                    mainStack = push(mainStack, list, cursor);
                    counter++;
                } else 
                if (strcmp(comanda, "d") == 0) {
                    arg1 = atoi(param1);
                    list = delete(list, cursor, arg1);
                    List tmp3list = copyList(list);
                    mainStack = push(mainStack, tmp3list, cursor);
                    counter++;
                } else 
                if (strcmp(comanda, "re") == 0) {
                    //replace(param1,param2);
                }
                if (counter == 5) {
                    save(list, fname);
                    counter = 0;
                }

                size_t p1 = sizeof(param1);
                size_t p2 = sizeof(param2);
                memset(param1, 0, p1);
                memset(param2, 0, p2);
            }
        }
    }
    return list;
}

int main(int argc, char *argv[]) {
    Cursor cursor = (Cursor)malloc(sizeof(struct cursor));
    cursor->coloana = 1;
    cursor->linie = 1;
    List list = NULL;
    list = citire(list, cursor, argv[1]);
    return 0;
}