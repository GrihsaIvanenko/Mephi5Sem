#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/syscall.h>
#include <dirent.h>

#define _GNU_SOURCE
#include <unistd.h>

struct linux_dirent {
    unsigned long  d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

const int BUF_SIZE = 1024;

int main(int argc, char* argv[]) {
	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		printf("Usage %s <dir> or %s\n", argv[0], argv[0]);
		return 0;
	}
	if (argc > 2) {
		printf("Usage %s <dir> or %s\n", argv[0], argv[0]);
		exit(EXIT_FAILURE);
	}
	char* dirPath = ".";
	if (argc == 2) {
		dirPath = argv[1];
	}
	int fd = open(dirPath, O_RDONLY | O_DIRECTORY);
	if (errno != 0) {
		fprintf(stderr, "Error opening file \"%s\": ", dirPath);
		perror("");
		exit(EXIT_FAILURE);
	}
	char buf[BUF_SIZE];
	for (;;) {
		int nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
		if (nread == -1) {
			perror("Error making next syscall: ");
			close(fd);
			exit(EXIT_FAILURE);
		}
		if (nread == 0) {
			break;
		}
		for (int bpos = 0; bpos < nread;) {
			struct linux_dirent* d = (struct linux_dirent*) (buf + bpos);
			printf("%s\n", d->d_name);
			bpos += d->d_reclen;
		}
	}
	close(fd);
	return 0;
}
