//제공 해준다고함

#include <stdio.h> 
#include "fat.h"

main(void)
{ 
  int blkno, inodeno;
  FileSysInit();
  inodeno = GetFreeInodeNum();
  SetInodeBitmap(inode);
  blkno = GetFreeBlockNum();
  SetBlockBitmap(blkno);
  ...
}

Inode = pInode;
pInode=malloc(sizeof(Inode));
GetInode(5,pInode);
pInode0->allocBolcks=();
pInode0->blockPointer[0]=10;
putInode(5,pInode);