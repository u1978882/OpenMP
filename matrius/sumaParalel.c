#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include<malloc.h>


void omplirMatriu(int *matriu, int tamany){
    long i, j;
    #pragma omp parallel for private(i,j) shared(matriu)
    for (i = 0; i < tamany; i++)
    {
        for (j = 0; j < tamany; j++)
        {
            *((matriu+(i*(long)tamany)) + j) = rand() % 100;
        }
    }
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
    omplirMatriu(matriuA, tamanyMatriu);
    int *matriuB = malloc(sizeof(int) * tamanyMatriu * tamanyMatriu);
    omplirMatriu(matriuB, tamanyMatriu);
    int *matriuC = malloc(sizeof(int) * tamanyMatriu * tamanyMatriu);

    if (matriuA == NULL || matriuB == NULL || matriuC == NULL) {
        fprintf(stderr, "Ha fallat el malloc!\n");
        free(matriuA);
        free(matriuB);
        free(matriuC);
        return 0;
    }
  	
    omp_set_num_threads(omp_get_num_procs());

    double timeI, timeF, temps;
    timeI = omp_get_wtime();

    // Suma matriu
    long i, j;
    long max = tamanyMatriu * tamanyMatriu;
    #pragma omp parallel for private(i,j) shared(matriuA,matriuB,matriuC)
    for (i = 0; i < max; i++)
    {
        *(matriuC+i) = *(matriuA+i) + *(matriuB+i);
    }
    
    timeF = omp_get_wtime();
    temps = timeF - timeI;
    printf("%g\n", temps);
    
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

