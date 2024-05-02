#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../include/tests.h"


int main(int argc, char **argv){
    Tests *tests = createTests(argv[1]);

    struct timeval start, end; // Tempo de relgio

    gettimeofday(&start, NULL);
    execTests(tests, atoi(argv[2]));
    gettimeofday(&end, NULL);

    printf("Tempo de relogio da execução dos testes : %f segundos\n",
    1e-6*((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));

    // Libera a memoria 
    freeTests(tests);
}