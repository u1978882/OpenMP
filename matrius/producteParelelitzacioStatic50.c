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
        for (j = 0; j < tamany; j++)
            *((matriu+(i*(long)tamany)) + j) = 2;//rand() % 100;
}

void printMatriu(int *matriu, int tamany){
    for (long i = 0; i < tamany; i++)
    {
        for (long j = 0; j < tamany; j++)
        {
            printf("%5i ",  *((matriu+i*tamany) + j));
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

  	omp_set_num_threads(omp_get_num_procs());

    double timeI, timeF, temps;
    timeI = omp_get_wtime();

    // Multiplicacio matriu
    #pragma omp parallel for schedule(static, 50)
    for (long i = 0; i < tamanyMatriu; i++)
    {
        for (long j = 0; j < tamanyMatriu; j++)
        {
            *((matriuC+i*tamanyMatriu) + j) = 0;
            for (long k = 0; k < tamanyMatriu; k++)
            {
                *((matriuC+i*tamanyMatriu) + j) += *((matriuA+i*tamanyMatriu) + k) * *((matriuB+k*tamanyMatriu) + j);
            }
        }
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

