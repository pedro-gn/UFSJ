#include <stdio.h>
#include <stdlib.h>


void crescente(int prox);
void decrescente(int ant);



int main(){
    crescente(1);
    decrescente(5);
    return 0;
}



void crescente(int prox){
    printf("%d ", prox);
    if(prox >= 5){
        printf("\n");
        return;
    }
    crescente(prox+1);
    return;
}

void decrescente(int ant){
    printf("%d ", ant);
    if(ant <= 1){
        printf("\n");
        return;
    }
    decrescente(ant-1);
    return;
}