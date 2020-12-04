#include "hash.h"
#include "vector.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VECTOR_INITIAL_SIZE 10
int main(int argc, char **argv) {
    FILE *f;
    f = fopen("words.txt", "r");
    int i;
    char word[200], *buffer; 
    List l;
    Vector v = vec_init();

    for (i = 0; i < VECTOR_INITIAL_SIZE; i++)
        v = vec_add(v, NULL);
    for (i = 0; i < 100; i++) {
        fgets(word, 200, f);
        buffer = strdup(word);
        l = v->data[hash(word, v->size)]; 
        l = list_append(l, buffer);
        v = vec_set(v, hash(word, v->size), l);
    }
    vec_print(v);
    fclose(f);
    return 0;
}
