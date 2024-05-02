#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int randVets(int tamV, int op);
int maior(int *vet, int tamV);
int menor(int *vet, int tamV);
int media(int *vet, int tamV);

int main(){
    printf("Maior: %d \n", randVets(10, 1));
    printf("Menor: %d \n", randVets(10, 2));
    printf("Media: %d \n", randVets(10, 3));
}

int randVets(int tamV, int op){

    int *vet1 = malloc(sizeof(int) * tamV);
    int *vet2 = malloc(sizeof(int) * tamV);

    int r; //Resposta

    srand(time(NULL));

    for( int i = 0; i < tamV; i++){
        vet1[i] = rand() % 1000;
        vet1[i] = rand() % 1000;
    }


    switch (op)
    {
    case 1:
        r = maior(vet1, tamV);
        free(vet1);
        free(vet2);
        return r;
        break;

    case 2:
        r =  menor(vet1, tamV);
        free(vet1);
        free(vet2);
        return r;
        break;

    case 3:
        r = media(vet1, tamV);
        free(vet1);
        free(vet2);
        return r;
        break;

    default:
        free(vet1);
        free(vet2);
        return 1;
        break;
    }
}




int maior(int *vet, int tamV){
    int maiorN = vet[0];
    for(int i = 0; i < tamV; i++){
        if(vet[i] > maiorN){
            maiorN = vet[i];
        }
    }
    return maiorN;
}
int menor(int *vet, int tamV){
    int menorN = vet[0];
    for(int i = 0; i < tamV; i++){
        if(vet[i] < menorN){
            menorN = vet[i];
        }
    }
    return menorN;
}

int media(int *vet, int tamV){
    int t = 0;
    for(int i = 0; i < tamV; i++){
        t += vet[i];
    }
    return t/tamV;

}