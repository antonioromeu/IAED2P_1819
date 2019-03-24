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
    char participantes[LST_PARTICIPANTES];
    int data;
    int inicio;
    int duracao;
    int sala;
    data horario;
} evento;

evento tab_eventos[MAX_LEN];
evento tab_salas[MAX_SALAS][MAX_EVENTOS];
evento nulo;

void inicializaTabelas() {
    int i = 0, j = 0, k = 0;
    for (; i < MAX_LEN; i++) {
        tab_eventos[i] = nulo;
    }

    for (; j < MAX_SALAS; j++) {
        for (; k < MAX_EVENTOS; k++) {
            tab_salas[j][k] = nulo;
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
    if (a.sala != b.sala) return FALSE;
    else if (transformaData(a) > transformaData(b) || transformaData(a) < transformaData(b)) return FALSE;
    else if (a.inicio != b.inicio) return FALSE;
    else if (inicioParaMinutos(a.inicio) > inicioParaMinutos(b.inicio) && (inicioParaMinutos(a.inicio) + a.duracao) < inicioParaMinutos(b.inicio)) return FALSE;
    return TRUE;
}

int procuraEvento(char descricao[]) {
    int i = 0;
    for (; i < MAX_LEN; i++) {
        if (strcmp(tab_eventos[i].descricao, descricao) == 0) return i;
    }
    return -1;
}

void adicionaEvento(char descricao[], int data, int inicio, int duracao, int sala, char responsavel[], char participantes[]) {
    int i = 0;
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
    a.horario.minutos = a.inicio % 100;
    a.horario.hora = a.inicio / 100;
    while (strcmp(tab_eventos[i].descricao, nulo.descricao) != 0 && i < MAX_LEN) i++;
    tab_eventos[i] = a;
    i = 0;
    while (strcmp(tab_salas[a.sala - 1][i].descricao, nulo.descricao) != 0 && i < MAX_EVENTOS) i++;
    tab_salas[a.sala - 1][i] = a;
}

void listaEventos() {
    int i = 0;
    for (; strcmp(tab_eventos[i].descricao, nulo.descricao) != 0 && i < MAX_LEN; i++) {
        printf("%s %02d/%02d/%02d %02d:%02d %02d Sala%d %s\n* %s\n", tab_eventos[i].descricao, tab_eventos[i].horario.dia, tab_eventos[i].horario.mes, tab_eventos[i].horario.ano, tab_eventos[i].horario.hora, tab_eventos[i].horario.minutos, tab_eventos[i].duracao, tab_eventos[i].sala, tab_eventos[i].responsavel, tab_eventos[i].participantes);
    }
}

void listaSala(int sala) {
    int i = 0;
    for (; strcmp(tab_salas[sala - 1][i].descricao, nulo.descricao) != 0 && i < MAX_EVENTOS; i++) {
        printf("%s %02d/%02d/%02d %02d:%02d %02d Sala%d %s\n* %s\n", tab_salas[sala - 1][i].descricao, tab_salas[sala - 1][i].horario.dia, tab_salas[sala - 1][i].horario.mes, tab_salas[sala - 1][i].horario.ano, tab_salas[sala - 1][i].horario.hora, tab_salas[sala - 1][i].horario.minutos, tab_salas[sala - 1][i].duracao, tab_salas[sala - 1][i].sala, tab_salas[sala - 1][i].responsavel, tab_salas[sala - 1][i].participantes);
    }
}

void apagaEvento(char descricao[]) {
    int index;
    index = procuraEvento(descricao);
    for (; index < MAX_LEN; index++) {
        tab_eventos[index] = tab_eventos[index + 1];
    }
}

void alteraInicio(char descricao[], int novo_inicio) {    
    int index = 0;
    index = procuraEvento(descricao);
    tab_eventos[index].inicio = novo_inicio;
}

void alteraDuracao(char descricao[], int nova_duracao) {
    int index = 0;
    index = procuraEvento(descricao);
    tab_eventos[index].duracao = nova_duracao;
}

void mudaSala(char descricao[], int nova_sala) {
    int index = 0;
    index = procuraEvento(descricao);
    tab_eventos[index].sala = nova_sala;
}

int main() {
    char descricao[DESCRICAO], responsavel[PESSOA_RESP], participantes[LST_PARTICIPANTES], novo_participante[DESCRICAO];
    int novo_inicio = 0, nova_duracao = 0, nova_sala = 0, n_evento = 0, data = 0, inicio = 0, duracao = 0, sala = 0;
    strcpy(nulo.descricao, "nulo");
    inicializaTabelas();
    while (TRUE) {
        switch(getchar()) {
        case 'a' :
            scanf(" %[^:]:%d:%d:%d:%d:%[^:]:%[^\n]", descricao, &data, &inicio, &duracao, &sala, responsavel, participantes);
            adicionaEvento(descricao, data, inicio, duracao, sala, responsavel, participantes);
            n_evento++;
            break;
        case 'l' :
            listaEventos();
            break;
        case 's' :
            listaSala(sala);
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
