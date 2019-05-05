#ifndef _ITEM_
#define _ITEM_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define key(a) (a != NULL ? a->n : -1)
#define less(a, b) (a < b)
#define eq(a, b) (a == b)

typedef long Key;

typedef struct contact {
    char *name, *email, *number;
    long n;
} *Item;

Item newItem(char *name, char *email, char *number, int n);
void deleteItem(Item a);
void visitItem(Item a);

#endif
