#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main() {
	printf ("_OPENMP = %d\n", _OPENMP);
	printf ("omp_get_num_procs() = %d\n", omp_get_num_procs ( ));
	printf("omp_get_max_threads() = %d\n", omp_get_max_threads());
	printf("omp_get_dynamic() = %d\n", omp_get_dynamic());
	printf("omp_get_wtick() = %e\n", omp_get_wtick());
	printf("omp_get_nested() = %d\n", omp_get_nested());
	printf("omp_get_max_active_levels() =%d\n", omp_get_max_active_levels());
	omp_sched_t kind;
	int chunk_size;
	omp_get_schedule(&kind, &chunk_size);
	printf("omp_get_schedule() = kind : %d; chunk_size: %d\n", kind, chunk_size);
	return 0;
}
