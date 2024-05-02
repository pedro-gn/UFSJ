#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencher(int *vet, int vetSize, int count);
void printar(int *vet, int vetSize, int count, int mode);
void maior(int *vet, int vetSize, int count, int maiorn);


int main(){
    srand(time(NULL));
    int vet[10];
    preencher(vet, 10, 0);
    printar(vet, 10, 0, 1);
    printf("\n");
    printar(vet, 10, 0, 2);
    maior(vet, 10, 0, 0);
    return 0;
}

void preencher(int *vet, int vetSize, int count){
    if( count == vetSize){
        return;
    }

    vet[0] = rand() % 100;
    preencher(vet+1, vetSize, count+1);
    return;
}

void printar(int *vet, int vetSize, int count, int mode){
    if( count == vetSize){
        return;
    }

    if(mode == 1){
        printf("%d-", vet[0]);
        printar(vet+1, vetSize, count+1, mode);
        return;
    }else if(mode == 2){
        printar(vet+1, vetSize, count+1, mode);
        printf("%d-", vet[0]);
        return;
    }
}

void maior(int *vet, int vetSize, int count, int maiorn){
    if(count == vetSize){
        printf("\nMaior numero: %d ", maiorn);
        return;
    }

    if(vet[0] > maiorn){
        maiorn = vet[0];
    }

    maior(vet+1, vetSize, count+1, maiorn);
}