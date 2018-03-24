#include <stdio.h>
#include "fs.h"

int main(void)
{
    printf("Start OK\n");
    int blkno, inodeno;
    FileSysInit();
    inodeno = GetFreeInodeNum();
    // printf("%d",inodeno);
    SetInodeBitmap(2);
    ResetInodeBitmap(6);
    SetBlockBitmap(3);
    SetBlockBitmap(6);
    ResetBlockBitmap(6);
    Inode *pInode;
    GetInode(0, pInode);
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