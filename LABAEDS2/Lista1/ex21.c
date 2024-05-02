#include <stdio.h>
#include <stdlib.h>


void imprime(char *vet);




int main(){

    char *vet = "pedro";

    imprime(vet);
    return 0;
}


void imprime(char *vet){
    if(*vet == '\0'){
        return;
    }else{
        imprime(vet+1);
        printf("%c", vet[0]);
    }

}