#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int dado;
    struct No* proximo;
} No;

typedef struct {
    No* cabeca;
} ListaEncadeada;

void inicializaLista(ListaEncadeada* l) {
    l->cabeca = NULL;
}

bool listaVazia(const ListaEncadeada* l) {
    return l->cabeca == NULL;
}

void insereOrdenado(ListaEncadeada* l, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    novoNo->dado = valor;
    novoNo->proximo = NULL;

    if (listaVazia(l) || l->cabeca->dado > valor) {
        novoNo->proximo = l->cabeca;
        l->cabeca = novoNo;
        return;
    }

    No* atual = l->cabeca;
    while (atual->proximo != NULL && atual->proximo->dado < valor) {
        atual = atual->proximo;
    }

    novoNo->proximo = atual->proximo;
    atual->proximo = novoNo;
}

No* Procura(const ListaEncadeada* l, int valor) {
    No* atual = l->cabeca;
    while (atual != NULL && atual->dado != valor) {
        atual = atual->proximo;
    }
    return atual;
}

bool removeElemento(ListaEncadeada* l, int valor) {
    if (listaVazia(l)) return false;

    No* atual = l->cabeca;
    No* anterior = NULL;

    while (atual != NULL && atual->dado != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return false;

    if (anterior == NULL) {
        l->cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    return true;
}

void imprimeLista(const ListaEncadeada* l) {
    No* atual = l->cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

int main() {
    ListaEncadeada l;
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

    return 0;
}
