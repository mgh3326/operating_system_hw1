#include <stdio.h>
#include "fs.h"
#include "disk.h"

/******************/
#include <fcntl.h>
#include <unistd.h>
/******************/

void testcase1(void)
{
	int n = GetFreeInodeNum();
	printf("free inode num : %d\n", n);

	Inode inode = {10, 11, 0};
	Inode check;
	PutInode(1, &inode);
	SetInodeBitmap(2);

	GetInode(1, &check);
	printf("%d, %d\n", check.allocBlocks, check.type);

	n = GetFreeInodeNum();
	printf("free inode num : %d\n", n);

	inode.allocBlocks = 1234;
	inode.type = 9999;
	PutInode(0, &inode);
	SetInodeBitmap(0);

	GetInode(0, &check);
	printf("%d, %d\n", check.allocBlocks, check.type);

	n = GetFreeInodeNum();
	printf("free inode num : %d\n", n);
}

// checking set inode bitmap and get free inode number
void testcase2()
{
	for (int i = 1; i < 100; ++i)
	{
		SetInodeBitmap(i);
	}
	int n = GetFreeInodeNum();
	printf("free : %d\n", n);

	SetInodeBitmap(0);
	n = GetFreeInodeNum();
	printf("free : %d\n", n);
}

void testcase3()
{
	Inode inode = {1, 2};
	PutInode(1, &inode);

	inode.allocBlocks = 11;
	inode.type = 22;
	PutInode(2, &inode);

	Inode result = {7, 7};
	for (int i = 0; i < 3; ++i)
	{
		GetInode(i, &result);
		printf("%d, %d\n", result.allocBlocks, result.type);
	}
}
void testcase4()
{
	DevCreateDisk();
	DevOpenDisk();

	int blkno, inodeno;
	FileSysInit();

	Inode inode = {3, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	PutInode(0, &inode);
	GetInode(0, &inode);

	for (int i = 0; i < NUM_OF_BLK_PTR; i++)
		printf("blockPointer[%d] : %d\n", i, inode.blockPointer[i]);

	inodeno = GetFreeInodeNum();
	printf("before setInodeBitmap() : %d\n", inodeno);
	SetInodeBitmap(inodeno);
	printf("after setInodeBitmap() : %d\n", GetFreeInodeNum());

	blkno = GetFreeBlockNum();
	SetBlockBitmap(blkno);

	printf("GetFreeBlocNum() and SetBlockBitamp() : %d\n", blkno);
	printf("next free block num : %d\n", GetFreeBlockNum());

	FileSysInit();
	printf("File System Initialize ...\n");
	printf("GetFreeInodeNum() : %d\n", GetFreeInodeNum());
	printf("GetFreeBlockNum() : %d\n", GetFreeBlockNum());
}

void testcase5()
{
	const int maxBitCount = 512 << 3;
	int accum = 0;
	for (int i = 0; i < maxBitCount; ++i)
	{
		SetBlockBitmap(i);
	}
	for (int i = maxBitCount - 1; i >= 0; --i)
	{
		ResetBlockBitmap(i);
		int n = GetFreeBlockNum();
		accum += n;
	}
	int correctAns = (((maxBitCount - 1) * (maxBitCount)) >> 1);
	int ans = accum;
	printf("%d\n", correctAns ^ ans);
}

void testcase6()
{
	int inodeCount = INODELIST_BLKS * BLOCK_SIZE / sizeof(Inode);
	Inode inode = {0, 0, 0};
	int result = 1;
	int log[32] = {0};
	for (int index = 0; index < inodeCount; ++index)
	{
		PutInode(index, &inode);
		inode.allocBlocks++;
		inode.type++;
		/** inode.allocBlocks += inode.type; */
		/** inode.type += inode.allocBlocks; */
	}

	for (int index = 0; index < inodeCount; ++index)
	{
		GetInode(index, &inode);
		int isSame = (inode.allocBlocks == index && inode.type == index);
		if (!isSame)
		{
			log[index] = 1;
		}
		result &= isSame;
	}
	printf("----------------\n%d\n----------------\n", result);
	for (int index = 0; index < inodeCount; ++index)
	{
		if (log[index] == 1)
		{
			printf("inode %d has a problem", index);
		}
	}
}

void testcase7()
{
	int fd, result = 0;
	int acc = 0;
	fd = open("MY_DISK", O_RDWR);
	lseek(fd, 0, SEEK_SET);
	char c = 0;
	while (1)
	{
		int nread = read(fd, &c, 1);
		if (nread < 1)
		{
			break;
		}
		result += c;
		acc += 1;
	}
	printf("%d, %d\n", acc, result);
}

void (*func[])(void) = {testcase1, testcase2, testcase3, testcase4, testcase5, testcase6, testcase7};
void main(int argc, char *args[])
{
	// int inodeno, blkno;
	// Inode temp, temp2, temp3;
	// FileSysInit();
	// for (int i = 0; i < 30; i++)
	// 	SetInodeBitmap(i);
	// temp.allocBlocks = 3;
	// temp.type = 7;
	// temp.blockPointer[0] = 227;
	// temp.blockPointer[1] = 158;
	// inodeno = GetFreeInodeNum();
	// blkno = GetFreeBlockNum();
	// printf("free inodenum : %d\n", inodeno);
	// PutInode(inodeno, &temp);
	// SetInodeBitmap(inodeno);
	// GetInode(inodeno, &temp2);
	// printf("Inode 2 -- AllocBlocks : %d\n", temp2.allocBlocks);
	// printf("Inode 2 -- Type : %d\n", temp2.type);
	// temp2.allocBlocks = 582;
	// inodeno = GetFreeInodeNum();
	// printf("free inodenum : %d\n", inodeno);
	// PutInode(inodeno, &temp2);
	// SetInodeBitmap(inodeno);
	// GetInode(inodeno, &temp3);
	// printf("Inode 3 -- AllockBlocks : %d\n", temp3.allocBlocks);
	// printf("Inode 3 -- Type : %d\n", temp3.type);
	// printf("Inode 3 -- blockPointer[0] : %d\n", temp3.blockPointer[0]);
	// printf("Inode 3 -- blockPointer[1] : %d\n", temp3.blockPointer[1]);
	// ResetInodeBitmap(7);
	// ResetInodeBitmap(14);
	// ResetInodeBitmap(21);
	// ResetInodeBitmap(28);
	// char *block = (char *)malloc(BLOCK_SIZE);
	// DevReadBlock(1, block);
	// for (int i = 0; i < 5; i++)
	// {
	// 	for (int j = 7; j >= 0; j--)
	// 		printf("%d", *(block + i) >> j & 1);
	// 	printf("\n");
	// }
	// printf("실행 완료\n");
	FileSysInit();
	if (argc < 2)
	{
		printf("인자 넣어라\n");
		// func[1]();
		testcase1();
		return;
	}
	func[*args[1] - '0']();
}
