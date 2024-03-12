#include <stdio.h>
#include <omp.h>

int main() {
	for (int iter = 0; iter < 10; ++iter) {
		int chet = 1;
		omp_lock_t accesslock;
		#pragma omp parallel for shared(chet, accesslock) default(none)
		for (int i = 0; i < 10001; ++i) {
			omp_set_lock(&accesslock);
			chet = (chet) ? 0 : 1;
			omp_unset_lock(&accesslock);
		}
		printf("%d\n", chet);
	}
	return 0;
}
