#ifndef _ITEMD_
#define _ITEMD_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define keyD(a) (a != NULL ? a->domain : "")
#define lessD(a, b) (strcmp(a, b) < 0)
#define eqD(a, b) (strcmp(a, b) == 0)

typedef char *KeyD;

typedef struct domain {
    char *domain;
    int n;
} *ItemD;

ItemD newItemD(char *domain);
void deleteItemD(ItemD a);
void visitItemD(ItemD a);

#endif
