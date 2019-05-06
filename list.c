#include "list.h"

list *mk_list() {
    list *l = (list*) malloc(sizeof(list));
    l->head = NULL;
    l->last = NULL;
    return l;
}

void free_list(list *l) {
    node *n = l->head;
    node *aux;
    while (n != NULL) {
        aux = n->next;
        free(n);
        n = aux;
    }
    free(l);
}

void add_last(list *l, Item cont) {
    node *new_last = (node*) malloc(sizeof(node));
    new_last->contact = cont;
    if (l->last != NULL) l->last->next = new_last;
    else l->head = new_last;
    new_last->previous = l->last;
    new_last->next = NULL;
    l->last = new_last;
}

/*
link delete(link head, char* text) {
    link t, prev;
    for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if (strcmp(t->text, text) == 0) {
            if (t == head) head = t->next;
            else prev->next = t->next;
            free(t->text);
            free(t);
        }
    }
    return head;
}
*/

void print_list(list *l) {
    node *aux;
    if (l == NULL) return;
    aux = l->head;
    while (aux != NULL) {
        visitItem(aux->contact);
        aux = aux->next;
    }
}
