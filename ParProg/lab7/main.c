#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	if (argc != 3) {
		printf("Usage ./lab [N_start] [N_end}\n");
		MPI_Finalize();
		return 0;
	}
	int tmp, f, count, gcount;
	int A = atoi(argv[1]);
	int B = atoi(argv[2]);
	if (A > B) {
		tmp = A;
		A = B;
		B = tmp;
	}
	int range[2];
	int size, rank;
	MPI_Status st;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int block = (B - A) / size;
	int ost = (B - A) % size;
	range[0] = A;
	range[1] = A + block;
	double gbegin = MPI_Wtime();
	if (!rank) {
		for (int i = 1; i < size; ++i) {
			range[0] = range[1];
			range[1] += block;
			if (ost) {
				--ost;
				range[1]++;
			}
			MPI_Send(range, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		range[0] = A;
		range[1] = A + block;
	} else {
		MPI_Recv(range, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
	}
	count = 0;
	double begin = MPI_Wtime();
#pragma omp parallel for num_threads(2) reduction(+: count) shared(range, rank) private(f) default(none)
	for (int i = range[0]; i < range[1]; ++i) {
		f = (i == 1) ? 0 : 1;
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
	double end = MPI_Wtime();
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Reduce(&count, &gcount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	double gend = MPI_Wtime();
	if (!rank) {
		printf("gcount = %d\n", gcount);
	}
	char a[] = "0.txt";
	a[0]+=rank;
	FILE *fp = fopen(a, "a");
	fprintf(fp, "%d %f\n", rank, end-begin);
	fclose(fp);
	if (!rank) {
		fp = fopen("log.txt", "a");
		fprintf(fp, "%d %f\n", size, gend - gbegin);
		fclose(fp);
	}
	MPI_Finalize();
	return 0;
}
