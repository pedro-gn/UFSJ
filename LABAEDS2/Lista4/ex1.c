#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int itens[MAX];
    int quantidade;
} Lista;

void inicializaLista(Lista* l) {
    l->quantidade = 0;
}

bool listaVazia(const Lista* l) {
    return l->quantidade == 0;
}

bool listaCheia(const Lista* l) {
    return l->quantidade == MAX;
}

int Procura(const Lista* l, int x) {
    for (int i = 0; i < l->quantidade; i++) {
        if (l->itens[i] == x) {
            return i; 
        }
    }
    return -1; 
}

bool insereOrdenado(Lista* l, int x) {
    if (listaCheia(l)) {
        return false;
    }

    int i = 0;
    while (i < l->quantidade && l->itens[i] < x) {
        i++;
    }

    for (int j = l->quantidade; j > i; j--) {
        l->itens[j] = l->itens[j - 1];
    }

    l->itens[i] = x;
    l->quantidade++;
    return true;
}

bool removeElemento(Lista* l, int x) {
    int index = Procura(l, x);
    if (index == -1) {
        return false;
    }

    for (int i = index; i < l->quantidade - 1; i++) {
        l->itens[i] = l->itens[i + 1];
    }

    l->quantidade--;
    return true;
}