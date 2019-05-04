/*
 * File: proj2.c
 * Author: Antonio Romeu Paulo Pinheiro (92427)
 * Description: A system for managing contacts in C.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Item.c"
#include "tree.c"

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
    while (TRUE) {
        Item newContact = NULL;
        Item res = NULL;
        treeHead = NULL;
        switch(getchar()) {
            case 'a' :
                scanf(" %s %s %s", name, email, number);
                newContact = newItem(name, email, number);
                visitItem(newContact);
                STinsert(treeHead, newContact);
                break;
            case 'l' :
                break;
            case 'p' :
                scanf(" %s", name);
                res = STsearch(*treeHead, name);
                if (res == NULL) printf("Nome inixistente.");
                visitItem(res);
                break;
            case 'r' :
                break;
            case 'e' :
                scanf(" %s %s", name, email);
                break;
            case 'c' :
                break;
            case 'x' :
                return 0;
                break;
            }
        getchar(); /*reads the \n*/
    }
   return 0;
}
