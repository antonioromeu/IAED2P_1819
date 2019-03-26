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
int contador_eventos = 0;
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
    else if (inicioParaMinutos(a.inicio) > (inicioParaMinutos(b.inicio) + b.duracao - 1) || inicioParaMinutos(b.inicio) > (inicioParaMinutos(a.inicio) + a.duracao - 1)) return FALSE;
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

int verificaSobreposicaoSalas(evento a) {
    int i = 0, res = 0;
    for (; i < contador_eventos; i++) {
        if (strcmp(a.descricao, tab_eventos[i].descricao) != 0) {
            if (sobreposto(a, tab_eventos[i])){
                if (a.sala == tab_eventos[i].sala) {
                    printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
                    res = 1;
                }
            }
        }
    }
    return res;
}

int verificaSobreposicaoResponsavel(evento a) {
    int i = 0, k = 0, res = 0;
    for (i = 0; i < contador_eventos; i++) {
        if (strcmp(a.descricao, tab_eventos[i].descricao) != 0) {
            if (sobreposto(a, tab_eventos[i])) {
                if (strcmp(a.responsavel, tab_eventos[i].responsavel) == 0) {
                    printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.responsavel);
                    res = 1;
                }
            }
        }
    }

    for (i = 0; i < contador_eventos; i++) {
        if (strcmp(a.descricao, tab_eventos[i].descricao) != 0) {
            if (sobreposto(a, tab_eventos[i])) {
                for (k = 0; k < 3; k++) {
                    if (strcmp(a.responsavel, tab_eventos[i].participantes[k]) == 0) {
                        printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.responsavel);
                        res = 1;
                    }
                }
            }
        }
    }
    return res;
}

int verificaSobreposicaoParticipantes(evento a) {
    int i = 0, k = 0, j = 0, res = 0;
    for (i = 0; i < contador_eventos; i++) {
        if (strcmp(a.descricao, tab_eventos[i].descricao) != 0) {
            if (sobreposto(a, tab_eventos[i])) {
                for (j = 0; j < 3; j++) {
                    if (strcmp(a.participantes[j], tab_eventos[i].responsavel) == 0) {
                        printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participantes[j]);
                        res = 1;
                    }
                }
            }
        }
    }
    for (i = 0; i < contador_eventos; i++) {
        if (strcmp(a.descricao, tab_eventos[i].descricao) != 0) {
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
    }

    return res;
}

int verificaMaxParticipantes(evento a) {
    int i = 0, k = 0;
    for (; i < 3; i++) {
        for (; k < 3; k++) {
            
        }
    }
}

int procuraEvento(char descricao[]) {
    int i = 0;
    for (; i < contador_eventos; i++) {
        if (strcmp(tab_eventos[i].descricao, descricao) == 0) return i;
    }
    return -1;
}

