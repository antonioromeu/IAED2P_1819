#include <stdlib.h>
#include "Hash.h"

static int N, M;
linkHash *st;

int hashU(char *v, int M) {
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a * b % (M-1)) h = (a * h + *v) % M;
    return h;
}

void HSinit(int max) {
    int i;
    N = 0;
    M = 2 * max;
    st = (linkHash*) malloc(sizeof(linkHash) * M);
    for (i = 0; i < M; i++) st[i] = NULLlink;
}

void HSinsert(Key domain) {
    Key v = domain;
    int i = hashU(v, M);
    while (st[i] != NULLlink) i = (i + 1) % M;
    st[i]->domain = domain;
    N++;
}

linkHash HSsearch(Key domain) {
    Key v = domain;
    int i = hashU(v, M);
    while (st[i] != NULLlink) {
        if (eq(v, st[i]->domain)) return st[i];
        else i = (i + 1) % M;
    }
    return NULLlink;
}

linkHash HSdelete(Key domain) {
    Key v = domain;
    int j, i = hashU(v, M);
    linkHash aux;
    while (st[i] != NULLlink) {
        if (eq(v, st[i]->domain)) break;
        else i = (i + 1) % M;
    }
    if (st[i] == NULLlink) return NULLlink;
    aux = st[i];
    st[i] = NULLlink;
    N--;
    for (j = (i + 1) % M; st[j] != NULLlink; j = (j + 1) % M, N--) {
        v = st[j]->domain;
        st[j] = NULLlink;
        HSinsert(v);
    }
    return aux;
}

void HSincrement(Key domain) {
    linkHash res = HSsearch(domain);
    if (res == NULLlink) HSinsert(domain);
    else res->n++;
    return;
}

void HSdecrement(Key domain) {
    linkHash res = HSsearch(domain);
    if (res == NULLlink) return;
    if (res->n == 1) {
        res->n--;
        HSdelete(domain);
    }
    else res->n--;
}
