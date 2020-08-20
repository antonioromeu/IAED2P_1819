#include "Commands.h"

void commandA() {
    Item newContact = NULL;
    Email newEmail = NULL;
    nodeD *res = NULL;
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    char *local = (char*) malloc(sizeof(char) * MAX_PART);
    char *domain = (char*) malloc(sizeof(char) * MAX_PART);
    char *number = (char*) malloc(sizeof(char) * MAX_NUMBER);
    scanf(" %[0-9a-zA-Z_-] %[0-9a-zA-Z_.-]@%[0-9a-zA-Z_.-] %[0-9-]", name, local, domain, number);
    if (STsearch(*treeContact, name)) printf("Nome existente.\n");      /* Searches struct contact by the name, if it already exists in the tree of contacts prints error message */
    else {                                                              /* Otherwise creates the contact and adds it to the tree and the list of contacts */
        newContact = newItem(name, local, domain, number);
        STinsert(treeContact, newContact);
        add_last(listContacts, newContact);
        res = search_nodeD(listDomains, domain);
        if (res != NULL) res->information->n++;                         /* Searches struct email by domain, if if already exists in the list of domains increments its counter */
        else {
            newEmail = newDomain(domain);                               /* Creates a new struct email */
            add_lastD(listDomains, newEmail);                           /* Adds it to teh list of domains */
        }
    }
    free(name);
    free(number);
    free(local);
    free(domain);
}

void commandL() {
    print_list(listContacts);                                           /* Prints the list of contatcs sorted by introducation */
}

void commandP() {
    Item res = NULL;
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    scanf(" %[0-9a-zA-Z_-]", name);
    res = STsearch(*treeContact, name);
    if (res == NULL) printf("Nome inexistente.\n");                     /* Searches the struct contact by name, if it already exists prints error message */
    else visitItem(res);                                                /* Else prints the components of the struct */
    free(name);
}

void commandR() {
    Item res = NULL;
    nodeD *new = NULL;
    char *name = (char*) malloc(sizeof(char) * MAX_NAME);
    scanf(" %[0-9a-zA-Z_-]", name);
    res = STsearch(*treeContact, name);
    if (res == NULL) printf("Nome inexistente.\n");                     /* Searches struct contact by the name, if it doesnt exist prints error message */
    else {
        new = search_nodeD(listDomains, res->domain);                   /* Searches the struct email by domain */
        if (new->information->n == 1)
            listDomains = free_nodeD(listDomains, new->information);    /* If the counter is 1, removes the struct of the list */
        else new->information->n--;                                     /* Else decrements the number of ocurrences */
        listContacts = free_node(listContacts, res);                    /* Removes the struct contact from the list of contacts */
        STdelete(treeContact, name);                                    /* Removes the stuct contact from the tree of contacts */
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
    if (res == NULL) printf("Nome inexistente.\n");                     /* Searches the strut contact by name, if it doesnt exist prints error message */
    else {
        newNode = search_nodeD(listDomains, res->domain);
        if (newNode->information->n == 1)
            listDomains = free_nodeD(listDomains, newNode->information);/* Removes the struct email of the list of domains if the number of ocurrences is 1 */
        else newNode->information->n--;                                 /* Else decrements it */
        free(res->local);
        free(res->domain);
        res->local = (char*) malloc(strlen(local) + 1);                 /* Allocates memory for the pointer to local based on the lenght of the name */
        res->domain = (char*) malloc(strlen(domain) + 1);               /* Allocates memory for the pointer to domain based on the lenght of the domain */
        strcpy(res->local, local);                                      /* Copies the local scaned to the pointer to local of the struct */
        strcpy(res->domain, domain);                                    /* Copies the domain scaned to the pointer to domain of the struct */
        newNode = search_nodeD(listDomains, domain);
        if (newNode != NULL) newNode->information->n++;                 /* If the struct email aready exists in the list of domains, increments its counter */
        else {
            newEmail = newDomain(domain);                               /* Else, creates a new email with the scaned domain and adds it the list of domains */
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
    if (res == NULL) printf("%s:0\n", domain);                          /* Prints the domain and the number of ocurrences, if it doesnt exist the number is 0 */
    else printf("%s:%d\n", domain, res->information->n);
    free(domain);
}
