#ifndef FSE_H
#define FSE_H

typedef struct NO {
    int info;
    struct NO* prox;
} NO;

typedef struct {
    int qtd;
    NO* ini;
    NO* fim;
} Fila;

Fila* criarFila();
int enfileirar(Fila* f, int valor);
int desenfileirar(Fila* f, int* valor);
int verInicio(Fila* f, int* valor);
void imprimirFila(Fila* f);
void destruirFila(Fila* f);

#endif
