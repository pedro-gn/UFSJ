#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int dado;
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct {
    No* cabeca;
    No* cauda;
} ListaDuplamenteEncadeada;

void inicializaLista(ListaDuplamenteEncadeada* l) {
    l->cabeca = NULL;
    l->cauda = NULL;
}

bool listaVazia(const ListaDuplamenteEncadeada* l) {
    return l->cabeca == NULL;
}

void insereOrdenado(ListaDuplamenteEncadeada* l, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    novoNo->dado = valor;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;

    if (listaVazia(l)) {
        l->cabeca = novoNo;
        l->cauda = novoNo;
        return;
    }

    if (valor < l->cabeca->dado) {
        novoNo->proximo = l->cabeca;
        l->cabeca->anterior = novoNo;
        l->cabeca = novoNo;
        return;
    }

    if (valor > l->cauda->dado) {
        novoNo->anterior = l->cauda;
        l->cauda->proximo = novoNo;
        l->cauda = novoNo;
        return;
    }

    No* atual = l->cabeca;
    while (atual->proximo != NULL && atual->proximo->dado < valor) {
        atual = atual->proximo;
    }

    novoNo->proximo = atual->proximo;
    novoNo->anterior = atual;
    if (atual->proximo) {
        atual->proximo->anterior = novoNo;
    }
    atual->proximo = novoNo;
}

No* Procura(const ListaDuplamenteEncadeada* l, int valor) {
    No* atual = l->cabeca;
    while (atual != NULL && atual->dado != valor) {
        atual = atual->proximo;
    }
    return atual;
}

bool removeElemento(ListaDuplamenteEncadeada* l, int valor) {
    No* noParaRemover = Procura(l, valor);
    if (!noParaRemover) return false;

    if (noParaRemover->anterior) {
        noParaRemover->anterior->proximo = noParaRemover->proximo;
    } else {
        l->cabeca = noParaRemover->proximo;
    }

    if (noParaRemover->proximo) {
        noParaRemover->proximo->anterior = noParaRemover->anterior;
    } else {
        l->cauda = noParaRemover->anterior;
    }

    free(noParaRemover);
    return true;
}

void liberaLista(ListaDuplamenteEncadeada* l) {
    No* atual = l->cabeca;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    l->cabeca = NULL;
    l->cauda = NULL;
}

void imprimeLista(const ListaDuplamenteEncadeada* l) {
    No* atual = l->cabeca;
    printf("NULL <-> ");
    while (atual != NULL) {
        printf("%d <-> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

int main() {
    ListaDuplamenteEncadeada l;
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
