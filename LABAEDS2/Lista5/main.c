#include <stdio.h>
#include "fila2.h"

int main() {
    Fila* f = NULL;
    int opcao, valor;

    do {
        printf("1 - Criar fila\n");
        printf("2 - Enfileirar um item\n");
        printf("3 - Ver o inicio da fila\n");
        printf("4 - Desenfileirar um item\n");
        printf("5 - Imprimir a fila\n");
        printf("6 - Destruir a fila\n");
        printf("7 - Sair\n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                if (f) destruirFila(f);
                f = criarFila();
                if (f) printf("Fila criada com sucesso!\n");
                else printf("Erro ao criar fila!\n");
                break;
            case 2:
                printf("Informe o valor: ");
                scanf("%d", &valor);
                if (enfileirar(f, valor)) printf("Item enfileirado!\n");
                else printf("Erro ao enfileirar!\n");
                break;
            case 3:
                if (verInicio(f, &valor)) printf("Início da fila: %d\n", valor);
                else printf("Fila vazia ou não criada!\n");
                break;
            case 4:
                if (desenfileirar(f, &valor)) printf("Item desenfileirado: %d\n", valor);
                else printf("Fila vazia ou não criada!\n");
                break;
            case 5:
                imprimirFila(f);
                break;
            case 6:
                destruirFila(f);
                f = NULL;
                printf("Fila destruída!\n");
                break;
            case 7:
                if (f) destruirFila(f);
                printf("Saindo...\n");
                break;
        }
    } while(opcao != 7);

    return 0;
}
