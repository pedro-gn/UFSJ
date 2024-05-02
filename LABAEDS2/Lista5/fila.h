#define MAX 100

typedef struct {
    int itens[MAX];
    int inicio, fim;
} Fila;

Fila* criarFila();
int enfileirar(Fila* f, int valor);
int desenfileirar(Fila* f, int* valor);
int verInicio(Fila* f, int* valor);
void imprimirFila(Fila* f);
void destruirFila(Fila* f);
int estaVazia(Fila* f);
