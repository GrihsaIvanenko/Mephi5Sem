#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

void makeCat(int fd) {
	char byte;
	while (read(fd, &byte, sizeof(byte)) == 1) {
		printf("%c", byte);
	}
	printf("\n");	
}

int main(int argc, char* argv[]) {
	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		printf("Usage %s <file1> <file2> ...\n", argv[0]);
		return 0;
	}
	if (argc == 1) {
		printf("Enter at least one file name\n");
		exit(EXIT_FAILURE);
	}
	for (int argId = 1; argId < argc; ++argId) {
		int fd = open(argv[argId], O_RDONLY);
		if (errno != 0) {
			//strerror
			fprintf(stderr, "Error opening file \"%s\": ", argv[argId]);
			perror("");
			errno = 0;
		} else {
			makeCat(fd);
			close(fd);
		}
	}
	return 0;
}
