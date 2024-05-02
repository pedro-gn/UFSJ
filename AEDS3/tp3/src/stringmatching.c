#include "../include/stringmatching.h"


//=============================================Utils=========================================================
// Reverte a string
char *reverseString(char *string, int stringLenght){
    char *revString = malloc(sizeof(char) * stringLenght + 1); 

    for(int i = stringLenght-1, j = 0; i >= 0; i--, j++){
        revString[j] = string[i];
    }

    revString[stringLenght] = '\0';

    return revString;
}



//=========================================Força Bruta========================================================
void* bruteforce(void *arg){
    FuncArgs *args = (FuncArgs*)arg;

    int textLength = strlen( args->text);
    int patternLength = strlen(args->pattern);
    char *revPattern = reverseString(args->pattern, patternLength);


    for( int i = 0; i < textLength; i++){
        for( int j = i, k = 0 ; k < patternLength; j++, k++){

            if( args->text[j] == args->pattern[k] ){
                // Casou 1 caractere
                if(k == patternLength-1){
                    // Checa se casou todos caracteres 
                    free(revPattern);
                    free(args);
                    return (void*)(intptr_t)i+1;
                }else{
                    continue;
                }
            }else{
                // Caso não case, para e move o padrao em 1 posição
                break;
            }
        }
    }

    // Faz o mesmo processo com a string invertida
    for( int i = 0; i < textLength + patternLength-1; i++){
        for( int j = i, k = 0 ; k < patternLength; j++, k++){

            if(j>=textLength){
                j = j - textLength;
            }

            if( args->text[j] == revPattern[k] ){
                // Casou 1 caractere
                if(k == patternLength-1){
                    // Checa se casou todos caracteres
                    free(revPattern); 
                    free(args);
                    return (void*)(intptr_t)(i + patternLength);
                }else{
                    continue;
                }
            }else{
                // Caso não case, para e move o padrao em 1 posição
                break;
            }
        }
    }

    // Não Achou
    free(args);
    free(revPattern);
    return (void*)(intptr_t)-1;
}



//==================================================================BMH==============================================================

// Pre processamento que cria a tabela de deslocamento ou bad characteres
void preProcess(char *pattern, int patternLength, int *badCharTable) {
    int i;
    
    // Inicializa a tabela de caracteres ruins com o comprimento do padrão
    for (i = 0; i < ALPHABET_SIZE; i++) {
        badCharTable[i] = patternLength;
    }
    
    // Preenche a tabela com o deslocamento correto para cada caractere do padrão
    for (i = 0; i < patternLength - 1; i++) {
        badCharTable[(int)pattern[i]] = patternLength - 1 - i;
    }
}

void *BMHSearch(void *arg) {
    FuncArgs *args = (FuncArgs*)arg;

    int textLength = strlen( args->text);
    int patternLength = strlen(args->pattern);
    char *revPattern = reverseString(args->pattern, patternLength);
    
    int badCharTable[ALPHABET_SIZE];

    // Preprocessa o padrao para montar a tabela de deslocamento
    preProcess(args->pattern, patternLength, badCharTable);
    
    int shift = 0;
    while (shift <= textLength - patternLength) {
        int j = patternLength - 1;
        
        // Enquanto os caracteres do padrão e do texto forem iguais
        while (j >= 0 && args->pattern[j] == args->text[shift + j]) {
            j--;
        }
        
        if (j < 0) {
            // padrão encontrado
            free(args);
            free(revPattern);
            return (void*)(intptr_t)shift+1;
        } else {
            // Realiza um deslocamento com base na tabela de caracteres ruins
            shift += badCharTable[(int)args->text[shift + patternLength - 1]];
        }
    }


    // Repete o processo para o padrao invertido
    preProcess(revPattern, patternLength, badCharTable);
    shift = 0;
    while (shift <= textLength - patternLength) {
        int j = patternLength - 1;
        
        // Enquanto os caracteres do padrão e do texto forem iguais
        while (j >= 0 && revPattern[j] == args->text[shift + j]) {
            j--;
        }
        
        if (j < 0) {
            //padrão encontrado
            free(args);
            free(revPattern);
            return (void*)(intptr_t)shift+patternLength;
        } else {
            // Realiza um deslocamento com base na tabela de caracteres ruins
            shift += badCharTable[(int)args->text[shift + patternLength - 1]];
        }
    }

    // Não Achou
    free(args);
    free(revPattern);
    return (void*)(intptr_t)-1;
}



//==============================================================================Shift-And=====================================================================

void *shiftAnd(void *arg) {
    FuncArgs *args = (FuncArgs*)arg;

    int patternLength = strlen(args->pattern);
    int textLength = strlen(args->text);
    char *revPattern = reverseString(args->pattern, patternLength);

    unsigned int mask[ALPHABET_SIZE] = {0}; // Inicializa a máscara com zeros
    
    // Cria a máscara
    for (int i = 0; i < patternLength; i++) {
        mask[args->pattern[i]] |= (1 << i);
    }
    
    // Executa o algoritmo Shift-And
    unsigned int state = 0;
    unsigned int match = (1 << (patternLength - 1)); // Máscara para verificar a correspondência completa


    // Padrão normal
    int i = 0;
    while (i < textLength) {
        state = ((state << 1) | 1) & mask[args->text[i]];

        if (state & match) {
            int offset = i - patternLength + 1;
            if (offset >= 0) {
                free(args);
                free(revPattern);
                return (void*)(intptr_t)offset+1;
            }
        }

        i++;
    }

    // Padrão invertido
    // Zera a mascara e repete para o padrao inverso
    memset(mask, 0, sizeof(mask));
    for (int i = 0; i < patternLength; i++) {
        mask[revPattern[i]] |= (1 << i);
    }

    state = 0;
    i = 0;
    while (i < textLength) {
        state = ((state << 1) | 1) & mask[args->text[i]];

        if (state & match) {
            int offset = i - patternLength + 1;
            if (offset >= 0) {
                free(args);
                free(revPattern);
                return (void*)(intptr_t)offset+patternLength;
            }
        }

        i++;
    }


    // Não Achou
    free(args);
    free(revPattern);
    return (void*)(intptr_t)-1;
}