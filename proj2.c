/* Author: Antonio Romeu Paulo Pinheiro (92427) */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TreeContact.h"
#include "List.h"
#include "ListD.h"

#define FALSE 0
#define TRUE 1
#define MAX_NAME 1024
#define MAX_PART 512
#define MAX_NUMBER 64

link *treeContact;
list *listContacts;
listD *listDomains;

void commandA() {
    Item newContact = NULL;
    Email newEmail = NULL;
    nodeD *res = NULL;
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    char *local = (char*) malloc(sizeof(char) * MAX_PART);
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    char *number = (char*) malloc(sizeof(char) * MAX_NUMBER);
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-] %[0-9-]", name, local, domain, number);
    if (STsearch(*treeContact, name)) printf("Nome existente.\n");
    else {
        newContact = newItem(name, local, domain, number);
        STinsert(treeContact, newContact);
        add_last(listContacts, newContact);
        res = search_nodeD(listDomains, domain);
        if (res != NULL) res->information->n++;
        else {    
            newEmail = newDomain(domain);
            add_lastD(listDomains, newEmail);
        }
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
    nodeD *new = NULL;
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    scanf(" %[0-9a-zA-Z_-]", name);
    res = STsearch(*treeContact, name);
    if (res == NULL) printf("Nome inexistente.\n");
    else {
        new = search_nodeD(listDomains, res->domain);
        if (new->information->n == 1) listDomains = free_nodeD(listDomains, new->information);
        else new->information->n--;
        listContacts = free_node(listContacts, res);
        STdelete(treeContact, name);
    }
    free(name);
}

void commandE() {
    Item res = NULL;
    Email newEmail;
    nodeD *newNode = NULL;
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    char *local = (char*) malloc(sizeof(char) * MAX_PART);
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-]", name, local, domain);
    res = STsearch(*treeContact, name);
    if (res == NULL) printf("Nome inexistente.\n");
    else {
        newNode = search_nodeD(listDomains, res->domain);
        if (newNode->information->n == 1) listDomains = free_nodeD(listDomains, newNode->information);
        else newNode->information->n--;
        free(res->local);
        free(res->domain);
        res->local = (char*) malloc(strlen(local) + 1);
        res->domain = (char*) malloc(strlen(domain) + 1);
        strcpy(res->local, local);
        strcpy(res->domain, domain);
        newNode = search_nodeD(listDomains, domain);
        if (newNode != NULL) newNode->information->n++;
        else {
            newEmail = newDomain(domain);
            add_lastD(listDomains, newEmail);
        }
    }
    free(name);
    free(local);
    free(domain);
}

void commandC() {
    nodeD *res;
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    scanf(" %[0-9a-zA-Z_.-]", domain);
    res = search_nodeD(listDomains, domain);
    if (res == NULL) printf("%s:0\n", domain);
    else printf("%s:%d\n", domain, res->information->n);
    free(domain);
}

int main() {
    treeContact = (link*) malloc(sizeof(link));
    STinit(treeContact);
    listContacts = mk_list();
    listDomains = mk_listD();
    while (TRUE) {
        switch(getchar()) {
            case 'a' :
                commandA();
                break;
            case 'l' :
                print_list(listContacts);
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
        getchar(); /*reads the \n*/
    }
   return 0;
}
