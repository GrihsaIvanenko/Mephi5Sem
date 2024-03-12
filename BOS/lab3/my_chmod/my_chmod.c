#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		printf("Usage %s <number> <file>\n", argv[0]);
		return 0;
	}
	if (argc != 3) {
		printf("Usage %s <number> <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	char* end_parse = NULL;
	unsigned long mode = strtoul(argv[1], &end_parse, 8);
	if (strlen(argv[1]) != 4 || end_parse != argv[1] + 4) {
		printf("Invalid mode. Ensure you enter a four-digit octal number (e. g., 0644).\n");
		exit(EXIT_FAILURE);
	}
	if (chmod(argv[2], mode) == -1) {
		perror("Error changing file mode: ");
		exit(EXIT_FAILURE);
	}
	printf("Permissions for %s changed to %s\n", argv[2], argv[1]);
	return 0;
}
