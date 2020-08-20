#ifndef _ITEM_
#define _ITEM_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define key(a) (a != NULL ? a->name : "")
#define less(a, b) (strcmp(a, b) < 0)
#define eq(a, b) (strcmp(a, b) == 0)

#define MAX_NAME 1024
#define MAX_PART 512
#define MAX_NUMBER 64

typedef char *Key;

typedef struct contact {
    Key name, local, domain, number;
} *Item;

Item newItem(Key name, Key local, Key domain, Key number);
void deleteItem(Item a);
void visitItem(Item a);

#endif
