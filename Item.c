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
    printf("name: %s\n", a->name);
    printf("email: %s\n", a->email);
    printf("number: %s\n", a->number);
}
