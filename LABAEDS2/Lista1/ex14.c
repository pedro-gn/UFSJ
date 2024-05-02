#include <stdio.h>
#include <math.h>

int raizes(float A, float B, float C, float *X1, float *X2) {
    if (A == 0) {
        printf("A não pode ser zero.\n");
        return -1; // indicando um erro
    }

    float delta = B * B - 4 * A * C;

    if (delta < 0) {
        return 0; // Nenhuma raiz real
    } else if (delta == 0) {
        *X1 = -B / (2 * A);
        return 1; // Uma raiz real
    } else {
        *X1 = (-B + sqrt(delta)) / (2 * A);
        *X2 = (-B - sqrt(delta)) / (2 * A);
        return 2; // Duas raízes reais
    }
}

int main() {
    float A, B, C;
    float X1, X2;
    
    printf("Entre com os coeficientes A, B e C da equação do segundo grau (Ax^2 + Bx + C = 0):\n");
    scanf("%f %f %f", &A, &B, &C);

    int numRaizes = raizes(A, B, C, &X1, &X2);
    
    switch(numRaizes) {
        case -1:
            printf("Coeficiente A não pode ser zero.\n");
            break;
        case 0:
            printf("Não há raízes reais.\n");
            break;
        case 1:
            printf("Existe uma raiz real: %f\n", X1);
            break;
        case 2:
            printf("Existem duas raízes reais: %f e %f\n", X1, X2);
            break;
        default:
            printf("Erro desconhecido.\n");
            break;
    }
    
    return 0;
}
