/* Author: Antonio Romeu Paulo Pinheiro (92427) */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TreeContact.h"
#include "List.h"
/*#include "ListD.h"*/

#define FALSE 0
#define TRUE 1
#define MAX_NAME 1024
#define MAX_PART 512
#define MAX_NUMBER 64

link *treeContact;
list *listHead;
/*listD *listHeadDomain;*/

void commandA() {
    Item newContact = NULL;
    /*nodeD newDomain = NULL;*/
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    char *local = (char*) malloc(sizeof(char) * MAX_PART);
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    char *number = (char*) malloc(sizeof(char) * MAX_NUMBER);
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-] %[0-9-]", name, local, domain, number);
    if (STsearch(*treeContact, name)) printf("Nome existente.\n");
    else {
        newContact = newItem(name, local, domain, number);
        STinsert(treeContact, newContact);
        add_last(listHead, newContact);
    }
    free(name);
    free(number);
    free(local);
    free(domain);
}

void commandP() {
    Item res = NULL;
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    scanf(" %[0-9a-zA-Z_-]", name);
    res = STsearch(*treeContact, name);
    if (res == NULL) printf("Nome inexistente.\n");
    else visitItem(res);
    free(name);
}

void commandR() {
    Item res = NULL;
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    scanf(" %[0-9a-zA-Z_-]", name);
    res = STsearch(*treeContact, name);
    if (res == NULL) printf("Nome inexistente.\n");
    else {
        STdelete(treeContact, name);
        listHead = free_node(listHead, res);
    }
    free(name);
}

void commandE() {
    Item res = NULL;
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    char *local = (char*) malloc(sizeof(char) * MAX_PART);
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-]", name, local, domain);
    res = STsearch(*treeContact, name);
    if (res == NULL) printf("Nome inexistente.\n");
    else {
        free(res->local);
        free(res->domain);
        res->local = (char*) malloc(strlen(local) + 1);
        res->domain = (char*) malloc(strlen(domain) + 1);
        strcpy(res->local, local);
        strcpy(res->domain, domain);
    }
    free(name);
    free(local);
    free(domain);
}

/*void commandC() {
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    nodeD *aux;
    scanf(" %[0-9a-zA-Z_.-]", domain);
    aux = search_nodeD(listHeadDomain, domain);
    printf("%s:%d", domain, aux->n);
    free(domain);
}*/

void contDomains(list *l) {
    int c = 0;
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    node *aux, *n = l->head;
    scanf(" %[0-9a-zA-Z_.-]", domain);
    while (n != NULL) {
        if (strcmp(n->contact->domain, domain) == 0) c++;
        aux = n->next;
        n = aux;
    }
    printf("%s:%d\n", domain, c);
    free(domain);
}

int main() {
    treeContact = (link*) malloc(sizeof(link));
    STinit(treeContact);
    listHead = mk_list();
    while (TRUE) {
        switch(getchar()) {
            case 'a' :
                commandA();
                break;
            case 'l' :
                print_list(listHead);
                break;
            case 'p' :
                commandP();
                break;
            case 'r' :
                commandR();
                break;
            case 'e' :
                commandE();
                break;
            case 'c' :
                /*commandC();*/
                contDomains(listHead);
                break;
            case 'x' :
                STfree(treeContact);
                free(treeContact);
                free_list(listHead);
                /*free_list(listHeadDomain);*/
                return 0;
                break;
            }
        getchar(); /*reads the \n*/
    }
   return 0;
}
