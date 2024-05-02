#include <stdio.h>

int negativos(float *vet, int N);

int main(){
    //array de teste
    float array[5] = {5, -1, -2, -3};

    printf("Negativos: %d", negativos(array, 5));
    return 0;
}

int negativos(float *vet, int N){
    int count = 0;

    for(int i = 0; i < N; i++){
        if(vet[i] < 0){
            count++;
        }
    }

    return count;
}