#include <stdio.h>
#include "fs.h"
#include "disk.h" //이거 추가하면 될라나
#include "temp.h" //이거 추가하면 될라나
#include <stdlib.h>
#include <string.h>
void FileSysInit(void)
{
    // printf("Block Size : %d\n", BLOCK_SIZE);
    // malloc(BLOCK_SIZE);
    DevCreateDisk();
    // DevReadBlock(1, 1);
    // printf("DevCreateDisk() 실행\n");
    char *buf = malloc(BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        buf[i] = '0';
    }
    // memset(buf, 0, sizeof(buf)); // 이러면 되는건가
    // printf("%s\n", buf);
    // fflush(stdout);
    for (int i = 0; i <= 6; i++) //1부터 6까지라서
    {
        DevWriteBlock(i, buf);
    }
    free(buf);
}
void SetInodeBitmap(int blkno)
{
    char *buf = malloc(BLOCK_SIZE);
    DevOpenDisk();
    DevReadBlock(1, buf);
    // printf("first : %s\n", buf);
    buf[blkno] = '1';
    // printf("second : %s\n", buf);
    DevWriteBlock(1, buf);
    free(buf);
}

void ResetInodeBitmap(int blkno)
{
    char *buf = malloc(BLOCK_SIZE);
    DevOpenDisk();
    DevReadBlock(1, buf);
    // printf("first : %s\n", buf);
    buf[blkno] = '0';
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
    buf[blkno] = '1';
    // printf("second : %s\n", buf);
    DevWriteBlock(2, buf);
    free(buf);
}

void ResetBlockBitmap(int blkno)
{
    char *buf = malloc(BLOCK_SIZE);
    DevOpenDisk();
    DevReadBlock(2, buf);
    // printf("first : %s\n", buf);
    buf[blkno] = '0';
    // printf("second : %s\n", buf);
    DevWriteBlock(2, buf);
    free(buf);
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
