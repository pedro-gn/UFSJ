#include<stdio.h>
#include<string.h>

//N (numero[]) e um numero representado por uma sequencia de elementos do conjunto  {{0-9} ∪ {A-Z}}
//B e a base numerica de N
//T e a base para ser convertido

void converter(char s[20],int,int);

void main()
{   
    char numero[20];
    int B,T;
    printf("Padrao da entrada: Numero SuaBase BaseDeconversao-\n");
    while(numero && B && T != 0){
        scanf("%s%d%d",numero,&B,&T);
        converter(numero,B,T);
    }
}

void converter(char s[20],int B,int T){
    //variaveis
    int count = 0, r, digito, i, o = 0, b = 1;

    //Para converter os caracteres de entrada com valor ASII para o valor da base basta subtrair 48 se for numeros de 0 a 9
    //E para letras subtrair 48 + 7. por exemplo Z em ASCII = 90 para converter para base 36 Z - 48 - 7 = 35
    //entao basta subtrair '0' = 48 para numeros e '0' - 7 para letras

    for(i = strlen(s)-1; i >= 0; i--){
        if(s[i] >= 'A' && s[i] <= 'Z'){
            digito = s[i]-'0'-7;
        }else{
            digito = s[i]-'0';
        }
        o = digito * b + o;
        b = b * B;
    }

    //tranforma o digito convertido para nova base
    while(o != 0){
        r = o % T;
        digito = '0' + r;
        if(digito > '9')
        {
            digito += 7;
        }
        s[count]=digito;

        count++;
        o = o/T;
        printf("\n%d\n", o);
    }

    //imprime a saida 
    for( i = count-1; i >= 0; i--)
    {
        printf("%c",s[i]);
    }
    printf("\n");
}