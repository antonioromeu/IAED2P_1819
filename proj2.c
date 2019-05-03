/*
 * File: proj2.c
 * Author: Antonio Romeu Paulo Pinheiro (92427)
 * Description: A system for managing contacts in C.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_NOME 1023
#define MAX_EMAIL 511
#define MAX_PARTE 509
#define MAX_NUM 63

typedef struct stru_node {
    struct stru_node *next, *previous;
    char *nome, *email, *local, *dominio, *num;
} node;

typedef struct {
    node *head, *last;
} list;

list *mk_list() {
    list *l = (list*) malloc(sizeof(list));
    l->head = NULL;
    l->last = NULL;
    return l;
}

node *criaContacto(char *nome, char *email, char *num) {

}

list *adicionaContacto(node *contacto) {

}

int main() {
    char *nome = (char*) malloc(sizeof(char) * MAX_NOME);
    char *email = (char*) malloc(sizeof(char) * MAX_EMAIL);
    char *num = (char*) malloc(sizeof(char) * MAX_NUM);
    node *novo_contacto = NULL;
    list *l = mk_list();
    while (TRUE) {
        switch(getchar()) {
        case 'a' :
            scanf(" %[0-9a-zA-Z-_] %[0-9a-zA-Z-_.]+@[0-9a-zA-Z-_.] %[0-9\-]", nome, email, num);
            novo_contacto = criaContacto(nome, email, num);
            adicionaContacto(novo_contacto);
            break;
/*
        case 'l' :
            break;
        case 'p' :
            break;
        case 'r' :
            break;
        case 'e' :
            break;
        case 'c' :
            break;
*/
        case 'x' :
            return 0;
            break;
        }
        getchar(); /* Reads the \n */
    }
   return 0;
}
