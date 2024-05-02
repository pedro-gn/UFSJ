#include <stdio.h>
#include <stdlib.h>

int soma(int comeco,int  final);

int main(){
    int f,c;


    printf("Começo do intervalo:");
    scanf("%d", &c);
    printf("Final do intervalo:");
    scanf("%d", &f);

    soma(c, f);
}



int soma(int comeco, int final){
    if(comeco == final-1 ){
        return comeco+final;
    }
    printf("%d--", soma(comeco+1, final) + comeco);       
                
    return soma(comeco+1, final) + comeco;


}