#include <stdio.h>
#include "fs.h"

int main(void)
{
    printf("Start OK\n");
    int blkno, inodeno;
    FileSysInit();
    return 0;
}
// main(void)
// {
//   int blkno, inodeno;
//   FileSysInit();
//   inodeno = GetFreeInodeNum();
//   SetInodeBitmap(inode);
//   blkno = GetFreeBlockNum();
//   SetBlockBitmap(blkno);
//   ...
// }

// Inode = pInode;
// pInode=malloc(sizeof(Inode));
// GetInode(5,pInode);
// pInode0->allocBolcks=();
// pInode0->blockPointer[0]=10;
// putInode(5,pInode);