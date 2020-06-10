#include "types.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"

int
devzeroread(struct inode *ip, char *buf, int n, int offset)
{
    uint target;

	target = n;
	while(n > 0){
		*buf++ = 0;
		--n;
	}

	return target - n;
}

int
devzerowrite(struct inode *ip, char *buf, int n, int offset)
{
    return n;
}

int
devzeroinit()
{
    devsw[DEVZERO].read = devzeroread;
    devsw[DEVZERO].write = devzerowrite;
}