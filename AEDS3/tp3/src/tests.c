#include "../include/tests.h"


// Cria o estrutura testes com pelo nome do arquivo com os testes passado
Tests *createTests(char *fileName){

    Tests *tests;
    tests = (Tests *)malloc(sizeof(Tests));
    tests->fileName = malloc(strlen(fileName) * sizeof(char) +1);

    // Nome do arquivo
    strcpy(tests->fileName,fileName);

    FILE *f = fopen(fileName, "r");

    // N de testes
    fscanf(f," %d ", &tests->ntests);
    
    // Alloca memoria para a quantidade de testes
    tests->texts = (char**)malloc(tests->ntests *  sizeof(char*));
    tests->patterns = (char**)malloc(tests->ntests *  sizeof(char*));

    for(int i = 0; i < tests->ntests; i++){
        tests->texts[i] = malloc(MAX_TEXT_SIZE * sizeof(char));
        tests->patterns[i] = malloc(MAX_PATTERN_SIZE * sizeof(char));
        fscanf(f, " %s %s ", tests->patterns[i], tests->texts[i]);

        // Simula o formato circular da pedra
        char *temp = malloc(strlen(tests->patterns[i]) * sizeof(char) + 1);
        strcat(tests->texts[i], strncpy(temp, tests->texts[i], strlen(tests->patterns[i])));

        while(strlen(tests->patterns[i]) > strlen(tests->texts[i])){
            char *temp = malloc(strlen(tests->texts[i]) * sizeof(char) + 1);
            strcat(tests->texts[i], strncpy(temp, tests->texts[i], strlen(tests->texts[i])));
            free(temp);
        }
        free(temp);
    }

    fclose(f);
    return tests;
}

// Escreve o resultado no arquivo de saida
void writeText(int **results, int nresults, char *fileName){
    char *name;
    FILE *f;

    name = strtok(fileName, ".");
    strcat(name, ".out");

    f = fopen(name, "w");
    
    for(int i = 0; i< nresults; i++){
        if(results[i] == -1){
            fprintf(f,"N\n");
        }else{
            fprintf(f,"S %d\n", results[i]);
        }
    }
    
    fclose(f);

}   

// Libera a memoria dos textos e dos patterns 
void freeTests(Tests *tests){

    for(int i = 0; i < tests->ntests; i++){
        free(tests->patterns[i]);
        free(tests->texts[i]);
    }

    free(tests->fileName);
    free(tests->patterns);
    free(tests->texts);
    free(tests);
}

// Executa os testes com o algoritmo escolhido 
void execTests(Tests *tests, int strmatchAlgo){

    pthread_t threads[tests->ntests]; //threads
    // Array de retorno com os resultados dos threds
    int *results[tests->ntests]; 
    for (int i = 0; i < tests->ntests; i++) {
        results[i] = malloc(sizeof(int)); // ou o tamanho adequado para armazenar o resultado
    }

    // Cria as threads
    for(int i = 0; i < tests->ntests; i++){
        // Prepara os argumentos para mandar para thread
        FuncArgs *args = malloc(sizeof(FuncArgs));
        strcpy(args->text, tests->texts[i]);
        strcpy(args->pattern, tests->patterns[i]);

        // Escolhe Qual Algoritmo Será usado
        switch (strmatchAlgo){
        case 1: 
            pthread_create(&threads[i], NULL, bruteforce, (void*)args);
            break;
        case 2:
            pthread_create(&threads[i], NULL, BMHSearch, (void*)args);
            break;
        case 3:
            pthread_create(&threads[i], NULL, shiftAnd, (void*)args);
            break;
        default:
            printf("Algoritmo Invalido!!");
            free(args);
            break;
        }
    }

    // Aguarda o término das threads
    for (int i = 0; i < tests->ntests; i++) {
        pthread_join(threads[i], (void**)&(results[i]));
    }


    // Escreve os resultados no arquivo de saida
    writeText(results, tests->ntests, tests->fileName);
}