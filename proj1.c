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
    int dia, mes, ano, amd, hora, minutos;
} data;

typedef struct {
    char descricao[DESCRICAO], responsavel[PESSOA_RESP], participantes_str[LST_PARTICIPANTES], participantes[3][PESSOA_RESP];
    int data, inicio, duracao, sala, n_participantes;
    data horario;
} evento;

evento tab_eventos[MAX_LEN], nulo;
int contador_eventos = 0;

void inicializaTabelas() {
    int i;
    for (i = 0; i < MAX_LEN; i++) {
        tab_eventos[i] = nulo;
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

int verificaSobreposicaoSalas(evento a) {
    int i = 0, res = 0;
    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && (sobreposto(a, tab_eventos[i])) && (a.sala == tab_eventos[i].sala)) {
            printf("Impossivel agendar evento %s. Sala%d ocupada.\n", a.descricao, a.sala);
            res += 1;
        }
    }
    return res;
}

int verificaSobreposicaoResponsavel(evento a) {
    int i = 0, k = 0, res = 0;
    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && (sobreposto(a, tab_eventos[i])) && (strcmp(a.responsavel, tab_eventos[i].responsavel) == 0)) {
            printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.responsavel);
            res = 1;
        }
    }

    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && sobreposto(a, tab_eventos[i])) {
            for (k = 0; k < 3; k++) {
                if (strcmp(a.responsavel, tab_eventos[i].participantes[k]) == 0) {
                    printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.responsavel);
                    res = 1;
                }
            }
        }
    }
    return res;
}

