#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int dado;
    struct No* proximo;
} No;

typedef struct {
    No* cabeca;
} ListaCircular;

void inicializaLista(ListaCircular* l) {
    l->cabeca = NULL;
}

bool listaVazia(const ListaCircular* l) {
    return l->cabeca == NULL;
}
void insereOrdenado(ListaCircular* l, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    novoNo->dado = valor;

    if (listaVazia(l)) {
        novoNo->proximo = novoNo; // A lista é circular, então ela aponta para si mesma
        l->cabeca = novoNo;
    } else {
        if (valor < l->cabeca->dado) {
            No* atual = l->cabeca;
            while (atual->proximo != l->cabeca) {
                atual = atual->proximo;
            }
            novoNo->proximo = l->cabeca;
            atual->proximo = novoNo;
            l->cabeca = novoNo;
        } else {
            No* atual = l->cabeca;
            while (atual->proximo != l->cabeca && atual->proximo->dado < valor) {
                atual = atual->proximo;
            }
            novoNo->proximo = atual->proximo;
            atual->proximo = novoNo;
        }
    }
}
No* Procura(const ListaCircular* l, int valor) {
    if (listaVazia(l)) return NULL;

    No* atual = l->cabeca;
    do {
        if (atual->dado == valor) {
            return atual;
        }
        atual = atual->proximo;
    } while (atual != l->cabeca);
    
    return NULL;
}

bool removeElemento(ListaCircular* l, int valor) {
    if (listaVazia(l)) return false;

    No* atual = l->cabeca;
    No* anterior = NULL;
    do {
        if (atual->dado == valor) {
            if (anterior) {
                anterior->proximo = atual->proximo;
                if (atual == l->cabeca) {
                    l->cabeca = anterior->proximo;
                }
            } else {
                if (atual->proximo == atual) { // único elemento
                    l->cabeca = NULL;
                } else {
                    No* temp = atual;
                    while (atual->proximo != temp) {
                        atual = atual->proximo;
                    }
                    l->cabeca = temp->proximo;
                    atual->proximo = l->cabeca;
                }
            }
            free(atual);
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    } while (atual != l->cabeca);

    return false;
}

void liberaLista(ListaCircular* l) {
    if (listaVazia(l)) return;

    No* atual = l->cabeca->proximo;
    while (atual != l->cabeca) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(l->cabeca);
    l->cabeca = NULL;
}

void imprimeLista(const ListaCircular* l) {
    if (listaVazia(l)) return;

    No* atual = l->cabeca;
    do {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    } while (atual != l->cabeca);
    printf("%d (cabeça)\n", l->cabeca->dado);
}

int main() {
    ListaCircular l;
    inicializaLista(&l);

    insereOrdenado(&l, 5);
    insereOrdenado(&l, 3);
    insereOrdenado(&l, 7);
    insereOrdenado(&l, 4);

    imprimeLista(&l);

    if (Procura(&l, 5)) {
        printf("5 encontrado na lista!\n");
    } else {
        printf("5 não encontrado na lista.\n");
    }

    removeElemento(&l, 5);
    imprimeLista(&l);

    if (Procura(&l, 5)) {
        printf("5 encontrado na lista!\n");
    } else {
        printf("5 não encontrado na lista.\n");
    }

    liberaLista(&l);
    return 0;
}