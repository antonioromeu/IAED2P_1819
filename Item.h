#ifndef _ITEM_
#define _ITEM_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define key(a) (a != NULL ? a->name : "")
#define less(a, b) (strcmp(a, b) < 0)
#define eq(a, b) (strcmp(a, b) == 0)

typedef char *Key;

typedef struct contact {
    char *name, *email, *number;
} *Item;

Item newItem(char *name, char *email, char *number);
void deleteItem(Item a);
void visitItem(Item a);

#endif
