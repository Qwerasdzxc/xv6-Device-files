#include "types.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"

int
devnullread(struct inode *ip, char *buf, int n, int offset)
{
    return n;
}

int
devnullwrite(struct inode *ip, char *buf, int n, int offset)
{
    return n;
}

int
devnullinit()
{
    devsw[DEVNULL].read = devnullread;
    devsw[DEVNULL].write = devnullwrite;
}