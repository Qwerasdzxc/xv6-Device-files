#include "types.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "devkmesg.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"

#define KMESG_BUFF_SIZE 4096

char kmesgbuff[KMESG_BUFF_SIZE];
uint kmesgwriteoffset;

int
devkmesgread(struct inode *ip, char *buf, int n, int offset)
{
    int i;

    if (offset >= kmesgwriteoffset)
        offset = 0;

    for (i = offset; i < offset + n && i < kmesgwriteoffset; i ++) {
        buf[i-offset] = kmesgbuff[i];
    }

	return i;
}

void
writetokmesg(char c)
{
    kmesgbuff[kmesgwriteoffset++ % KMESG_BUFF_SIZE] = c;
}

int
devkmesginit()
{
    devsw[DEVKMESG].read = devkmesgread;
}