#include "kernel/types.h";
#include "kernel/fcntl.h";
#include "user.h";

char str[] = "Test input";
char buf[512];

int
main (void)
{
    int fd, n;

    fd = open("/dev/devzero", O_RDWR);
    if (fd < 0) {
        printf("open error");
        exit();
    }

    n = write(fd, str, sizeof(str));
    if (n != sizeof(str)) {
        printf("write error");
        exit();
    }

    n = read(fd, buf, 512);
    if (n < 0) {
        printf("read error");
        exit();
    }

    printf("%s\n", buf);

    close(fd);
    exit();
}