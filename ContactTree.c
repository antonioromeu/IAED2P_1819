#include "ContactTree.h"

Item newItem(char *name, char *local, char *domain, char *number) {
    Item x = (Item) malloc(sizeof(struct contact));
    x->name = strdup(name);
    x->local = strdup(local);
    x->domain = strdup(domain);
    x->number = strdup(number);
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
