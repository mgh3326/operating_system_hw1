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

    buf[blkno / 8] |= 128 / ((blkno % 8));
    
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
    buf[blkno / 8] ^= 128 / ((blkno % 8));

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
    //3번째 블록에 0~7
    //4             8~15
    //5             16~23
    //6             24~31
    DevReadBlock((blkno % 8)+3, buf);
    pInode = malloc(1 * sizeof *pInode);//이게 필요할라나

    // pInode->allocBlocks = 0;
    pInode->allocBlocks = (blkno % 8)+3;
    // pInode->type=?;

    // pInode->blockPointer[NUM_OF_BLK_PTR]; // Direct block pointers
}

int GetFreeInodeNum(void)
{
        char *buf = malloc(BLOCK_SIZE);
        DevOpenDisk();
        DevReadBlock(1, buf);
        int binary[20] = { 0, };
        int position = 0;
        int index;
        for(int i=0;i<BLOCK_SIZE;i++)
        {
             int decimal = buf[i];

            while (1)
            {
                binary[position] = decimal % 2;    // 배열에 나머지 저장
                decimal = decimal / 2;             // 2로 나눈 몫을 저장

                position++;    // 자릿수 변경
                 if (decimal == 0)    // 몫이 0이 되면 반복을 끝냄
                 {  
                    index=0;
                    break;
                 }
                    
            }
            for (int j = position - 1; j >= 0; j--)
                {
                    //printf("%d", binary[j]);
                    if(binary[j]==0)
                        return index;
                    index++;
                }
        }
        return -1; //실패할 경우

}

int GetFreeBlockNum(void)
{
    char *buf = malloc(BLOCK_SIZE);
        DevOpenDisk();
        DevReadBlock(2, buf);
        int binary[20] = { 0, };
        int position = 0;
        int index;
        for(int i=0;i<BLOCK_SIZE;i++)
        {
             int decimal = buf[i];

            while (1)
            {
                binary[position] = decimal % 2;    // 배열에 나머지 저장
                decimal = decimal / 2;             // 2로 나눈 몫을 저장

                position++;    // 자릿수 변경
                 if (decimal == 0)    // 몫이 0이 되면 반복을 끝냄
                 {  
                    index=0;
                    break;
                 }
                    
            }
            for (int j = position - 1; j >= 0; j--)
                {
                    //printf("%d", binary[j]);
                    if(binary[j]==0)
                        return index;
                    index++;
                }
        }
        return -1; //실패할 경우
}
