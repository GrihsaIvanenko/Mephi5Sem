#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

void makeCp(int fdCopyFrom, int fdCopyTo) {
	char byte;
	while (read(fdCopyFrom, &byte, sizeof(byte)) == 1) {
		if (write(fdCopyTo, &byte, sizeof(byte)) == 0) {
			fprintf(stderr, "Error writing byte");
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		printf("Usage %s <file_copy_from> <file_copy_to>\n", argv[0]);
		return 0;
	}
	if (argc != 3) {
		printf("Usage %s <file_copy_from> <file_copy_to>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fdCopyFrom = open(argv[1], O_RDONLY);
	if (errno != 0) {
		fprintf(stderr, "Error opening file \"%s\": ", argv[1]);
		perror("");
		exit(EXIT_FAILURE);
	}
	int fdCopyTo = open(argv[2], O_WRONLY | O_CREAT);
	if (errno != 0) {
		fprintf(stderr, "Error opening file \"%s\": ", argv[2]);
		perror("");
		exit(EXIT_FAILURE);
	}
	makeCp(fdCopyFrom, fdCopyTo);
	close(fdCopyFrom);
	close(fdCopyTo);
	return 0;
}
