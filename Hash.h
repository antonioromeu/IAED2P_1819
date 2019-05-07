#include "Contact.h"

#define NULLlink NULL

typedef struct node {
    char *domain;
    int n;
    struct node *next;
} *linkHash;

void HSinit(int m);
void HSinsert(Key domain);
linkHash HSdelete(Key domain);
linkHash HSsearch(Key domain);
void HSincrement(Key domain);
