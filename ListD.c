#include "ListD.h"

Email newDomain(char *domain) {
    Email x = (Email) malloc(sizeof(struct email));
    x->domain = (char*) malloc(strlen(domain) + 1);
    strcpy(x->domain, domain);
    x->n = 1;
    return x;
}



listD *mk_listD() {
    listD *l = (listD*) malloc(sizeof(listD));
    l->head = NULL;
    l->last = NULL;
    return l;
}

void free_listD(listD *l) {
    nodeD *n = l->head;
    nodeD *aux;
    while (n != NULL) {
        aux = n->next;
        free(n->information->domain);
        free(n->information);
        free(n);
        n = aux;
    }
    free(l);
}

void add_lastD(listD *l, Email cont) {
    nodeD *new_last = (nodeD*) malloc(sizeof(nodeD));
    new_last->information = cont;
    if (l->last != NULL) l->last->next = new_last;
    else l->head = new_last;
    new_last->previous = l->last;
    new_last->next = NULL;
    l->last = new_last;
}

nodeD *search_nodeD(listD *l, char *domain) {
    nodeD *aux;
    if (l == NULL || domain == NULL) return NULL;
    aux = l->head;
    while (aux != NULL) {
        if (strcmp(aux->information->domain, domain) == 0) return aux;
        aux = aux->next;
    }
    return NULL;
}

listD *free_nodeD(listD *l, Email cont) {
    nodeD *n = search_nodeD(l, cont->domain);
    if (l->head == NULL || n == NULL) return l;
    if (strcmp(l->head->information->domain, cont->domain) == 0) l->head = l->head->next;
    if (strcmp(l->last->information->domain, cont->domain) == 0) l->last = l->last->previous;
    if (n->next != NULL) n->next->previous = n->previous;
    if (n->previous != NULL) n->previous->next = n->next;
    free(n->information->domain);
    free(n->information);
    free(n);
    return l;
}
