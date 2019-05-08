#include "ContactTree.h"

Item newItem(char *name, char *local, char *domain, char *number) {
    Item x = (Item) malloc(sizeof(struct contact));
    x->name = (char*) malloc(sizeof(char) * 1023);
    x->number = (char*) malloc(sizeof(char) * 63);
    x->local = (char*) malloc(sizeof(char) * 509);
    x->domain = (char*) malloc(sizeof(char) * 509);
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
