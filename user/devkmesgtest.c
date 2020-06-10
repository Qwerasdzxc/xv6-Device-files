#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user.h"
#include "kernel/devkmesg.h"

#define READ_COUNT 40
#define BUF_SIZE 1024

char buf[BUF_SIZE];

int
main (void)
{
    int fd, n;

    fd = open("/dev/devkmesg", O_RDONLY);
    if (fd < 0) {
        printf("open error");
        exit();
    }

    n = read(fd, buf, READ_COUNT);
    if (n < 0) {
        printf("read error");
        exit();
    }

    printf("%s", buf);

    printf("\n\nKRAJ ISPISA\n\n", buf);

    n = read(fd, buf, READ_COUNT);
    if (n < 0) {
        printf("read error");
        exit();
    }

    printf("%s\n", buf);

        printf("\n\nKRAJ ISPISA\n\n", buf);

    n = read(fd, buf, READ_COUNT);
    if (n < 0) {
        printf("read error");
        exit();
    }

    printf("%s\n", buf);

    close(fd);
    exit();
}