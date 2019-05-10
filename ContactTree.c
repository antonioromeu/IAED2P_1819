#include "ContactTree.h"

Item newItem(char *name, char *local, char *domain, char *number) {
    Item x = (Item) malloc(sizeof(struct contact));
    x->name = (char*) malloc(strlen(name) + 1);
    x->local = (char*) malloc(strlen(local) + 1);
    x->domain = (char*) malloc(strlen(domain) + 1);
    x->number = (char*) malloc(strlen(number) + 1);
    strcpy(x->name, name);
    strcpy(x->local, local);
    strcpy(x->domain, domain);
    strcpy(x->number, number);
    return x;
}

void deleteItem(Item a) {
    free(a->name);
    free(a->local);
    free(a->domain);
    free(a->number);
    free(a);
}

void visitItem(Item a) {
    printf("%s %s@%s %s\n", a->name, a->local, a->domain, a->number);
}
