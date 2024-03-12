#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Usage ./lab [N_start] [N_finish]\n");
		return 1;
	}
	int A = atoi(argv[1]);
	int B = atoi(argv[2]);
	if (A > B) {
		int tmp = A;
		A = B;
		B = tmp;
	}
	int count = 0;
	double begin = omp_get_wtime();
	for (int i = A; i < B; ++i) {
		int f = (i == 1) ? 0 : 1;
		for (int j = 2; j * j <= i; ++j) {
			if (i % j == 0) {
				f = 0;
				break;
			}
		}	
		if (f) {
			++count;
		}	
	}
	double end = omp_get_wtime(); 
	FILE* fp;
	fp = fopen("log.txt", "a");
	fprintf(fp, "%d %f", count, end-begin);
	fclose(fp);
	return 0;
}
