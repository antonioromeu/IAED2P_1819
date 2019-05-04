#include "Item.h"

Item newItem(char *name, char *email, char *number) {
    Item x = (Item) malloc(sizeof(struct contact));
    x->name = strdup(name);
    x->email = strdup(email);
    x->number = strdup(number);
    return x;
}

void deleteItem(Item a) {
    free(a->name);
    free(a->email);
    free(a->number);
    free(a);
}

void visitItem(Item a) {
    printf("%s %s %s\n", a->name, a->email, a->number);
}
