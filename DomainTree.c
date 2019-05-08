#include "DomainTree.h"

ItemD newItemD(char *domain) {
    ItemD x = (ItemD) malloc(sizeof(struct domain));;
    x->domain = strdup(domain);
    x->n = 0;
    return x;
}

void deleteItemD(ItemD a) {
    free(a->domain);
    free(a);
}

void visitItemD(ItemD a) {
    printf("%s %d\n", a->domain, a->n);
}
