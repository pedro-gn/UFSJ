#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#include "memory.h"

/*
struct Page é a definição da estrutura de dados Page.
É uma estrutura que representa uma página na memória.
Possui um campo "value" para armazenar o valor da página e
um ponteiro "next" que aponta para a próxima página na lista encadeada.
*/
typedef struct Page {
    char value[9];
    struct Page* next;
} Page;

/*
AddNewPage adiciona uma nova página à lista de páginas.
Recebe como parâmetros o endereço do ponteiro para o primeiro elemento da lista,
o endereço do ponteiro para o último elemento da lista, o número total de páginas,
o endereço do contador de páginas utilizadas e o valor da página a ser adicionada.
*/
void AddNewPage(Page** first, Page** last, int numPages, int* usedPages, char value[9]) {
    Page* newPage = (Page*)malloc(sizeof(Page));
    strncpy(newPage->value, value, 9);
    newPage->next = NULL;

    if (*first == NULL) {
        *first = newPage;
        *last = newPage;
    }
    else {
        (*last)->next = newPage;
        *last = newPage;
    }

    (*usedPages)++;
}


/*
LRU implementa o algoritmo Least Recently Used (LRU) para substituição de páginas.
Recebe como parâmetros o endereço do ponteiro para o primeiro elemento da lista,
o endereço do ponteiro para o último elemento da lista, o número total de páginas,
o endereço do contador de páginas utilizadas e o valor da página a ser adicionada.
A função reorganiza a lista de páginas, movendo a página com o valor especificado para o final da lista.
*/
void LRU(Page** first, Page** last, int numPages, int* usedPages, char value[9]) {
    Page* current = *first;
    Page* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->value, value) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
                current->next = NULL;
                (*last)->next = current;
                *last = current;
            }

            return;
        }

        prev = current;
        current = current->next;
    }
}

/*
FIFO implementa o algoritmo First-In, First-Out (FIFO) para substituição de páginas.
Recebe como parâmetros o endereço do ponteiro para o primeiro elemento da lista,
o endereço do ponteiro para o último elemento da lista, o número total de páginas,
o endereço do contador de páginas utilizadas e o valor da página a ser adicionada.
A função remove o primeiro elemento da lista e adiciona a nova página no final da lista.
*/
void FIFO(Page** first, Page** last, int numPages, int* usedPages, char value[9]) {
    Page* newPage = (Page*)malloc(sizeof(Page));
    strncpy(newPage->value, value, 9);
    newPage->next = NULL;

    if (*first == NULL) {
        *first = newPage;
        *last = newPage;
    }
    else {
        (*last)->next = newPage;
        *last = newPage;
    }

    if (*usedPages >= numPages) {
        Page* temp = *first;
        *first = (*first)->next;
        free(temp);
    }
    else {
        (*usedPages)++;
    }
}

/*
Random implementa o algoritmo de substituição de páginas aleatório.
Recebe como parâmetros o endereço do ponteiro para o primeiro elemento da lista,
o número de páginas utilizadas e o valor da página a ser adicionada.
A função seleciona aleatoriamente uma página da lista e a substitui pelo valor especificado.
*/
void Random(Page** first, int usedPages, char value[9]) {
    int index = rand() % usedPages;
    Page* current = *first;

    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    strncpy(current->value, value, 9);
}

/*
Find busca por uma página na lista de páginas.
Recebe como parâmetros o endereço do ponteiro para o primeiro elemento da lista,
o endereço do ponteiro para o último elemento da lista, o valor da página a ser buscada
e o algoritmo de substituição de páginas em uso.
A função percorre a lista de páginas e verifica se a página com o valor especificado está presente.
Retorna verdadeiro se a página for encontrada e falso caso contrário.
*/
bool Find(Page** first, Page** last, char value[9], const char* alg) {
    Page* current = *first;
    Page* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->value, value) == 0) {
            if (strcmp(alg, "lru") == 0) {
                if (prev != NULL) {
                    prev->next = current->next;
                    current->next = NULL;
                    (*last)->next = current;
                    *last = current;
                }
            }
            else if (strcmp(alg, "fifo") == 0) {
                // No action needed for FIFO algorithm
            }
            else if (strcmp(alg, "random") == 0) {
                Random(first, *last - *first + 1, value);
            }

            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

/*
Replace substitui uma página da lista de acordo com o algoritmo especificado.
Recebe como parâmetros o algoritmo de substituição de páginas, o endereço do ponteiro para o primeiro elemento da lista,
o endereço do ponteiro para o último elemento da lista, o número total de páginas,
o endereço do contador de páginas utilizadas e o valor da página a ser substituída.
A função chama a função correspondente ao algoritmo especificado para realizar a substituição da página.
*/
void ReplacePage(const char* alg, Page** first, Page** last, int numPages, int* usedPages, char value[9]) {
    if (strcmp(alg, "lru") == 0) {
        LRU(first, last, numPages, usedPages, value);
    }
    else if (strcmp(alg, "fifo") == 0) {
        FIFO(first, last, numPages, usedPages, value);
    }
    else if (strcmp(alg, "random") == 0) {
        if (*usedPages >= numPages) {
            Page* temp = *first;
            *first = (*first)->next;
            free(temp);
        }

        AddNewPage(first, last, numPages, usedPages, value);
    }
}

/*
WriteAddress escreve um endereço na lista de páginas, tratando os casos de falta de página.
Recebe como parâmetros o endereço do ponteiro para o primeiro elemento da lista,
o endereço do ponteiro para o último elemento da lista, o número total de páginas,
o endereço do contador de páginas utilizadas, o endereço temporário do valor da página,
o endereço do contador de falhas de página e o endereço do contador de escritas.
A função verifica se o endereço está presente na lista de páginas.
Se estiver presente, atualiza a posição da página na lista.
Caso contrário, adiciona uma nova página e realiza a substituição, caso necessário.
*/
void WriteAddress(Page** first, Page** last, int numPages, int* usedPages, char tmpAddress[9], int* faults, int* writes) {
    if (!Find(first, last, tmpAddress, "lru")) {
        (*faults)++;
        (*writes)++;

        if (*usedPages >= numPages) {
            ReplacePage("lru", first, last, numPages, usedPages, tmpAddress);
        }
        else {
            AddNewPage(first, last, numPages, usedPages, tmpAddress);
        }
    }
    else {
        (*writes)++;
    }
}

/*
FreeMemory libera a memória alocada para a lista de páginas.
Recebe como parâmetro o endereço do primeiro elemento da lista.
A função percorre a lista de páginas e libera a memória alocada para cada elemento.
*/

void FreeMemory(Page* first) {
    Page* current = first;
    Page* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}