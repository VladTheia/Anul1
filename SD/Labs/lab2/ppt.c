#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Student {
    char* nume;
    int id;
    int semestru;
    float nota;
} Student;

typedef struct Node {
    Student *student;
    struct Node next;
    struct Node prev;
} Lista;

typedef struct Database {
    int size;
    Node *table;
} Database;

//insert
//delete
//isEmpty
//printList
//search
void init(Database **database, char* filename) {
    (*database) = (Database*)malloc(sizeof(Database));
    (*database)->table = (Node*)malloc(sizoef(Node));
    FILE *fin = fopen(filename, "r");
    if(fin == NULL) {
        printf("Nu s-a deschis fisierul\n");
        return;
    }
    char8 id[3];
    char buffer[100];
    while (fgets(buffer, sizoef(buffer), fin) != NULL) {
        buffer[strlen(buffer) - 1] = 0;
        sscanf(buffer, "%s %s %s %s", id, nume, semestru, nota);
        stundent.id = atoi(id);
        student.nume = strdup(nume);
        student.semestru = atoi(semestru);
        student.nota = atof(nota);
    }
}

int main(int argc, char * argv[]) {


    return 0;
}
