#include "DomainTree.h"

ItemD newItemD(char *domain) {
    ItemD x = (ItemD) malloc(sizeof(struct domain));
    x->domain = (char*) malloc(sizeof(char) * 509);    
    strcpy(x->domain, domain);
    x->n = 1;
    return x;
}

void deleteItemD(ItemD a) {
    free(a->domain);
    free(a);
}

void visitItemD(ItemD a) {
    printf("%s %d\n", a->domain, a->n);
}
