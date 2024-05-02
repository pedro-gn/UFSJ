typedef struct ConjuntoInt ConjuntoInt;

// Cria um conjunto vazio
ConjuntoInt* cria_conjunto();


// Insere um elemento no conjunto
void insere_elemento(ConjuntoInt* conjunto, int valor);

// Remove um elemento do conjunto
void remove_elemento(ConjuntoInt* conjunto, int valor);

// União de dois conjuntos
ConjuntoInt* uniao(ConjuntoInt* a, ConjuntoInt* b);

// Intersecção de dois conjuntos
ConjuntoInt* interseccao(ConjuntoInt* a, ConjuntoInt* b);

// Diferença entre dois conjuntos
ConjuntoInt* diferenca(ConjuntoInt* a, ConjuntoInt* b);

// Testa se um número pertence ao conjunto
int pertence_conjunto(ConjuntoInt* conjunto, int valor);

// Menor valor do conjunto
int menor_valor(ConjuntoInt* conjunto);

// Maior valor do conjunto
int maior_valor(ConjuntoInt* conjunto);

// Testa se dois conjuntos são iguais
int conjuntos_iguais(ConjuntoInt* a, ConjuntoInt* b);

// Retorna o tamanho do conjunto
int tamanho_conjunto(ConjuntoInt* conjunto);

// Testa se o conjunto é vazio
int conjunto_vazio(ConjuntoInt* conjunto);


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

struct ConjuntoInt {
    int itens[MAX_SIZE];
    int tamanho;
};

ConjuntoInt* cria_conjunto() {
    ConjuntoInt* c = (ConjuntoInt*) malloc(sizeof(ConjuntoInt));
    if (c != NULL) {
        c->tamanho = 0;
    }
    return c;
}


void insere_elemento(ConjuntoInt* conjunto, int valor) {
    if (conjunto->tamanho < MAX_SIZE && indice_elemento(conjunto, valor) == -1) {
        conjunto->itens[conjunto->tamanho++] = valor;
    }
}

void remove_elemento(ConjuntoInt* conjunto, int valor) {
    int index = indice_elemento(conjunto, valor);
    if (index != -1) {
        for (int i = index; i < conjunto->tamanho - 1; i++) {
            conjunto->itens[i] = conjunto->itens[i + 1];
        }
        conjunto->tamanho--;
    }
}

ConjuntoInt* uniao(ConjuntoInt* a, ConjuntoInt* b) {
    ConjuntoInt* uni = cria_conjunto();
    for (int i = 0; i < a->tamanho; i++) {
        insere_elemento(uni, a->itens[i]);
    }
    for (int i = 0; i < b->tamanho; i++) {
        insere_elemento(uni, b->itens[i]);
    }
    return uni;
}

ConjuntoInt* interseccao(ConjuntoInt* a, ConjuntoInt* b) {
    ConjuntoInt* inter = cria_conjunto();
    for (int i = 0; i < a->tamanho; i++) {
        if (indice_elemento(b, a->itens[i]) != -1) {
            insere_elemento(inter, a->itens[i]);
        }
    }
    return inter;
}

ConjuntoInt* diferenca(ConjuntoInt* a, ConjuntoInt* b) {
    ConjuntoInt* diff = cria_conjunto();
    for (int i = 0; i < a->tamanho; i++) {
        if (indice_elemento(b, a->itens[i]) == -1) {
            insere_elemento(diff, a->itens[i]);
        }
    }
    return diff;
}

int pertence_conjunto(ConjuntoInt* conjunto, int valor) {
    return indice_elemento(conjunto, valor) != -1;
}

int menor_valor(ConjuntoInt* conjunto) {
    int min = INT_MAX;
    for (int i = 0; i < conjunto->tamanho; i++) {
        if (conjunto->itens[i] < min) {
            min = conjunto->itens[i];
        }
    }
    return min;
}

int maior_valor(ConjuntoInt* conjunto) {
    int max = INT_MIN;
    for (int i = 0; i < conjunto->tamanho; i++) {
        if (conjunto->itens[i] > max) {
            max = conjunto->itens[i];
        }
    }
    return max;
}

int conjuntos_iguais(ConjuntoInt* a, ConjuntoInt* b) {
    if (a->tamanho != b->tamanho) {
        return 0;
    }
    for (int i = 0; i < a->tamanho; i++) {
        if (!pertence_conjunto(b, a->itens[i])) {
            return 0;
        }
    }
    return 1;
}

int tamanho_conjunto(ConjuntoInt* conjunto) {
    return conjunto->tamanho;
}

int conjunto_vazio(ConjuntoInt* conjunto) {
    return conjunto->tamanho == 0;
}