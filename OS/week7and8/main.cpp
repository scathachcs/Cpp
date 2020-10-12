#include <memory.h>
#include <stdio.h>
#include "FileSystem.h"

void test()
{
	formatDisk();

	SBitMap InodeBitMap;
	createEmptyBitMap(InodeBitMap, g_NumInodes);

	SBitMap DataBlockBitMap;
	createEmptyBitMap(DataBlockBitMap, g_NumBlocks);

	createFile("test.txt",  0, 'f', g_MaxFileSize);
	createFile("test1.txt", 0, 'f', 640);
	createFile("test1.txt", 0, 'f', 0);
	memcpy(InodeBitMap.pMapData, g_Disk+g_BlockBitMapSize, g_InodeBitMapSize);   //从虚拟硬盘中读取Inode的位示图
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                 //从虚拟硬盘读取数据块位示图
	printf("Inode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);

	removeFile("test.txt", 0);
	removeFile("test.txt", 0);
	memcpy(InodeBitMap.pMapData, g_Disk+g_BlockBitMapSize, g_InodeBitMapSize);   //从虚拟硬盘中读取Inode的位示图
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                 //从虚拟硬盘读取数据块位示图
	printf("\nInode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);
    

	char* gbuff=new char[640];
	SOpenFile* file= openFile("/test1.txt");
	readDataFromFile(gbuff,640,*file);                                          //从虚拟硬盘中读取文件内容
	
	char* pbuff = new char[200];
	int num=writeData2File(pbuff,200,*file);                                            //虚拟硬盘中写入文件越界，分配新的内存
	printf("预计写入字符数：200，实际写入字符数：%d" ,num);

	memcpy(InodeBitMap.pMapData, g_Disk+g_BlockBitMapSize, g_InodeBitMapSize);   //从虚拟硬盘中读取Inode的位示图
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                 //从虚拟硬盘读取数据块位示图
	printf("\nInode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);


	delete gbuff;
	delete pbuff;
	delete InodeBitMap.pMapData;
	delete DataBlockBitMap.pMapData;
}

int main(void)
{
	test();

	return 0;
} 