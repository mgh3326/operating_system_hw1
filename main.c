#include <stdio.h>
#include "fs.h"
#include "disk.h"
#include <stdlib.h>
int main(void)
{
	printf("Start OK\n");
	int blkno, inodeno;
	FileSysInit();
	inodeno = GetFreeInodeNum();
	// printf("%d",inodeno);

	SetInodeBitmap(inodeno);
	blkno = GetFreeBlockNum();
	ResetInodeBitmap(6);
	SetBlockBitmap(blkno);
	ResetBlockBitmap(6);
	Inode *pInode;
	pInode = malloc(BLOCK_SIZE / 8);
	GetInode(5, pInode);
	// pInode0->allocBolcks=();
	pInode->blockPointer[0] = 10;
	PutInode(5, pInode);
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

