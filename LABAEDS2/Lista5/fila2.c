#include "fila2.h"
#include <stdlib.h>
#include <stdio.h>

Fila* criarFila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if (f) {
        f->qtd = 0;
        f->ini = NULL;
        f->fim = NULL;
    }
    return f;
}

int enfileirar(Fila* f, int valor) {
    if (!f) return 0;

    NO* novo = (NO*)malloc(sizeof(NO));
    if (!novo) return 0;

    novo->info = valor;
    novo->prox = NULL;

    if (!f->ini) f->ini = novo;
    else f->fim->prox = novo;

    f->fim = novo;
    f->qtd++;
    return 1;
}

int desenfileirar(Fila* f, int* valor) {
    if (!f || !f->ini) return 0;

    NO* temp = f->ini;
    *valor = temp->info;
    f->ini = f->ini->prox;
    
    free(temp);
    f->qtd--;

    if (!f->ini) f->fim = NULL;
    return 1;
}

int verInicio(Fila* f, int* valor) {
    if (!f || !f->ini) return 0;
    
    *valor = f->ini->info;
    return 1;
}

void imprimirFila(Fila* f) {
    NO* temp = f->ini;
    while (temp) {
        printf("%d ", temp->info);
        temp = temp->prox;
    }
    printf("\n");
}

void destruirFila(Fila* f) {
    NO* temp;
    while (f->ini) {
        temp = f->ini;
        f->ini = f->ini->prox;
        free(temp);
    }
    free(f);
}
