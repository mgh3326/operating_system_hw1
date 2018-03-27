#include <stdio.h>
#include "fs.h"
#include "disk.h" //이거 추가하면 될라나
#include "temp.h" //이거 추가하면 될라나
#include <stdlib.h>
#include <string.h>
void FileSysInit(void) //Success
{
    DevCreateDisk();
    // DevOpenDisk();

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
    //DevOpenDisk();
    DevReadBlock(INODE_BITMAP_BLK_NUM, buf);
    // printf("first : %s\n", buf);
    // inodeno%8
    // if(inodeno%8==0){//0일때
    // buf[inodeno / 8] |= 128;
    // }
    // else{
    // buf[inodeno / 8] |= 128 / ((inodeno % 8)+1);//원래 내꺼
    buf[inodeno / 8] |= 1 << (8 - 1 - (inodeno % 8));

    // printf("second : %s\n", buf);
    DevWriteBlock(INODE_BITMAP_BLK_NUM, buf);
    free(buf);
}

void ResetInodeBitmap(int inodeno)
{
    char *buf = malloc(BLOCK_SIZE);
    //DevOpenDisk();
    DevReadBlock(INODE_BITMAP_BLK_NUM, buf);
    // printf("first : %s\n", buf);
    // buf[inodeno / 8] ^= 128 /((inodeno % 8)+1);
    buf[inodeno / 8] &= ~(1 << (8 - 1 - (inodeno % 8)));

    // printf("second : %s\n", buf);
    DevWriteBlock(INODE_BITMAP_BLK_NUM, buf);
    free(buf);
}

void SetBlockBitmap(int blkno)
{
    char *buf = malloc(BLOCK_SIZE);
    //DevOpenDisk();
    DevReadBlock(BLOCK_BITMAP_BLK_NUM, buf);
    // printf("first : %s\n", buf);

    // buf[blkno / 8] |= 128 / ((blkno % 8)+1);
    //  buf[blkno / 8] |= 1 << (8 - 1 - blkno % 8);
    buf[blkno / 8] |= 1 << (8 - 1 - (blkno % 8));

    // printf("second : %s\n", buf);
    DevWriteBlock(BLOCK_BITMAP_BLK_NUM, buf);
    free(buf);
}

void ResetBlockBitmap(int blkno)
{
    char *buf = malloc(BLOCK_SIZE);
    //DevOpenDisk();
    DevReadBlock(BLOCK_BITMAP_BLK_NUM, buf);
    // printf("first : %d\n", buf[0]);
    // buf[blkno / 8] ^= 128 / ((blkno % 8)+1);
    //buf[blkno / 8] &= ~(1 << (8 - 1 - blkno % 8));
    buf[blkno / 8] &= ~(1 << (8 - 1 - (blkno % 8)));

    // printf("second : %d\n", buf[0]);

    DevWriteBlock(BLOCK_BITMAP_BLK_NUM, buf);
    free(buf);
}

void PutInode(int inodeno, Inode *pInode)
{
    char *buf = malloc(BLOCK_SIZE);
    //DevOpenDisk();
    DevReadBlock((inodeno / 8) + INODELIST_BLK_FIRST, buf);
    // pInode->allocBlocks--;
    // memcpy(buf+(blkno % 8)*64, (void *)&pInode->type, BLOCK_SIZE/8);
    memcpy(buf + (inodeno % 8) * sizeof(Inode), pInode, sizeof(Inode));

    DevWriteBlock((inodeno / 8) + INODELIST_BLK_FIRST, buf);
    free(buf);

    //   memcpy((void *)&pInode->type, (void *)&buf+(blkno % 8)*64, BLOCK_SIZE/8);
}

void GetInode(int inodeno, Inode *pInode)
{
    char *buf = malloc(BLOCK_SIZE);

    //DevOpenDisk();
    //3번째 블록에 0~7
    //4             8~15
    //5             16~23
    //6             24~31
    DevReadBlock((inodeno / 8) + INODELIST_BLK_FIRST, buf);
    // for(int i=0;i<512;i++)
    // {
    //     printf("%d : %d \n",i,pInode[i].type);
    // }

    //memcpy((void *)&pInode->type, (void *)&buf+(blkno % 8)*64, BLOCK_SIZE/8);
    memcpy(pInode, buf + (inodeno % 8) * sizeof(Inode), sizeof(Inode));

    // pInode->allocBlocks = 0;
    // pInode->allocBlocks++;
    free(buf);

    // pInode->type=?;

    // pInode->blockPointer[NUM_OF_BLK_PTR]; // Direct block pointers
}

int GetFreeInodeNum(void)
{
    char *buf = malloc(BLOCK_SIZE);
    //DevOpenDisk();
    DevReadBlock(INODE_BITMAP_BLK_NUM, buf);

    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        //if pBlock[i] == 11111111, continue
        if (buf[i] == -1)
            continue;

        for (int j = 7; j >= 0; j--)
        {
            if (!(buf[i] >> j & 1))
            {
                return (i * 8) + (7 - j);
            }
        }
    }
    // int binary[20] = { 0, };
    // int position = 0;
    // int index;
    // for(int i=0;i<BLOCK_SIZE;i++)
    // {
    //      int decimal = buf[i];

    //     while (1)
    //     {
    //         binary[position] = decimal % 2;    // 배열에 나머지 저장
    //         decimal = decimal / 2;             // 2로 나눈 몫을 저장

    //         position++;    // 자릿수 변경
    //          if (decimal == 0)    // 몫이 0이 되면 반복을 끝냄
    //          {
    //             index=0;
    //             break;
    //          }

    //     }
    //     for (int j = position - 1; j >= 0; j--)
    //         {
    //             //printf("%d", binary[j]);
    //             if(binary[j]==0)
    //                 {
    //                         free(buf);

    //                     return index;
    //                 }
    //             index++;
    //         }
    // }
    //     free(buf);

    // return -1; //실패할 경우
}

int GetFreeBlockNum(void)
{
    char *buf = malloc(BLOCK_SIZE);
    //DevOpenDisk();
    DevReadBlock(BLOCK_BITMAP_BLK_NUM, buf);

    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        //if pBlock[i] == 11111111, continue
        if (buf[i] == -1)
            continue;

        for (int j = 7; j >= 0; j--)
        {
            if (!(buf[i] >> j & 1))
            {
                return (i * 8) + (7 - j);
            }
        }
    }
    // int binary[20] = { 0, };
    // int position = 0;
    // int index;
    // for(int i=0;i<BLOCK_SIZE;i++)
    // {
    //      int decimal = buf[i];

    //     while (1)
    //     {
    //         binary[position] = decimal % 2;    // 배열에 나머지 저장
    //         decimal = decimal / 2;             // 2로 나눈 몫을 저장

    //         position++;    // 자릿수 변경
    //          if (decimal == 0)    // 몫이 0이 되면 반복을 끝냄
    //          {
    //             index=0;
    //             break;
    //          }

    //     }
    //     for (int j = position - 1; j >= 0; j--)
    //         {
    //             //printf("%d", binary[j]);
    //             if(binary[j]==0)
    //             {
    //                             free(buf);

    //                 return index;
    //             }

    //             index++;
    //         }
    // }
    //             free(buf);

    // return -1; //실패할 경우
}
