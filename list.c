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

node *search_node(list *l, Item cont) {
    node *aux;
    if (l == NULL || cont == NULL) return NULL;
    aux = l->head;
    while (aux != NULL) {
        if (aux->contact == cont) return aux;
        aux = aux->next;
    }
    return NULL;
}

list *free_node(list *l, Item cont) {
    node *n = search_node(l, cont);
    if (l->head == NULL || n == NULL) return l;
    if (l->head->contact == cont) l->head = l->head->next;
    if (l->last->contact == cont) l->last = l->last->previous;
    if (n->next != NULL) n->next->previous = n->previous;
    if (n->previous != NULL) n->previous->next = n->next;
    free(n);
    return l;
} 

void print_list(list *l) {
    node *aux;
    if (l == NULL) return;
    aux = l->head;
    while (aux != NULL) {
        visitItem(aux->contact);
        aux = aux->next;
    }
}
