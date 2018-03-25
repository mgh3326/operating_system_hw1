#include <stdio.h>
#include "fs.h"
#include "disk.h"
#include <stdlib.h>
#include <string.h>
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
    pInode->allocBlocks=0;
    // memset(pInode,0,512);
    for(int i=0;i<512;i++)
    {
        pInode[i].type=0;
        
    }
    for (int i=0;i<64;i++)
    {
        printf("%d : %d\n",i,pInode[i].type);
    }
	GetInode(5, pInode);
	for (int i=0;i<64;i++)
    {
        printf("%d : %d\n",i,pInode[i].type);
    }
	pInode->blockPointer[0] = 10;
	PutInode(5, pInode);
    for (int i=0;i<64;i++)
    {
        printf("%d : %d\n",i,pInode[i].type);
    }
    
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

