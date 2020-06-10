#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    int x, y;
    int *xp, *yp;

    xp = &x;
    yp = &y;

	getcp(xp, yp);

    printf("getcp: x= %d y= %d\n", x, y);
	exit();
}
