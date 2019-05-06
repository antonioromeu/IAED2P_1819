/*
 * File: proj2.c
 * Author: Antonio Romeu Paulo Pinheiro (92427)
 * Description: A system for managing contacts in C.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

#define FALSE 0
#define TRUE 1
#define MAX_NAME 1023
#define MAX_EMAIL 511
#define MAX_PART 509
#define MAX_NUMBER 63

link *treeHead;

int main() {
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    char *email = (char*) malloc(sizeof(char) * MAX_EMAIL);
    char *number = (char*) malloc(sizeof(char) * MAX_NUMBER);
    char *local = (char*) malloc(sizeof(char) * MAX_PART);
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    treeHead = (link*) malloc(sizeof(link));
    STinit(treeHead);
    while (TRUE) {
        Item newContact = NULL;
        Item res = NULL;
        switch(getchar()) {
            case 'a' :
                scanf(" %[0-9a-zA-Z-_] %[0-9a-zA-Z-_.]@%[0-9a-zA-Z-_.] %[0-9-]", name, local, domain, number);
                newContact = newItem(name, local, domain, number);
                STinsert(treeHead, newContact);
                break;
            case 'l' :
                traverse(*treeHead);
                break;
            case 'p' :
                scanf(" %s", name);
                res = STsearch(*treeHead, name);
                if (res == NULL) printf("Nome inixistente.");
                visitItem(res);
                break;
            case 'r' :
                scanf(" %s", name);
                break;
            case 'e' :
                scanf(" %s %s", name, email);
                break;
            case 'c' :
                scanf(" %s", domain);
                break;
            case 'x' :
                return 0;
                break;
            }
        getchar(); /*reads the \n*/
    }
   return 0;
}
