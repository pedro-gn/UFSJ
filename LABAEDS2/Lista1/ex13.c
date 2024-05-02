#include <stdio.h>

typedef struct {
    char nome[50];
    int matricula;
    float nota;
} Aluno;

void maiorMenorNota(Aluno alunos[], int tamanho) {

    Aluno maiorNota = alunos[0];
    Aluno menorNota = alunos[0];

    for(int i = 1; i < tamanho; i++) {
        if(alunos[i].nota > maiorNota.nota) {
            maiorNota = alunos[i];
        }
        if(alunos[i].nota < menorNota.nota) {
            menorNota = alunos[i];
        }
    }

    printf("Aluno com a maior nota:\n");
    printf("Nome: %s\n", maiorNota.nome);
    printf("Matricula: %d\n", maiorNota.matricula);
    printf("Nota: %.2f\n", maiorNota.nota);

    printf("\nAluno com a menor nota:\n");
    printf("Nome: %s\n", menorNota.nome);
    printf("Matricula: %d\n", menorNota.matricula);
    printf("Nota: %.2f\n", menorNota.nota);
}

int main() {
    Aluno alunos[] = {
        {"Ana", 12345, 85.5},
        {"João", 67890, 90.0},
        {"Maria", 11121, 70.5},
        {"Lucas", 22232, 88.0}
    };
    
    int tamanho = sizeof(alunos) / sizeof(alunos[0]);
    
    maiorMenorNota(alunos, tamanho);
    
    return 0;
}