void adicionaEvento(evento a) {
    int res = 0;
    res += verificaSobreposicaoSalas(a);
    res += verificaSobreposicaoResponsavel(a);
    res += verificaSobreposicaoParticipantes(a);
    if (res != 0) return;
    else tab_eventos[contador_eventos] = a;
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

void mudaInicio(char descricao[], int inicio) {
    int index = procuraEvento(descricao);
    tab_eventos[index].horario.minutos = inicio % 100;
    tab_eventos[index].horario.hora = inicio / 100;
}

void mudaDuracao(char descricao[], int duracao) {
    int index = procuraEvento(descricao);
    tab_eventos[index].duracao = duracao;
}

void mudaSala(char descricao[], int sala) {
    int index = procuraEvento(descricao);
    tab_eventos[index].sala = sala;
}

void listaEventos() {
    int i = 0;
    for (; i < contador_eventos; i++) {
        if (strcmp(tab_eventos[i].descricao, nulo.descricao) != 0) printf("%s %02d/%02d/%02d %02d:%02d %02d Sala%d %s\n* %s\n", tab_eventos[i].descricao, tab_eventos[i].horario.dia, tab_eventos[i].horario.mes, tab_eventos[i].horario.ano, tab_eventos[i].horario.hora, tab_eventos[i].horario.minutos, tab_eventos[i].duracao, tab_eventos[i].sala, tab_eventos[i].responsavel, tab_eventos[i].participantes_str);
    }
}

void listaSala(int sala) {
    int i = 0;
    for (; i < contador_eventos; i++) {
        if (tab_eventos[i].sala == sala) printf("%s %02d/%02d/%02d %02d:%02d %02d Sala%d %s\n* %s\n", tab_eventos[i].descricao, tab_eventos[i].horario.dia, tab_eventos[i].horario.mes, tab_eventos[i].horario.ano, tab_eventos[i].horario.hora, tab_eventos[i].horario.minutos, tab_eventos[i].duracao, tab_eventos[i].sala, tab_eventos[i].responsavel, tab_eventos[i].participantes_str);
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
    evento temp;
    index = procuraEvento(descricao);
    if (index != -1) {
        temp = tab_eventos[index];
        temp.inicio = novo_inicio;
        res += verificaSobreposicaoSalas(temp);
        if (res != 0) return;
        res += verificaSobreposicaoResponsavel(temp);
        res += verificaSobreposicaoParticipantes(temp);
        if (res != 0) return;
        mudaInicio(descricao, novo_inicio);
    }
    else printf("Evento %s inexistente\n", descricao);
}

void alteraDuracao(char descricao[], int nova_duracao) {
    int res = 0, index;
    evento temp;
    index = procuraEvento(descricao);
    if (index != -1) {
        temp = tab_eventos[index];
        temp.duracao = nova_duracao;
        res += verificaSobreposicaoSalas(temp);
        res += verificaSobreposicaoResponsavel(temp);
        res += verificaSobreposicaoParticipantes(temp);
        if (res != 0) return;
        mudaDuracao(descricao, nova_duracao);
    }
    else printf("Evento %s inexistente\n", descricao);
}

void alteraSala(char descricao[], int nova_sala) {
    int res = 0, index;
    evento temp;
    index = procuraEvento(descricao);
    if (index != -1) {
        temp = tab_eventos[index];
        temp.sala = nova_sala;
        res += verificaSobreposicaoSalas(temp);
        res += verificaSobreposicaoResponsavel(temp);
        res += verificaSobreposicaoParticipantes(temp);
        if (res != 0) return;
        mudaSala(descricao, nova_sala);
    }
    else printf("Evento %s inexistente\n", descricao);
}

void ordenaEventos() {
    int index = contador_eventos - 1;
    evento temp;
    for (; index > 0; index--) {
        if (tab_eventos[index - 1].horario.amd > tab_eventos[index].horario.amd) {
            temp = tab_eventos[index];
            tab_eventos[index] = tab_eventos[index - 1];
            tab_eventos[index - 1] = temp;
        }
        else if (inicioParaMinutos(tab_eventos[index - 1].inicio) > inicioParaMinutos(tab_eventos[index].inicio)) {
            temp = tab_eventos[index];
            tab_eventos[index] = tab_eventos[index - 1];
            tab_eventos[index - 1] = temp;
        }
        else if (inicioParaMinutos(tab_eventos[index - 1].inicio) == inicioParaMinutos(tab_eventos[index].inicio) && tab_eventos[index - 1].sala > tab_eventos[index].sala) {
            temp = tab_eventos[index];
            tab_eventos[index] = tab_eventos[index - 1];
            tab_eventos[index - 1] = temp;
        }
        else break;
    }
}

int main() {
    char descricao[DESCRICAO], responsavel[PESSOA_RESP], participantes[LST_PARTICIPANTES];
    int data = 0, inicio = 0, duracao = 0, sala = 0, novo_inicio = 0, nova_duracao = 0, nova_sala;
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
            /*for 
            if (strcmp(a.responsavel, tab_eventos[i].participantes[0]) == 0)*/
            contador_eventos++;
            ordenaEventos();
            break;
        case 'l' :
            listaEventos();
            break;
        case 's' :
            scanf(" %d", &sala);
            listaSala(sala);
            break;
        case 'r' :
            scanf(" %[^\n]", descricao);
            apagaEvento(descricao);
            ordenaEventos();
            break;
        case 'i' :
            scanf(" %[^:]:%d", descricao, &novo_inicio);
            alteraInicio(descricao, novo_inicio);
            ordenaEventos();
            break;
        case 't' :
            scanf(" %[^:]:%d", descricao, &nova_duracao);
            alteraDuracao(descricao, nova_duracao);
            ordenaEventos();
            break;
        case 'm' :
            scanf(" %[^:]:%d", descricao, &nova_sala);
            alteraSala(descricao, nova_sala);
            ordenaEventos();
            break;
        case 'x':
            return 0;
            break;
        }
        getchar(); /* le o \n */
    }
   return 0;
}
