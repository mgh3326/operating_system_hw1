#include <stdio.h>
#include "fs.h"
#include "disk.h" //이거 추가하면 될라나
void FileSysInit(void)
{
    printf("Block Size : %d\n", BLOCK_SIZE);
    // malloc(BLOCK_SIZE);
    DevCreateDisk();
    // DevReadBlock(1, 1);
    printf("DevCreateDisk() 실행\n");
}
void SetInodeBitmap(int blkno)
{
}

void ResetInodeBitmap(int blkno)
{
}

void SetBlockBitmap(int blkno)
{
}

void ResetBlockBitmap(int blkno)
{
}

void PutInode(int blkno, Inode *pInode)
{
}

void GetInode(int blkno, Inode *pInode)
{
}

int GetFreeInodeNum(void)
{
}

int GetFreeBlockNum(void)
{
}
