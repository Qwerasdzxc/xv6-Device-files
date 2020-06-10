#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("setcp: error - provide both x and y coordinates\n");
        exit();
    }

    int x, y;

    x = atoi(argv[1]);
    y = atoi(argv[2]);

    if (setcp(x, y) < 0)
        printf("setcp: error - coordinates out of bounds\n");
	
	exit();
}
