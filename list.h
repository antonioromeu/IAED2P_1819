#ifndef _LIST_
#define _LIST_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contact.h"

typedef struct str_node {
    struct str_node *next, *previous;
    Item contact;
} node;

typedef struct {
    node *head, *last;
} list;

list *mk_list();
void free_list(list *l);
void add_last(list *l, Item cont);
void print_list(list *l);
list *free_node(list *l, Item cont);
node *search_node(list *l, Item cont);

#endif
