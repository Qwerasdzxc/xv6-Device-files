#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user.h"

#define BUF_SIZE 12

char str[] = "Test input";
char buf[BUF_SIZE];

int
main (void)
{
    int fd, n;

    fd = open("/dev/devrand", O_RDWR);
    if (fd < 0) {
        printf("open error");
        exit();
    }

    n = write(fd, str, sizeof(str));
    if (n != sizeof(str)) {
        printf("write error");
        exit();
    }

    n = read(fd, buf, BUF_SIZE);
    if (n < 0) {
        printf("read error");
        exit();
    }

    printf("%s\n", buf);

    close(fd);
    exit();
}