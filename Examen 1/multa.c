#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char const *argv[])
{
	int m[600][600];
	int n[600][600];
	int rest[600][600];
	int sum = 0;


	for (int i = 0; i < 600; ++i)
	{
		for (int j = 0; j < 600; ++j)
		{
			m[i][j] = 1;
			n[i][j] = 1;
		}
	}

	int NUM_THREADS; 
	for(NUM_THREADS=1; NUM_THREADS<15; NUM_THREADS++)
	{
		int c, d, k;
		omp_set_num_threads(NUM_THREADS);
		const double start = omp_get_wtime();
		
		#pragma omp parallel for schedule(dynamic) private (c, d, k, sum)
		for (c = 0; c < 600; c++) {
			for (d = 0; d < 600; d++) {
				for (k = 0; k < 600; k++) {
					sum = sum + m[c][k]*n[k][d];
				}
			rest[c][d] = sum;
			sum = 0;
			}
		}

		/*
		for (int c = 0; c < 600; c++) {
			for (int d = 0; d < 600; d++)
				printf("%i  ", rest[c][d]);

		printf("\n");
		}
		*/

		const double end = omp_get_wtime();
		printf("%lf\n", (end - start));
	}
	return 0;
}