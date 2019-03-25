#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DESCRICAO 63
#define PESSOA_RESP 63
#define LST_PARTICIPANTES 191
#define MAX_SALAS 10
#define MAX_EVENTOS 100
#define MAX_LEN 1000
#define FALSE 0
#define TRUE 1

typedef struct {
    int dia;
    int mes;
    int ano;
    int amd;
    int hora;
    int minutos;
} data;

typedef struct {
    char descricao[DESCRICAO];
    char responsavel[PESSOA_RESP];
    char participantes_str[LST_PARTICIPANTES];
    char participantes[3][PESSOA_RESP];
    int data;
    int inicio;
    int duracao;
    int sala;
    data horario;
} evento;

evento tab_eventos[MAX_LEN];
int tab_salas[MAX_SALAS][MAX_EVENTOS];
evento nulo;

void inicializaTabelas() {
    int i, j, k;
    for (i = 0; i < MAX_LEN; i++) {
        tab_eventos[i] = nulo;
    }

    for (j = 0; j < MAX_SALAS; j++) {
        for (k = 0; k < MAX_EVENTOS; k++) {
            tab_salas[j][k] = -1;
        }
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

int sobreposto(evento a, evento b) {
    if (transformaData(a) != transformaData(b)) return FALSE;
    else if (inicioParaMinutos(a.inicio) >= inicioParaMinutos(b.inicio) + b.duracao || inicioParaMinutos(b.inicio) >= inicioParaMinutos(a.inicio) + a.duracao) return FALSE;
    return TRUE;
}

evento separaParticipantes(evento a, char participantes[]) {
    int i = 0, p = 0, j = 0;
    for (; participantes[i] != '\0' && i < LST_PARTICIPANTES; i++, j++) {
        if (participantes[i] == ':') {
            a.participantes[p][j] = '\0';
            p++;
            j = -1;
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

int verificaSobreposicao(evento a) {
    int i, j, k, res = 0;
    for (i = 0; i < MAX_EVENTOS; i++) {
        if (sobreposto(a, tab_eventos[tab_salas[a.sala - 1][i]])){
            printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
            res = 1;
        }
    }
    for (i = 0; i < MAX_LEN; i++) {
        if (sobreposto(a, tab_eventos[i])) {
            if (strcmp(a.responsavel, tab_eventos[i].responsavel) == 0) {
                printf("Impossivel agendar evento %s. Responsavel %s tem um evento sobreposto.\n", a.descricao, a.responsavel);
                res = 1;
            }
        }
    }
    for (i = 0; i < MAX_EVENTOS; i++) {
        if (sobreposto(a, tab_eventos[i])) {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 3; k++) {
                    if (strcmp(a.participantes[j], tab_eventos[i].participantes[k]) == 0) {
                        printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participantes[j]);
                        res = 1;
                    }
                }
            }
        }
    }
    return res;
}

int procuraEvento(char descricao[]) {
    int i = 0;
    for (; i < MAX_LEN; i++) {
        if (strcmp(tab_eventos[i].descricao, descricao) == 0) return i;
    }
    return -1;
}

void adicionaEvento(evento a) {
    int i = 0, index;
    if (verificaSobreposicao(a) == 1) return;
    while (strcmp(tab_eventos[i].descricao, nulo.descricao) != 0 && i < MAX_LEN) i++;
    tab_eventos[i] = a;
    index = i;
    i = 0;
    while (tab_salas[a.sala - 1][i] != -1 && i < MAX_EVENTOS) i++;
    tab_salas[a.sala - 1][i] = index;
}

evento criaEvento(char descricao[], int data, int inicio, int duracao, int sala, char responsavel[], char participantes[]) {
    evento a;
    strcpy(a.descricao, descricao);
    a.data = data;
    a.inicio = inicio;
    a.duracao = duracao;
    a.sala = sala;
    strcpy(a.responsavel, responsavel);
    strcpy(a.participantes_str, participantes);
    a = separaParticipantes(a, participantes);
    a.horario.amd = transformaData(a);
    a.horario.dia = a.horario.amd % 100;
    a.horario.mes = (a.horario.amd % 10000) / 100;
    a.horario.ano = a.horario.amd / 10000;
    a.horario.minutos = a.inicio % 100;
    a.horario.hora = a.inicio / 100;
    return a;
}

void listaEventos() {
    int i = 0;
    for (; i < MAX_LEN; i++) {
        if (strcmp(tab_eventos[i].descricao, nulo.descricao) != 0) printf("%s %02d/%02d/%02d %02d:%02d %02d Sala%d %s\n* %s\n", tab_eventos[i].descricao, tab_eventos[i].horario.dia, tab_eventos[i].horario.mes, tab_eventos[i].horario.ano, tab_eventos[i].horario.hora, tab_eventos[i].horario.minutos, tab_eventos[i].duracao, tab_eventos[i].sala, tab_eventos[i].responsavel, tab_eventos[i].participantes_str);
    }
}

void listaSala(int sala) {
    int i = 0;
    for(; i < MAX_EVENTOS; i++) {
        if (strcmp(tab_eventos[tab_salas[sala - 1][i]].descricao, nulo.descricao) != 0 && tab_salas[sala - 1][i] != -1)
            printf("%s %02d/%02d/%02d %02d:%02d %02d Sala%d %s\n* %s\n", tab_eventos[tab_salas[sala - 1][i]].descricao, tab_eventos[tab_salas[sala - 1][i]].horario.dia, tab_eventos[tab_salas[sala - 1][i]].horario.mes, tab_eventos[tab_salas[sala - 1][i]].horario.ano, tab_eventos[tab_salas[sala - 1][i]].horario.hora, tab_eventos[tab_salas[sala - 1][i]].horario.minutos, tab_eventos[tab_salas[sala - 1][i]].duracao, tab_eventos[tab_salas[sala - 1][i]].sala, tab_eventos[tab_salas[sala - 1][i]].responsavel, tab_eventos[tab_salas[sala - 1][i]].participantes_str);
    }
}

void apagaEvento(char descricao[]) {
    int index;
    index = procuraEvento(descricao);
    if (index != -1) {
        for (; index < MAX_LEN; index++) {
            tab_eventos[index] = tab_eventos[index + 1];
            }
        }
    else printf("Evento %s inexistente", descricao);
}

void alteraInicio(char descricao[], int novo_inicio) {    
    int index;
    index = procuraEvento(descricao);
    if (index != -1) tab_eventos[index].inicio = novo_inicio;
    else printf("Evento %s inexistente", descricao);
}

void alteraDuracao(char descricao[], int nova_duracao) {
    int index;
    index = procuraEvento(descricao);
    tab_eventos[index].duracao = nova_duracao;
}

void mudaSala(char descricao[], int nova_sala) {
    int index;
    index = procuraEvento(descricao);
    tab_eventos[index].sala = nova_sala;
}

int main() {
    char descricao[DESCRICAO], responsavel[PESSOA_RESP], participantes[LST_PARTICIPANTES];
    int data = 0, inicio = 0, duracao = 0, sala = 0, novo_inicio = 0;
    evento a;
    strcpy(nulo.descricao, "nulo");
    nulo.sala = 0;
    inicializaTabelas();
    while (TRUE) {
        switch(getchar()) {
        case 'a' :
            scanf(" %[^:]:%d:%d:%d:%d:%[^:]:%[^\n]", descricao, &data, &inicio, &duracao, &sala, responsavel, participantes);
            a = criaEvento(descricao, data, inicio, duracao, sala, responsavel, participantes);
            adicionaEvento(a);
            break;
        case 'l' :
            listaEventos();
            break;
        case 's' :
            scanf(" %d", &sala);
            listaSala(sala);
            break;
        case 'r' : /* falta tratar do ultimo slot do vetor evento */
            scanf(" %s", descricao);
            apagaEvento(descricao);
            break;
        case 'i' :
            scanf(" %[^:]:%d", descricao, &novo_inicio); /* adicionar erros caso o evento exista */
            alteraInicio(descricao, novo_inicio);
            break;
        case 'x':
            return 0;
            break;
        }
        getchar(); /* le o \n */
    }
   return 0;
}

void insertionSort(int arr[], int n) { 
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


