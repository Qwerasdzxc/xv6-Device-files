#include "types.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "buf.h"
#include "defs.h"
#include "mmu.h"
#include "param.h"
#include "proc.h"

int
devdiskread(struct inode *ip, char *buf, int n, int offset)
{
    int pos = offset / BSIZE, i;

    struct buf *b = bread(ip -> dev, pos);

    for (i = 0; i < n; i ++)
        buf[i] = b -> data[offset++];

    return n;
}

int
devdiskwrite(struct inode *ip, char *buf, int n, int offset)
{
    int pos = offset / BSIZE, i;

    struct buf *b = bread(ip -> dev, pos);

    for (i = 0; i < n; i ++)
        b -> data[offset++] = buf[i];

    log_write(b);
    brelse(b);
    
    return n;
}

int
devdiskinit()
{
    devsw[DEVDISK].read = devdiskread;
    devsw[DEVDISK].write = devdiskwrite;
}