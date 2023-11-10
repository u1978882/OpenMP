#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include<malloc.h>


void omplirMatriu(int *matriu, int tamany){
    for (long i = 0; i < tamany; i++)
        for (long j = 0; j < tamany; j++)
            *((matriu+(i*(long)tamany)) + j) = rand() % 100;
}

void printMatriu(int *matriu, int tamany){
    for (long i = 0; i < tamany; i++)
    {
        for (long j = 0; j < tamany; j++)
        {
            printf("%3i ",  *((matriu+i*tamany) + j));
        }
        printf("\n");
    }
}


int main(int argc, char *argv[]) {

    int tamanyMatriu = 100;
    if (argc >= 2) tamanyMatriu = atoi(argv[1]);

    int *matriuA = malloc(sizeof(int) * tamanyMatriu * tamanyMatriu);
    int *matriuB = malloc(sizeof(int) * tamanyMatriu * tamanyMatriu);
    int *matriuC = malloc(sizeof(int) * tamanyMatriu * tamanyMatriu);

    if (matriuA == NULL || matriuB == NULL || matriuC == NULL) {
        fprintf(stderr, "Ha fallat el malloc!\n");
        free(matriuA);
        free(matriuB);
        free(matriuC);
        return 0;
    }
    
    omplirMatriu(matriuB, tamanyMatriu);
    omplirMatriu(matriuA, tamanyMatriu);

  	
    clock_t clock_inicial = clock();

    // Suma matriu
    for (long i = 0; i < tamanyMatriu; i++)
        for (long j = 0; j < tamanyMatriu; j++)
            *((matriuC+i*tamanyMatriu) + j) = *((matriuA+i*tamanyMatriu) + j) + *((matriuB+i*tamanyMatriu) + j);
    
    clock_t clock_final = clock();
    printf("%f\n",(double)(clock_final - clock_inicial) / CLOCKS_PER_SEC);
    
    //printf("--- Matriu A ---\n");
    //printMatriu(matriuA, tamanyMatriu);
    //printf("--- Matriu B ---\n");
    //printMatriu(matriuB, tamanyMatriu);
    //printf("--- Matriu C ---\n");
    //printMatriu(matriuC, tamanyMatriu);

    free(matriuA);
    free(matriuB);
    free(matriuC);  

	return 0;
}

