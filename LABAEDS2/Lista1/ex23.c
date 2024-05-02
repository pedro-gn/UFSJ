#include <stdio.h>
#include <stdlib.h>

int soma(int comeco, int fim);

int main(){
    printf("%d",soma(1,6));
}

int soma(int comeco, int fim){
    if(comeco == fim-1){
        return comeco+fim;
    }
    return soma(comeco+1, fim) + comeco;
}