/*
 * File: proj2.c
 * Author: Antonio Romeu Paulo Pinheiro (92427)
 * Description: A system for managing contacts in C.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "list.h"

#define FALSE 0
#define TRUE 1
#define MAX_NAME 1023
#define MAX_EMAIL 511
#define MAX_PART 509
#define MAX_NUMBER 63

link *treeHead_C;
list *listHead;

int main() {
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    char *number = (char*) malloc(sizeof(char) * MAX_NUMBER);
    char *local = (char*) malloc(sizeof(char) * MAX_PART);
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    treeHead_C = (link*) malloc(sizeof(link));
    STinit(treeHead_C);
    listHead = mk_list();
    while (TRUE) {
        Item newContact = NULL;
        Item res = NULL;
        switch(getchar()) {
            case 'a' :
                scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-] %[0-9-]", name, local, domain, number);
                newContact = newItem(name, local, domain, number);
                STinsert(treeHead_C, newContact);
                add_last(listHead, newContact);
                break;
            case 'l' :
                print_list(listHead);
                break;
            case 'p' :
                scanf(" %[0-9a-zA-Z_-]", name);
                res = STsearch(*treeHead_C, name);
                if (res == NULL) printf("Nome inixistente.");
                else visitItem(res);
                break;
            case 'r' :
                scanf(" %s", name);
                if (STsearch(*treeHead_C, name) == NULL) printf("Nome inixistente.");
                else {
                    STdelete(treeHead_C, name);
                    
                break;
            case 'e' :
                scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-]", name, local, domain);
                res = STsearch(*treeHead_C, name);
                if (res == NULL) printf("Nome inixistente.");
                else {
                    if ((strcmp(local, res->local) != 0) && (strcmp(domain, res->domain) != 0)) {
                        res->local = strdup(local);
                        res->domain = strdup(domain);
                    }
                    else if (strcmp(local, res->local) != 0) res->local = strdup(local);
                    else res->domain = strdup(domain);
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
                STfree(treeHead_C);
                return 0;
                break;
            }
        getchar(); /*reads the \n*/
    }
   return 0;
}
