typedef struct Cubo Cubo;

//cria um cubo dado o comprimento da aresta.
Cubo* cria_cubo(double aresta);

//retorna o volume do cubo.
double volume(Cubo *cubo);

//retorna a área da superfície do cubo.
double area_superficie(Cubo *cubo);

//altera o comprimento da aresta do cubo.
void altera_aresta(Cubo *cubo, double novo_comprimento);



#include <stdio.h>
#include <stdlib.h>

struct Cubo {
    double aresta;
};

Cubo* cria_cubo(double aresta) {
    Cubo *c = (Cubo*) malloc(sizeof(Cubo));
    if (c != NULL) {
        c->aresta = aresta;
    }
    return c;
}

double volume(Cubo *cubo) {
    return cubo->aresta * cubo->aresta * cubo->aresta;
}

double area_superficie(Cubo *cubo) {
    return 6 * (cubo->aresta * cubo->aresta);
}

void altera_aresta(Cubo *cubo, double novo_comprimento) {
    cubo->aresta = novo_comprimento;
}
