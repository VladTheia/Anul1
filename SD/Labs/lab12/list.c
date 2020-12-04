#include <malloc.h>
#include <stdarg.h>
#include "list.h"
#include <string.h>

/** Deletes the specified string from the list.
 * Returns the new list.
 * TODO: needs implementation
 * */
List list_delete(List l, char* val) {
	if (l == NULL)
		return l;
	if (l->next == NULL && strcmp(l->val, val) == 0) 
		return list_free(l);
	List aux = l, to_delete;
	while (strcmp(l->next->val, val) != 0) {
		l = l->next;
		free(l->next->val);
		to_delete = l->next;
		l->next = l->next->next;
		free(to_delete);
	}
	return aux;
}

List list_prepend(List l, char* val) {
	List n = list_init(val);
	n->next = l;
	return n;
}

List list_make(int count, ...) {
	List l = NULL;
	int i = 0;
	va_list arguments;
	va_start( arguments, count );
	for (i = 0; i< count; ++i) {
		l = list_append(l, va_arg ( arguments, char*));
	}
	va_end(arguments);
	return l;

}

List list_append(List l, char* val) {
	if (l == NULL)
		return list_init(val);
	List it = l;
	while (it->next != NULL) {
		it = it-> next;
	}
	it -> next = list_init(val);
	return l;
}

List list_init(char* val) {
	List l  = (List) malloc(sizeof(Nod));
	l->next = NULL;
	l->val = val;
	return l;
}

int list_isEmpty(List l) {
	if (l == NULL)
		return 1;
	else
		return 0;
}

int list_len(List l) {
	int n = 0;
	while (l != NULL) {
		n++;
		l = l-> next;
	}
	return n;
}

void list_print(List l) {
	printf("(");
	while (l != NULL) {
		printf("%s, ", l->val);
		l = l-> next;
	}
	printf(")");
}

List list_free(List l) {
	List l1 = l;
	while (l != NULL) {
		l1 = l;
		l = l->next;
		free(l1);
	}
	return NULL;
}







