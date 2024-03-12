#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		printf("Usage %s <file>\n", argv[0]);
		return 0;
	}
	if (argc != 2) {
		printf("Usage %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	const char* filename = argv[1];
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("Error opening file: ");
		exit(EXIT_FAILURE);
	}
	unsigned int flags;
	int result = ioctl(fd, FS_IOC_GETFLAGS, &flags);
	if (result == -1) {
		perror("Error getting file attributes: ");
		close(fd);
		exit(EXIT_FAILURE);
	}
	flags ^= FS_NOATIME_FL;
	if (flags & FS_NOATIME_FL) {
		printf("Add flag A for file %s - not update atime\n", filename);
	} else {
		printf("Remove flag A for file %s - updating atime\n", filename);
	}
	result = ioctl(fd, FS_IOC_SETFLAGS, &flags);
	if (result == -1) {
		perror("Error setting file attributes: ");
		close(fd);
		exit(EXIT_FAILURE);
	}
	printf("Successfully changed file attributes\n");
	close(fd);
	return 0;
}
