#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <math.h>

int main() {

  	clock_t clock_inicial = clock();


	int i;
    int num_steps = 5000;
    double x, pi, error, step, sum = 0.0;
    double PI_teo = 3.141592653589793238462643;
    step = 1.0/(double) num_steps;
    for (i=0;i< num_steps; i++)
    {
        x = (i+0.5)*step;
        sum+= 4.0/(1.0+x*x);
    }
    pi = step * sum;
    printf("pi es aproximadament %.16f\n",pi);
    error = fabs(pi-PI_teo);
    printf("Marge d’error %.16f\n",error);


	clock_t clock_final = clock();
	printf("Temps ");
	printf("%f\n",(double)(clock_final - clock_inicial) / CLOCKS_PER_SEC);

	return 0;
}
