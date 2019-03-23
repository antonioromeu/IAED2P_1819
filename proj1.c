#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DESCRICAO 63
#define PESSOA_RESP 63
#define LST_PARTICIPANTES 191
#define MAX_SALAS 10
#define MAX_EVENTOS 100
#define FALSE 0
#define TRUE 1
#define MAX_LEN 1000

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
    char participantes[LST_PARTICIPANTES];
    int data;
    int inicio;
    int duracao;
    int sala;
    data horario;
} evento;

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
    if (a.sala != b.sala) return FALSE;
    else if (transformaData(a) > transformaData(b) || transformaData(a) < transformaData(b)) return FALSE;
    else if (a.inicio != b.inicio) return FALSE;
    else if (inicioParaMinutos(a.inicio) > inicioParaMinutos(b.inicio) && (inicioParaMinutos(a.inicio) + a.duracao) < inicioParaMinutos(b.inicio)) return FALSE;
    return TRUE;
}

int procuraEvento(char descricao[], evento tab_eventos[MAX_LEN]) {
    int i = 0;
    for (; i < MAX_LEN; i++) {
        if (strcmp(tab_eventos[i].descricao, descricao) == 0) return i;
    }
    return -1;
}

void adicionaEvento(char descricao[], int data, int inicio, int duracao, int sala, char responsavel[], char participantes[], evento tab_eventos[MAX_LEN], int n_evento) {
    evento a;
    strcpy(a.descricao, descricao);
    a.data = data;
    a.inicio = inicio;
    a.duracao = duracao;
    a.sala = sala;
    strcpy(a.responsavel, responsavel);
    strcpy(a.participantes, participantes);
    a.horario.amd = transformaData(a);
    a.horario.dia = a.horario.amd % 100;
    a.horario.mes = (a.horario.amd % 10000) / 100;
    a.horario.ano = a.horario.amd / 10000;
    tab_eventos[n_evento] = a;
}

int listaEventos(evento tab_eventos[MAX_LEN]) {
    int i = 0;
    for (; i < 1; i++) {
        printf("%s %d/%d/%d %d:%d %d Sala%d %s\n* %s\n", tab_eventos[i].descricao, tab_eventos[i].horario.dia, tab_eventos[i].horario.mes, tab_eventos[i].horario.ano, tab_eventos[i].horario.hora, tab_eventos[i].horario.minutos, tab_eventos[i].duracao, tab_eventos[i].sala, tab_eventos[i].responsavel, tab_eventos[i].participantes);
    }
}

void apagaEvento(char descricao[], evento tab_eventos[MAX_LEN]) {
    int index;
    index = procuraEvento(descricao, tab_eventos);
    for (; index < MAX_LEN; index++) {
        tab_eventos[index] = tab_eventos[index + 1];
    }
}

void alteraInicio(char descricao[], evento tab_eventos[MAX_LEN], int novo_inicio) {    
    int index;
    index = procuraEvento(descricao, tab_eventos);
    tab_eventos[index].inicio = novo_inicio;
}

/*void alteraDuracao(char descricao[], evento tab_eventos[MAX_LEN], int nova_duracao) {
    int index;
    index = procuraTabela(descricao, tab_eventos);
    tab_eventos[index].duracao = nova_duracao;
}*/

/*void mudaSala(char descricao[], evento tab_eventos[MAX_LEN], int nova_sala) {
    int index;
    index = procuraTabela(descricao, tab_eventos);
    tab_eventos[index].sala = nova_sala;
}*/

int main() {
    char funcao, descricao[DESCRICAO], responsavel[PESSOA_RESP], participantes[LST_PARTICIPANTES], novo_participante[DESCRICAO];
    int novo_inicio = 0, nova_duracao = 0, nova_sala = 0, n_evento = 0, data = 0, inicio = 0, duracao = 0, sala = 0;
    evento tab_eventos[MAX_LEN];
    evento tab_salas[MAX_SALAS][MAX_EVENTOS];
    funcao = getchar();
    while (TRUE) {
        switch(funcao) {
        case 'a' :
            scanf(" %[0-9a-zA-Z ]:%d:%d:%d:%d:%[0-9a-zA-Z ]:%[0-9a-zA-Z: ]\n", descricao, &data, &inicio, &duracao, &sala, responsavel, participantes);
            adicionaEvento(descricao, data, inicio, duracao, sala, responsavel, participantes, tab_eventos, n_evento);
            n_evento++;
            break;
        case 'l' :
            listaEventos(tab_eventos);
            break;
        case 's' :
            break;
        case 'r' :
            scanf(" %s", descricao);
            //apagaEvento(descricao, tab_eventos);
            break;
        case 'i' :
            scanf(" %s:%d", descricao, &novo_inicio);
            alteraInicio(descricao, tab_eventos, novo_inicio);
            break;
        case 't' :
            scanf(" %s:%d", descricao, &nova_duracao);
            //alteraDuracao(descricao, tab_eventos, nova_duracao);
            break;
        case 'm' :
            scanf(" %s:%d", descricao, &nova_sala);
            //mudaSala(descricao, tab_eventos, nova_sala);
            break;
        case 'A' :
            scanf(" %s:%s", descricao, novo_participante);
            //adicionaParticipante(descricao, tab_eventos, novo_participante);
            break;
        case 'R' :
            break;
        case 'T' :
            break;
        }
        funcao = getchar();
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
