#ifndef LISTE_H_
#define LISTE_H_

typedef struct nod {
	char* val;
	struct nod* next;
} Nod;

/** The type of linked list of char*
 * The empty list is represented by NULL
 * */
typedef Nod* List;


/** Adds a new element at the beginning of the list*/
List list_prepend(List l, char* val);

/** Deletes the specified string from the list.
 * Returns the new list.
 * TODO: needs implementation
 * */
List list_delete(List l, char* val);


List list_append(List l, char* val);
List list_free(List l);
List list_init(char* val);
int list_isEmpty(List l);
void list_print(List l);
int list_len(List l);

List list_make(int count, ...);


#endif /* LISTE_H_ */
