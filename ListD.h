#ifndef _LISTD_
#define _LISTD_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct email {
    char *domain;
    int n;
} *Email;

typedef struct str_nodeD {
    struct str_nodeD *next, *previous;
    Email information;
} nodeD;

typedef struct {
    nodeD *head, *last;
} listD;

listD *mk_listD();
void free_listD(listD *l);
void add_lastD(listD *l, Email information);
nodeD *search_nodeD(listD *l, char *domain);
listD *free_nodeD(listD *l, Email information);
Email newDomain(char *domain);

#endif
