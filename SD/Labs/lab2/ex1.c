typedef struct Node {
    int value;
    struct Node *next;
} Node;

void add(Node **list, int value, int pos) {
    if((*list) == NULL) {
        printf("Lista goala\n");
        return;
    }
    if(pos < 0) {
        return;
    }
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->value = value;

    if(pos == 0) {
        tmp->next = (*list);
        (*list) = tmp;
        return;
    }

    int count = 1;
    Node *prev = (*list);
    Node *aux = (*list)->next;
    while (count != pos) {
        prev = aux;
        aux = aux->next;
        count ++;
    }

    prev->next = tmp;
    tmp->next = aux;
    aux->next = aux->next->next;
    return;
}

int main() {

}