int verificaSobreposicaoParticipantes(evento a) {
    int i = 0, k = 0, j = 0, res = 0;
    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && (sobreposto(a, tab_eventos[i]))) {
            for (j = 0; j < 3; j++) {
                if (strcmp(a.participantes[j], tab_eventos[i].responsavel) == 0 && (a.participantes[j][0] != '\0')) {
                    printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participantes[j]);
                    res = 1;
                    }
                }
            }
        }

    for (i = 0; i < contador_eventos; i++) {
        if ((strcmp(a.descricao, tab_eventos[i].descricao) != 0) && (sobreposto(a, tab_eventos[i]))) {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 3; k++) {
                    if (strcmp(a.participantes[j], tab_eventos[i].participantes[k]) == 0 && (a.participantes[j][0] != '\0')) {
                        printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n", a.descricao, a.participantes[j]);
                        res = 1;
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
    if (res != 0) return;
    res += verificaSobreposicaoResponsavel(a);
    res += verificaSobreposicaoParticipantes(a);
    if (res != 0) return;
    else tab_eventos[contador_eventos] = a;
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
    tab_eventos[index].inicio = inicio;
}

void mudaDuracao(char descricao[], int duracao) {
    int index = procuraEvento(descricao);
    tab_eventos[index].duracao = duracao;
}

void mudaSala(char descricao[], int sala) {
    int index = procuraEvento(descricao);
    tab_eventos[index].sala = sala;
}

void sortL() {
    int i, j;
    evento temp;
    for (i = 1; i < contador_eventos; i++) {
        temp = tab_eventos[i];
        j = i - 1;
        if (tab_eventos[j].inicio == temp.inicio) {
            while (j >= 0 && tab_eventos[j].sala > temp.sala) {
                tab_eventos[j + 1] = tab_eventos[j];
                j -= 1;
            }
            tab_eventos[j + 1] = temp;
        }
        else {
            while (j >= 0 && tab_eventos[j].inicio > temp.inicio) {
                tab_eventos[j + 1] = tab_eventos[j];
                j -= 1;
            }
            tab_eventos[j + 1] = temp;
        }
    }
}

void sortS(){
    int i, j;
    evento temp; 
    for (i = 1; i < contador_eventos; i++) { 
        temp = tab_eventos[i];
        j = i - 1;
        if (tab_eventos[j].horario.amd == temp.horario.amd) {
            while (j >= 0 && tab_eventos[j].inicio > temp.inicio) {
                tab_eventos[j + 1] = tab_eventos[j];
                j -= 1;
            }
            tab_eventos[j + 1] = temp;
        }
        else {
            while (j >= 0 && tab_eventos[j].horario.amd > temp.horario.amd) {
                tab_eventos[j + 1] = tab_eventos[j];
                j -= 1;
            }
            tab_eventos[j + 1] = temp;
        }
    }
}

void listaEventos() {
    int i = 0;
    for (; i < contador_eventos; i++) {
        if (strcmp(tab_eventos[i].descricao, nulo.descricao) != 0) {
            printf("%s %02d%02d%02d %02d%02d %d Sala%d %s\n*", tab_eventos[i].descricao, tab_eventos[i].horario.dia, tab_eventos[i].horario.mes, tab_eventos[i].horario.ano, tab_eventos[i].horario.hora, tab_eventos[i].horario.minutos, tab_eventos[i].duracao, tab_eventos[i].sala, tab_eventos[i].responsavel);
            imprimeParticipantes(tab_eventos[i]);
        }
    }
}

void listaSala(int sala) {
    int i = 0;
    for (; i < contador_eventos; i++) {
        if (tab_eventos[i].sala == sala) {
            printf("%s %02d%02d%02d %02d%02d %d Sala%d %s\n*", tab_eventos[i].descricao, tab_eventos[i].horario.dia, tab_eventos[i].horario.mes, tab_eventos[i].horario.ano, tab_eventos[i].horario.hora, tab_eventos[i].horario.minutos, tab_eventos[i].duracao, tab_eventos[i].sala, tab_eventos[i].responsavel);
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
    else printf("Evento %s inexistente.\n", descricao);
}

void alteraDuracao(char descricao[], int nova_duracao) {
    int res = 0, index;
    evento temp;
    index = procuraEvento(descricao);
    if (index != -1) {
        temp = tab_eventos[index];
        temp.duracao = nova_duracao;
        res += verificaSobreposicaoSalas(temp);
        if (res != 0) return;
        res += verificaSobreposicaoResponsavel(temp);
        res += verificaSobreposicaoParticipantes(temp);
        if (res != 0) return;
        mudaDuracao(descricao, nova_duracao);
    }
    else printf("Evento %s inexistente.\n", descricao);
}

void alteraSala(char descricao[], int nova_sala) {
    int res = 0, index;
    evento temp;
    index = procuraEvento(descricao);
    if (index != -1) {
        temp = tab_eventos[index];
        temp.sala = nova_sala;
        res += verificaSobreposicaoSalas(temp);
        if (res != 0) return;
        res += verificaSobreposicaoResponsavel(temp);
        res += verificaSobreposicaoParticipantes(temp);
        if (res != 0) return;
        mudaSala(descricao, nova_sala);
    }
    else printf("Evento %s inexistente.\n", descricao);
}

void adicionaParticipante(char descricao[], char participante[]) {
    int index, i, res = 0;
    char copia[PESSOA_RESP+1];
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
    copia[0] = ' ';
    strcat(copia, participante);
    strcat(tab_eventos[index].participantes_str, copia);
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
    char descricao[DESCRICAO], responsavel[PESSOA_RESP], participante[PESSOA_RESP], novo_participante[PESSOA_RESP], participantes[LST_PARTICIPANTES];
    int data = 0, inicio = 0, duracao = 0, sala = 0, novo_inicio = 0, nova_duracao = 0, nova_sala = 0;
    evento a;
    inicializaTabelas();
    while (TRUE) {
        switch(getchar()) {
        case 'a' :
            scanf(" %[^:]:%d:%d:%d:%d:%[^:]:%[^\n]", descricao, &data, &inicio, &duracao, &sala, responsavel, participantes);
            a = criaEvento(descricao, data, inicio, duracao, sala, responsavel, participantes);
            adicionaEvento(a);
            contador_eventos++;
            break;
        case 'l' :
            sortL();
            listaEventos();
            break;
        case 's' :
            scanf(" %d", &sala);
            sortS();
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
