#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/lseek.h"
#include "user.h"

#define BUF_SIZE 600

char buffer[BUF_SIZE] = "writing and reading from /dev/disk directly into hard disk";

int
main (void)
{
    int fd, n;

    char result[BUF_SIZE];

    int i;

    fd = open("/dev/devdisk", O_RDWR);
    if (fd < 0) {
        printf("open error");
        exit();
    }

    n = write(fd, buffer, BUF_SIZE);
    if (n != BUF_SIZE) {
        printf("write error");
        exit();
    }

    lseek(fd, 0, SEEK_SET);

    n = read(fd, result, BUF_SIZE);
    if (n < 0) {
        printf("read error");
        exit();
    }

    printf("%s\n", result);

    close(fd);
    exit();
}