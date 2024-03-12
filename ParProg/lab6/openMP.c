#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage ./laba [threads]");
		return 1;
	}
	const int threads = atoi(argv[1]);
	const int count = 1000000;
	srand(0);
	int* arr = (void*) malloc(count*sizeof(int)), i, j, x, k;
	for (int i = 0; i < count; ++i) {
		arr[i] = rand();
	}
	double start = omp_get_wtime();
	for (int d = count / 2; d > 0; d /= 2) {
		#pragma omp parallel for num_threads(threads) shared(count, d, arr) private(j, x, k) default(none)
		for (i = 0; i < d; ++i) {
			for (j = i + d; j < count; j += d) {
				x = arr[j];
				k = j - d;
				while (k >= i && arr[k] > x) {
					arr[k + d] = arr[k];
					k -= d;
				}
				arr[k + d] = x;
			}
		}
	}
	double stop = omp_get_wtime();
	FILE* fp = fopen("log.txt", "a");
	int flag = 1;
	for (int i = 0; i < count - 1; ++i) {
		if (arr[i] > arr[i + 1]) {
			flag = 0;
		}
	}
	fprintf(fp, "%d %f %d\n", threads, stop - start, flag);
	fclose(fp);
	return 0;
}
