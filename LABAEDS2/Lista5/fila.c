#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

Fila* criarFila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if (f) {
        f->inicio = 0;
        f->fim = 0;
    }
    return f;
}

int estaVazia(Fila* f) {
    return f->inicio == f->fim;
}

int enfileirar(Fila* f, int valor) {
    if ((f->fim + 1) % MAX == f->inicio) return 0; // fila cheia

    f->itens[f->fim] = valor;
    f->fim = (f->fim + 1) % MAX;
    return 1;
}

int desenfileirar(Fila* f, int* valor) {
    if (estaVazia(f)) return 0;

    *valor = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    return 1;
}

int verInicio(Fila* f, int* valor) {
    if (estaVazia(f)) return 0;
    
    *valor = f->itens[f->inicio];
    return 1;
}

void imprimirFila(Fila* f) {
    int i = f->inicio;
    while (i != f->fim) {
        printf("%d ", f->itens[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

void destruirFila(Fila* f) {
    free(f);
}
