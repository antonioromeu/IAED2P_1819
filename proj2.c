/*
 * Author: Antonio Romeu Paulo Pinheiro (92427)
 * Description: A program for managing contacts in C.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Commands.h"

/* Constants */
#define FALSE 0
#define TRUE 1
#define MAX_NAME 1024
#define MAX_PART 512
#define MAX_NUMBER 64

/* Global variables */
link *treeContact;      /* Sorted tree that organizes contacts by name (key) */
list *listContacts;     /* Linked list that saves the contacts by the order of introduction */
listD *listDomains;     /* Linked list that saves the number of ocurrences of the domains */

int main() {
    treeContact = (link*) malloc(sizeof(link));     /* Allocates memory for the contact tree */
    STinit(treeContact);                            /* Initialization of the contact tree */
    listContacts = mk_list();                       /* Initialization of the list sorted by order of introduction */
    listDomains = mk_listD();                       /* Initialization of the list of domains */
    while (TRUE) {
        switch(getchar()) {
            case 'a' :
                commandA();
                break;
            case 'l' :
                commandL();
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
                commandC();
                break;
            case 'x' :
                STfree(treeContact);
                free(treeContact);
                free_list(listContacts);
                free_listD(listDomains);
                return 0;
                break;
            }
        getchar(); /* Reads the \n */
    }
   return 0;
}
