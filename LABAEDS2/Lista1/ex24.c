#include <stdio.h>
#include <stdlib.h>

int multiplica(int n, int m, int count);

int main(){
    int multi = multiplica(6, 7, 0);
    printf("%d", multi);
}


int multiplica(int n, int m, int count){

    if ( count == n){
        return 0;
    }
    return multiplica(n, m, count+1) + m;

}