#include "TreeDomain.h"

struct STnode {
    ItemD item;
    linkD l, r;
    int height; /*keeps the height of the node*/
};

ItemD NULLitemD = NULL;

int heightD(linkD h) {
    if (h == NULL) return 0;
    return h->height;
}

linkD rotLD(linkD h) {
    int height_left, height_right;
    linkD x = h->r;
    h->r = x->l;
    x->l = h;
    height_left = heightD(h->l); height_right = heightD(h->r);
    h->height = height_left > height_right ? height_left + 1 : height_right + 1;
    height_left = heightD(x->l); height_right = heightD(x->r);
    x->height = height_left > height_right ? height_left + 1 : height_right + 1;
    return x;
}

linkD rotRD(linkD h) {
    int height_left, height_right;
    linkD x = h->l;
    h->l = x->r;
    x->r = h;
    height_left = heightD(h->l); height_right = heightD(h->r);
    h->height = height_left > height_right ? height_left + 1 : height_right + 1;
    height_left = heightD(x->l); height_right = heightD(x->r);
    x->height = height_left > height_right ? height_left + 1 : height_right + 1;
    return x;
}

linkD rotLRD(linkD h) { /*double rotation left right*/
    if (h == NULL) return h;
    h->l = rotLD(h->l);
    return rotRD(h);
}

linkD rotRLD(linkD h) { /*double rotation right left*/
    if (h == NULL) return h;
    h->r = rotRD(h->r);
    return rotLD(h);
}

int BalanceD(linkD h) { /*balance factor*/
    if(h == NULL) return 0;
    return (heightD(h->l) - heightD(h->r));
}

linkD AVLbalanceD(linkD h) {
    int balanceFactor;
    if (h == NULL) return h;
    balanceFactor = BalanceD(h);
    if(balanceFactor > 1) {
        if (BalanceD(h->l) >= 0) h = rotRD(h);
        else h = rotLRD(h);
    }
    else if(balanceFactor <- 1) {
        if (BalanceD(h->r) <= 0) h = rotLD(h);
        else h = rotRLD(h);
    }
    else {
        int height_left = heightD(h->l);
        int height_right = heightD(h->r);
        h->height = height_left > height_right ? height_left + 1 : height_right + 1;
    }
    return h;
}

linkD NEWD(ItemD item, linkD l, linkD r) {
    linkD x = (linkD) malloc(sizeof(struct STnode));
    x->item = item;
    x->l = l;
    x->r = r;
    x->height = 1;
    return x;
}

linkD insertRD(linkD h, ItemD item) {
    if (h == NULL) return NEWD(item, NULL, NULL);
    if (lessD(keyD(item), keyD(h->item))) h->l = insertRD(h->l, item);
    else h->r = insertRD(h->r, item);
    h = AVLbalanceD(h);
    return h;
}

ItemD searchRD(linkD h, KeyD v) {
    if (h == NULL) return NULLitemD;
    if (eqD(v, keyD(h->item))) return h->item;
    if (lessD(v, keyD(h->item))) return searchRD(h->l, v);
    else return searchRD(h->r, v);
}

linkD maxD(linkD h) {
    if (h == NULL || h->r == NULL) return h;
    else return maxD(h->r);
}

linkD deleteRD(linkD h, KeyD k) {
    if (h == NULL) return h;
    else if (lessD(k, keyD(h->item))) h->l = deleteRD(h->l, k);
    else if (lessD(keyD(h->item), k)) h->r = deleteRD(h->r, k);
    else { /* case 3 */
        if (h->l != NULL && h->r != NULL) {
            linkD aux = maxD(h->l);
            { ItemD x; x = h->item; h->item = aux->item; aux->item = x; }
            h->l = deleteRD(h->l, keyD(aux->item));
        }
        else { /*cases 1 and 2*/
            linkD aux = h;
            if (h->l == NULL && h->r == NULL) h = NULL;
            else if (h->l == NULL) h = h->r;
            else h = h->l;
            deleteItemD(aux->item);
            free(aux);
        }
    }
    h = AVLbalanceD(h);
    return h;
}

int countD(linkD h) {
    if (h == NULL) return 0;
    else return (countD(h->r) + countD(h->l) + 1);
}

void sortRD(linkD h, void (*visit)(ItemD)) {
    if (h == NULL) return;
    sortRD(h->l, visit);
    visit(h->item);
    sortRD(h->r, visit);
}

linkD freeRD(linkD h) {
    if (h == NULL) return h;
    h->l = freeRD(h->l);
    h->r = freeRD(h->r);
    return deleteRD(h, keyD(h->item));
}

void STDinit(linkD *head) {
    *head = NULL;
}

void STDinsert(linkD *head, ItemD item) {
    *head = insertRD(*head, item);
}

ItemD STDsearch(linkD head, KeyD v) {
    return searchRD(head, v);
}

int STDcount(linkD head) {
    return countD(head);
}

void STDdelete(linkD*head, KeyD k) {
    *head = deleteRD(*head, k);
}

void STDsort(linkD head, void (*visit)(ItemD)) {
    sortRD(head, visit);
}

void STDfree(linkD *head) {
    *head = freeRD(*head);
}
