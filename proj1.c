/*
 * File: proj1.c
 * Author: Antonio Romeu (92427)
 * Description: A program for scheduling meetings and booking rooms in C
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DESCRICAO 64
#define NOME 64
#define LST_PARTICIPANTES 194
#define MAX_LEN 1000
#define FALSE 0
#define TRUE 1

typedef struct {
    char descricao[DESCRICAO], responsavel[NOME], participantes[3][NOME];
    int data, inicio, duracao, sala, n_participantes, amd;
} evento;

evento tab_eventos[MAX_LEN];
int contador_eventos = 0;

void inicializaTabela() {
    int i;
    for (i = 0; i < MAX_LEN; i++) {
        tab_eventos[i].descricao[0] = '\0';
        tab_eventos[i].responsavel[0] = '\0';
        tab_eventos[i].participantes[0][0] = '\0';
        tab_eventos[i].participantes[1][0] = '\0';
        tab_eventos[i].participantes[2][0] = '\0';
        tab_eventos[i].data = 0;
        tab_eventos[i].amd = 0;
        tab_eventos[i].inicio = 0;
        tab_eventos[i].duracao = 0;
        tab_eventos[i].sala = 0;
        tab_eventos[i].n_participantes = 0;
    }
}

int inicioParaMinutos(int inicio) {
    int minutos, horas;
    minutos = inicio % 100;
    horas = (inicio - minutos) / 100;
    horas *= 60;
    minutos += horas;
    return minutos;
}

int transformaData(evento a) {
    int amd = 0;
    amd = ((a.data % 10000) * 10000) + (((a.data / 10000) % 100) * 100) + (a.data / 1000000);
    return amd;
}

evento separaParticipantes(evento a, char participantes[]) {
    int i = 0, p = 0, j = 0;
    for (; participantes[i] != '\0' && i < LST_PARTICIPANTES; i++, j++) {
        if (participantes[i] == ':') {
            a.participantes[p][j] = '\0';
            p++;
            j = -1;
            a.n_participantes++;
            continue;
        }
        a.participantes[p][j] = participantes[i];
    }
    a.participantes[p][j] = '\0';
    for (i = p + 1; i < 3; i++) {
        a.participantes[i][0] = '\0';
    }
    return a;
}

void imprimeParticipantes(evento a) {
    int i;
    for (i = 0; i < 3; i++) {
        if (a.participantes[i][0] != '\0') printf(" %s", a.participantes[i]);
    }
    printf("\n");
}

int sobreposto(evento a, evento b) {
    if ((transformaData(a) != transformaData(b)) || (inicioParaMinutos(a.inicio) > (inicioParaMinutos(b.inicio) + b.duracao - 1)) || (inicioParaMinutos(b.inicio) > (inicioParaMinutos(a.inicio) + a.duracao - 1))) return FALSE;
    return TRUE;
}

int verificaSobreposicaoSalas(evento a) {
    int i, res = 0;
    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && (sobreposto(a, tab_eventos[i])) && (a.sala == tab_eventos[i].sala) && (a.sala != 0)) {
            printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
            res += 1;
        }
    }
    return res;
}

int verificaSobreposicaoResponsavel(evento a) {
    int i, k, res = 0;
    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && (sobreposto(a, tab_eventos[i])) && (strcmp(a.responsavel, tab_eventos[i].responsavel) == 0)) {
            printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.responsavel);
            res += 1;
        }
    }

    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && sobreposto(a, tab_eventos[i])) {
            for (k = 0; k < 3; k++) {
                if ((strcmp(a.responsavel, tab_eventos[i].participantes[k]) == 0)) {
                    printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.responsavel);
                    res += 1;
                }
            }
        }
    }
    return res;
}

int verificaSobreposicaoParticipantes(evento a) {
    int i, k, j, res = 0;
    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && (sobreposto(a, tab_eventos[i]))) {
            for (j = 0; j < 3; j++) {
                if (strcmp(a.participantes[j], tab_eventos[i].responsavel) == 0 && (a.participantes[j][0] != '\0')) {
                    printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participantes[j]);
                    res += 1;
                    }
                }
            }
        }

    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && (sobreposto(a, tab_eventos[i]))) {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 3; k++) {
                    if ((strcmp(a.participantes[j], tab_eventos[i].participantes[k]) == 0) && (a.participantes[j][0] != '\0')) {
                        printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participantes[j]);
                        res += 1;
                    }
                }
            }
        }
    }
    return res;
}

int verificaAdicionaParticipante(char participante[], evento a) {
    int i = 0, k = 0;
    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && sobreposto(a, tab_eventos[i])) {
            if (strcmp(tab_eventos[i].responsavel, participante) == 0) {
                printf("Impossivel adicionar participante. Participante %s tem um evento sobreposto.\n", participante);
                return 1;
            }
        }
    }

    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && sobreposto(a, tab_eventos[i])) {
            for (k = 0; k < 3; k++) {
                if (strcmp(tab_eventos[i].participantes[k], participante) == 0) {
                    printf("Impossivel adicionar participante. Participante %s tem um evento sobreposto.\n", participante);
                    return 1;
                }
            }
        }
    }

    return 0;
}

evento criaEvento(char descricao[], int data, int inicio, int duracao, int sala, char responsavel[], char participantes[]) {
    evento a;
    strcpy(a.descricao, descricao);
    a.n_participantes = 1;
    a.data = data;
    a.inicio = inicio;
    a.duracao = duracao;
    a.sala = sala;
    strcpy(a.responsavel, responsavel);
    a = separaParticipantes(a, participantes);
    a.amd = transformaData(a);
    return a;
}

int less(evento a, evento b) {
    if (a.amd < b.amd) return TRUE;
    else if (a.amd == b.amd) {
        if (a.inicio < b.inicio) return TRUE;
        else if (a.inicio == b.inicio) {
            if (a.sala < b.sala) return TRUE;
        }
    }
    return FALSE;
}

void sort() {
    int i, j, l;
    evento temp;
    l = 0;
    for (i = l + 1; i <= contador_eventos - 1; i++) {
        temp = tab_eventos[i];
        j = i - 1;
        while (j >= l && less(temp, tab_eventos[j])) {
            tab_eventos[j + 1] = tab_eventos[j];
            j--;
        }
        tab_eventos[j + 1] = temp;
    }
}

void adicionaEvento(evento a) {
    int res = 0;
    res += verificaSobreposicaoSalas(a);
    if (res != 0) return;
    res += verificaSobreposicaoResponsavel(a);
    res += verificaSobreposicaoParticipantes(a);
    if (res != 0) return;
    tab_eventos[contador_eventos] = a;
    contador_eventos++;
    sort();
}

int procuraEvento(char descricao[]) {
    int i = 0;
    for (; i < contador_eventos; i++) {
        if (strcmp(tab_eventos[i].descricao, descricao) == 0) return i;
    }
    return -1;
}

void listaEventos() {
    int i = 0;
    for (; i < contador_eventos; i++) {
        if (tab_eventos[i].descricao[0] != '\0') {
            printf("%s %08d %04d %d Sala%d %s\n*", tab_eventos[i].descricao, tab_eventos[i].data, tab_eventos[i].inicio, tab_eventos[i].duracao, tab_eventos[i].sala, tab_eventos[i].responsavel);
            imprimeParticipantes(tab_eventos[i]);
        }
    }
}

void listaSala(int sala) {
    int i = 0;
    for (; i < contador_eventos; i++) {
        if (tab_eventos[i].sala == sala) {
            printf("%s %08d %04d %d Sala%d %s\n*", tab_eventos[i].descricao, tab_eventos[i].data, tab_eventos[i].inicio, tab_eventos[i].duracao, tab_eventos[i].sala, tab_eventos[i].responsavel);
            imprimeParticipantes(tab_eventos[i]);
        }
    }
}

void apagaEvento(char descricao[]) {
    int index;
    index = procuraEvento(descricao);
    if (index != -1) {
        for (; index < contador_eventos; index++) {
            tab_eventos[index] = tab_eventos[index + 1];
            }
        contador_eventos--;
        }
    else printf("Evento %s inexistente.\n", descricao);
}

void alteraInicio(char descricao[], int novo_inicio) {    
    int res = 0, index;
    evento temp, copia;
    index = procuraEvento(descricao);
    if (index != -1) {
        copia = tab_eventos[index];
        temp = tab_eventos[index];
        apagaEvento(descricao);
        temp.inicio = novo_inicio;
        res += verificaSobreposicaoSalas(temp);
        if (res != 0) {
            adicionaEvento(copia);
            return;
        }
        res += verificaSobreposicaoResponsavel(temp);
        res += verificaSobreposicaoParticipantes(temp);
        if (res != 0) {
            adicionaEvento(copia);
            return;
        }
        adicionaEvento(temp);
    }
    else printf("Evento %s inexistente.\n", descricao);
}

void alteraDuracao(char descricao[], int nova_duracao) {
    int res = 0, index;
    evento temp, copia;
    index = procuraEvento(descricao);
    if (index != -1) {
        copia = tab_eventos[index];
        temp = tab_eventos[index];
        apagaEvento(descricao);
        temp.duracao = nova_duracao;
        res += verificaSobreposicaoSalas(temp);
        if (res != 0) {
            adicionaEvento(copia);
            return;
        }
        res += verificaSobreposicaoResponsavel(temp);
        res += verificaSobreposicaoParticipantes(temp);
        if (res != 0) {
            adicionaEvento(copia);            
            return;
        }
        adicionaEvento(temp);
    }
    else printf("Evento %s inexistente.\n", descricao);
}

void alteraSala(char descricao[], int nova_sala) {
    int res = 0, index;
    evento temp, copia;
    index = procuraEvento(descricao);
    if (index != -1) {
        copia = tab_eventos[index];
        temp = tab_eventos[index];
        apagaEvento(descricao);
        temp.sala = nova_sala;
        res += verificaSobreposicaoSalas(temp);
        if (res != 0) {
            adicionaEvento(copia);            
            return;
        }
        res += verificaSobreposicaoResponsavel(temp);
        res += verificaSobreposicaoParticipantes(temp);
        if (res != 0) {
            adicionaEvento(copia);
            return;
        }
        adicionaEvento(temp);
    }
    else printf("Evento %s inexistente.\n", descricao);
}

void adicionaParticipante(char descricao[], char participante[]) {
    int index, i, res = 0;
    evento temp;
    index = procuraEvento(descricao);
    for (i = 0; i < 3; i++) {
        if (strcmp(tab_eventos[index].participantes[i], participante) == 0) return;
    }
    if (index == -1) {
        printf("Evento %s inexistente.\n", descricao);
        return;
    }
    if (tab_eventos[index].n_participantes == 3) {
        printf("Impossivel adicionar participante. Evento %s ja tem 3 participantes.\n", descricao);
        return;
    }
    temp = tab_eventos[index];
    res += verificaAdicionaParticipante(participante, temp);
    if (res != 0) return;
    res += verificaSobreposicaoResponsavel(temp);
    res += verificaSobreposicaoParticipantes(temp);
    if (res != 0) return;
    strcpy(tab_eventos[index].participantes[tab_eventos[index].n_participantes], participante);
    tab_eventos[index].n_participantes++;
}

void removeParticipante(char descricao[], char participante[]) {
    int i, index;
    index = procuraEvento(descricao);
    if (index == -1) {
        printf("Evento %s inexistente.\n", descricao);
        return;
    }
    for (i = 0; i < 3; i++) {
        if (strcmp(tab_eventos[index].participantes[i], participante) == 0) {
            break;
        }
        if (i == 2) return;
    }
    if (tab_eventos[index].n_participantes == 1) {
        printf("Impossivel remover participante. Participante %s e o unico participante no evento %s.\n", participante, descricao);
        return;
    }
    for (i = 0; i < 3; i++) {
        if (strcmp(tab_eventos[index].participantes[i], participante) == 0) tab_eventos[index].participantes[i][0] = '\0';
    }
    tab_eventos[index].n_participantes--;
}

int main() {
    char descricao[DESCRICAO], responsavel[NOME], participante[NOME], novo_participante[NOME], participantes[LST_PARTICIPANTES];
    int data = 0, inicio = 0, duracao = 0, sala = 0, novo_inicio = 0, nova_duracao = 0, nova_sala = 0;
    evento a;
    inicializaTabela();
    while (TRUE) {
        switch(getchar()) {
        case 'a' :
            scanf(" %[^:]:%d:%d:%d:%d:%[^:]:%[^\n]", descricao, &data, &inicio, &duracao, &sala, responsavel, participantes);
            a = criaEvento(descricao, data, inicio, duracao, sala, responsavel, participantes);
            adicionaEvento(a);
            break;
        case 'l' :
            sort();
            listaEventos();
            break;
        case 's' :
            scanf(" %d", &sala);
            listaSala(sala);
            break;
        case 'r' :
            scanf(" %[^\n]", descricao);
            apagaEvento(descricao);
            break;
        case 'i' :
            scanf(" %[^:]:%d", descricao, &novo_inicio);
            alteraInicio(descricao, novo_inicio);
            break;
        case 't' :
            scanf(" %[^:]:%d", descricao, &nova_duracao);
            alteraDuracao(descricao, nova_duracao);
            break;
        case 'm' :
            scanf(" %[^:]:%d", descricao, &nova_sala);
            alteraSala(descricao, nova_sala);
            break;
        case 'A' :
            scanf(" %[^:]:%[^\n]", descricao, novo_participante);
            adicionaParticipante(descricao, novo_participante);
            break;
        case 'R' :
            scanf(" %[^:]:%[^\n]", descricao, participante);
            removeParticipante(descricao, participante);
            break;
        case 'x':
            return 0;
            break;
        }
        getchar();
    }
   return 0;
}
