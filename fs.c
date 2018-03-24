#include <stdio.h>
#include "fs.h"
#include "disk.h" //이거 추가하면 될라나
#include "temp.h" //이거 추가하면 될라나
#include <stdlib.h>
#include <string.h>
void FileSysInit(void)
{
    DevCreateDisk();
    char *buf = malloc(BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        buf[i] = 0;
    }
    // memset(buf, 0, sizeof(buf)); // 이러면 되는건가
    for (int i = 0; i <= 6; i++) //1부터 6까지라서
    {
        DevWriteBlock(i, buf);
    }
    free(buf);
}
void SetInodeBitmap(int inodeno)
{
    char *buf = malloc(BLOCK_SIZE);
    DevOpenDisk();
    DevReadBlock(1, buf);
    // printf("first : %s\n", buf);
    // inodeno%8

    buf[inodeno / 8] |= 128 / (inodeno % 8);

    // printf("second : %s\n", buf);
    DevWriteBlock(1, buf);
    free(buf);
}

void ResetInodeBitmap(int inodeno)
{
    char *buf = malloc(BLOCK_SIZE);
    DevOpenDisk();
    DevReadBlock(1, buf);
    // printf("first : %s\n", buf);
    buf[inodeno / 8] ^= 128 / (inodeno % 8);
    // printf("second : %s\n", buf);
    DevWriteBlock(1, buf);
    free(buf);
}

void SetBlockBitmap(int blkno)
{
    char *buf = malloc(BLOCK_SIZE);
    DevOpenDisk();
    DevReadBlock(2, buf);
    // printf("first : %s\n", buf);
    buf[blkno / 8] |= 128 / (blkno % 8);
    // printf("second : %s\n", buf);
    DevWriteBlock(2, buf);
    free(buf);
}

void ResetBlockBitmap(int blkno)
{
    char *buf = malloc(BLOCK_SIZE);
    DevOpenDisk();
    DevReadBlock(2, buf);
    // printf("first : %d\n", buf[0]);
    buf[blkno / 8] ^= 128 / (blkno % 8);

    // printf("second : %d\n", buf[0]);

    DevWriteBlock(2, buf);
    free(buf);
}

void PutInode(int blkno, Inode *pInode)
{
}

void GetInode(int blkno, Inode *pInode)
{
    char *buf = malloc(BLOCK_SIZE);

    DevOpenDisk();
    DevReadBlock(blkno % 8, buf);
    pInode = malloc(1 * sizeof *pInode);//이게 필요할라나

    // pInode->allocBlocks = 0;
    pInode->allocBlocks = blkno % 8;
    // pInode->type=?;

    // pInode->blockPointer[NUM_OF_BLK_PTR]; // Direct block pointers
}

int GetFreeInodeNum(void)
{
}

int GetFreeBlockNum(void)
{
}
