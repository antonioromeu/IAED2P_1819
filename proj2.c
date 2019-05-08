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
#define MAX_EMAIL 511
#define MAX_PART 509
#define MAX_NUMBER 63

link *treeContact;
list *listHead;

int main() {
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    char *number = (char*) malloc(sizeof(char) * MAX_NUMBER);
    char *local = (char*) malloc(sizeof(char) * MAX_PART);
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    treeContact = (link*) malloc(sizeof(link));
    STinit(treeContact);
    listHead = mk_list();
    while (TRUE) {
        Item newContact = NULL;
        Item res = NULL;
        switch(getchar()) {
            case 'a' :
                scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-] %[0-9-]", name, local, domain, number);
                res = STsearch(*treeContact, name);
                if (res != NULL) printf("Nome existente.\n");
                else {
                    newContact = newItem(name, local, domain, number);
                    STinsert(treeContact, newContact);
                    add_last(listHead, newContact);
                }
                break;
            case 'l' :
                print_list(listHead);
                break;
            case 'p' :
                scanf(" %[0-9a-zA-Z_-]", name);
                res = STsearch(*treeContact, name);
                if (res == NULL) printf("Nome inexistente.\n");
                else visitItem(res);
                break;
            case 'r' :
                scanf(" %s", name);
                res = STsearch(*treeContact, name);
                if (res == NULL) printf("Nome inexistente.\n");
                else {
                    STdelete(treeContact, name);
                    listHead = free_node(listHead, res);
                }
                break;
            case 'e' :
                scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-]", name, local, domain);
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
