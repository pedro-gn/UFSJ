#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "time.h"

#include "memory.h"

/*
Main Recebe como parâmetros o número de argumentos da linha de comando (argc) e
um array de strings contendo os argumentos da linha de comando (argv).
É o ponto de entrada do programa, onde a execução é iniciada.
*/
int main(int argc, char* argv[]) {
    /* A função inicia gerando uma semente para a função rand baseada no tempo atual usando srand(time(NULL)). 
    Isso garante que os números aleatórios gerados posteriormente sejam diferentes em cada execução do programa.*/
    srand(time(NULL));
    
    /* É verificado se o número de argumentos da linha de comando é igual a 5. Se não for, o programa 
    imprime uma mensagem informando o uso correto e retorna 1, indicando um erro na execução. */
    if (argc != 5) {
        printf("Uso: %s <algoritmo_substituicao> <arquivo_de_entrada> <tamanho_das_paginas> <tamanho_da_memoria>\n", argv[0]);
        return 1;
    }
    
    /* Os argumentos da linha de comando são convertidos para valores inteiros usando a função atoi e atribuídos a variáveis apropriadas,
    como memSize, pageSize e inputFile. Esses valores são usados para configurar os parâmetros do programa. */
    const char* algorithm = argv[1];
    const char* inputFile = argv[2];
    int pageSize = atoi(argv[3]);
    int memSize = atoi(argv[4]);
    
    /* São inicializadas variáveis para rastrear informações sobre o desempenho do programa, como usedPages, reads, writes, hits, misses, writebacks e faults.
    Essas variáveis serão atualizadas ao longo da execução do programa. */
    int usedPages = 0;
    int reads = 0;
    int writes = 0;
    int hits = 0;
    int misses = 0;
    int writebacks = 0;
    int faults = 0;
    
    /* São inicializados ponteiros first e last para NULL. Esses ponteiros serão usados para criar uma lista encadeada de páginas de memória. */
    Page* first = NULL;
    Page* last = NULL;
    
    /* O arquivo de entrada é aberto usando fopen com o nome do arquivo fornecido na linha de comando. Se ocorrer um erro ao abrir o arquivo,
    uma mensagem de erro é exibida e o programa retorna 1. */
    FILE* file = fopen(inputFile, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    unsigned addr;
    char operation;
    
    /* Em seguida, começa o processamento do arquivo de entrada. O programa é responsável por ler o arquivo de entrada linha por linha e processar cada acesso à memória.
    O fscanf é utilizado para ler o endereço de memória (addr) e a operação de leitura ou escrita (operation). Em seguida, o caractere seguinte é lido para determinar o tipo de operação.
    Com base no tipo de operação, os contadores apropriados são incrementados. No caso de uma falha de página (Page Fault), a função WriteAddress é chamada para escrever o endereço na memória,
    e o contador de falhas de página é incrementado. Os contadores de hits (páginas encontradas na memória) e writebacks (páginas escritas de volta no disco) também são atualizados, conforme necessário.*/
    while (fscanf(file, "%x %c", &addr, &operation) == 2) {
        char type;

        // Contabiliza a leitura ou escrita realizada
        if (operation == 'R') {
            reads++; 
        }
        else if (operation == 'W') {
            writes++; 
        }
    
        // Lê o próximo caractere para determinar o tipo de operação
        fscanf(file, " %c", &type);
    
        if (type == 'F') {
            // Falha de página (Page Fault)
            char tmpAddress[9];
            snprintf(tmpAddress, sizeof(tmpAddress), "%08x", addr); // Converte o endereço para uma string formatada
            WriteAddress(&first, &last, memSize / pageSize, &usedPages, tmpAddress, &faults, &writes); // Realiza a escrita do endereço na memória
            misses++; 
        }
        else if (type == 'H') {
            // Página encontrada na memória (Hit)
            hits++; 
        }
        else if (type == 'B') {
            // Página escrita de volta no disco (Writeback)
            writebacks++;
        }
    } /* Esse processo é repetido até que todas as linhas do arquivo tenham sido processadas. */
    
    /* O código agora imprime as informações solicitadas no formato especificado pelo TP2. 
    Ele exibe a configuração utilizada, o número total de acessos à memória, o número de page faults e
    o número de páginas sujas escritas de volta no disco. */
    printf("Configuração utilizada:\n");
    printf("Algoritmo de substituição: %s\n", algorithm);
    printf("Arquivo de entrada: %s\n", inputFile);
    printf("Tamanho das páginas: %d KB\n", pageSize);
    printf("Tamanho total da memória física: %d KB\n", memSize);
    printf("Número total de acessos à memória: %d\n", reads + writes);
    printf("Número de page faults: %d\n", faults);
    printf("Número de páginas sujas escritas de volta no disco: %d\n", writebacks);

    /*Após o prossamento o arquvo é fechado com fclose*/
    fclose(file);

    /* A função FreeMemory é chamada para liberar a memória alocada para as páginas. */
    FreeMemory(first);

    return 0;
}


