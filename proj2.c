/*
 * File: proj2.c
 * Author: Antonio Romeu Paulo Pinheiro (92427)
 * Description: A system for managing contacts in C.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TreeContact.h"
#include "TreeDomain.h"
#include "List.h"

#define FALSE 0
#define TRUE 1
#define MAX_NAME 1023
#define MAX_PART 509
#define MAX_NUMBER 63

link *treeContact;
list *listHead;

void commandA_C(char *name, char *local, char *domain, char *number) {
    Item newContact = NULL;
    Item res = NULL;
    res = STsearch(*treeContact, name);
    if (res != NULL) printf("Nome existente.\n");
    else {
        newContact = newItem(name, local, domain, number);
        STinsert(treeContact, newContact);
        add_last(listHead, newContact);
    }
}

void commandP_C(char *name) {
    Item res = NULL;
    res = STsearch(*treeContact, name);
    if (res == NULL) printf("Nome inexistente.\n");
    else visitItem(res);
}

void commandR_C(char *name) {
    Item res = NULL;
    res = STsearch(*treeContact, name);
    if (res == NULL) printf("Nome inexistente.\n");
    else {
        STdelete(treeContact, name);
        listHead = free_node(listHead, res);
    }
}

void commandE_C(char *name, char *local, char *domain) {
    Item res = NULL;
    res = STsearch(*treeContact, name);
    if (res == NULL) printf("Nome inexistente.\n");
    else {
        if ((strcmp(local, res->local) != 0) && (strcmp(domain, res->domain) != 0)) {
            strcpy(res->local, local);
            strcpy(res->domain, domain);
        }
        else if (strcmp(local, res->local) != 0) strcpy(res->local, local);
        else strcpy(res->domain, domain);
    }
}

int main() {
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    char *number = (char*) malloc(sizeof(char) * MAX_NUMBER);
    char *local = (char*) malloc(sizeof(char) * MAX_PART);
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    treeContact = (link*) malloc(sizeof(link));
    STinit(treeContact);
    listHead = mk_list();
    while (TRUE) {
        switch(getchar()) {
            case 'a' :
                scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-] %[0-9-]", name, local, domain, number);
                commandA_C(name, local, domain, number);
                break;
            case 'l' :
                print_list(listHead);
                break;
            case 'p' :
                scanf(" %[0-9a-zA-Z_-]", name);
                commandP_C(name);
                break;
            case 'r' :
                scanf(" %[0-9a-zA-Z_-]", name);
                commandR_C(name);
                break;
            case 'e' :
                scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-]", name, local, domain);
                commandE_C(name, local, domain);
                break;
            case 'c' :
                scanf(" %s", domain);
                break;
            case 'x' :
                free(name);
                free(number);
                free(local);
                free(domain);
                STfree(treeContact);
                free(treeContact);
                free_list(listHead);
                return 0;
                break;
            }
        getchar(); /*reads the \n*/
    }
   return 0;
}
