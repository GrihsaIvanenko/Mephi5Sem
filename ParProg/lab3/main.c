#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <assert.h>

int** makeArr(int rows, int columns)
{ 
	int** result = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; ++i) {
		result[i] = (int*)calloc(columns, sizeof(int));
	}
	return result;
}

void printAvTime(int* arLens, double* avtime, int arLensLen)
{
	printf("in milliseconds\n");
	for (int arLensId = 0; arLensId < arLensLen; ++arLensId) {
		printf("%d: %.10lf\n", arLens[arLensId], avtime[arLensId] * 1000.0);
	}
}

int f(int firNumb, int tenPw) {
	assert(1 <= firNumb && firNumb <= 3);
	assert(3 <= tenPw && tenPw <= 8);
	int res = 1;
	if (firNumb == 1) {
		res = 2;
	} else if (firNumb == 2) {
		res = 5;
	}
	for (int i = 0; i < tenPw; ++i) {
		res *= 10;
	}
	return res;
}

int main(int argc, char** argv)
{
	// Init data
	const int measCount = 15;
	int arLens[measCount];
	const int arsByLen = 10;
	int arLensId = 0;
	for (int tenPw = 3; tenPw < 8; ++tenPw) {
		for (int firNumb = 1; firNumb <= 3; ++firNumb) {
			arLens[arLensId++] = f(firNumb, tenPw);
		}
	}
	assert(arLensId == measCount);
	int threadCount = 4;
	// Init measurement arrays
	double* avTime = (double*)malloc(measCount * sizeof(double));

	// Start measuring
	for (int measId = 0; measId < measCount; ++measId) {
		double totalTime = 0;
		int* array = (int*)malloc(arLens[measId] * sizeof(int));
		for (int _ = 0; _ < arsByLen; ++_) {
			printf("meas %d, iter %d, size %d\n", measId, _, arLens[measId]);
			for (int pos = 0; pos < arLens[measId]; ++pos) {
				array[pos] = rand();
			}
			double startTime = omp_get_wtime();
			for (int d = arLens[measId] / 2; d > 0; d /= 2) {
				int i, j, x, k;
				#pragma omp parallel for num_threads(threadCount) shared(array, arLens, measId, d) private(i, j, x, k) default(none)
				for (i = 0; i < d; ++i) {
					for (j = i + d; j < arLens[measId]; j += d) {
						x = array[j];
						k = j - d;
						while (k >= i && array[k] > x) {
							array[k + d] = array[k];
							k -= d;
						}
						array[k + d] = x;
					}
				}
			}
			totalTime += omp_get_wtime() - startTime;
			int flag = 1;
			for (int i = 1; i < arLens[measId]; ++i) {
				if (array[i] < array[i - 1]) {
					flag = 0;
				}
			}
			if (flag == 0) {
				fprintf(stderr, "NOT SORTED!");
			}
		}
		avTime[measId] = totalTime / arsByLen;
	}
	printAvTime(arLens, avTime, measCount);
	printf("\n");
	return 0;
}
