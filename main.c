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