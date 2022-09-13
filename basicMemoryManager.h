#pragma once
#include <iostream>
#include <vector>
#include "externVars.h"
/*
1、确定整体需要使用的内存池大小，申请一块连续的内存区域作为内存池。
2、按照最低64bytes，最高4096bytes对齐的原则，将内存池划分为多个g_pageSize大小的内存块，
再将各个内存块按照64bytes，128bytes，256bytes，512bytes，1024bytes，2048bytes，4096bytes的大小进行分割，
每个内存块分割成多个子块，每个子块的大小为64bytes，128bytes，256bytes，512bytes，1024bytes，2048bytes，4096bytes中的一个。
这样就可以获取7个总大小相同，但是包含不同大小的小内存块的内存池，满足不同大小内存申请的需求。
*/

class my_memory_block {
public:
   //自身描述信息占用内存的起始地址=内存池描述信息的起始地址+内存池描述信息占用内存的大小+前面的内存块描述信息所占用内存的大小
	void* dataAddress; //内存块数据部分的起始地址
	size_t sizeType; //内存块大小
	bool isFinished; //内存块是否被分配
	size_t blockCount; //可用内存块数量
	std::vector<my_memory_block> childBlocks; //分割后的子块信息，记录分割后的子块的起始地址和大小
};

//memory_pool_desc:
//[|my_memory_pool desc infos|my_memory_block desc infos|my_memory_block data]
//my_memory_pool desc infos:
//[|memory_pool address start      memory_pool address end| my_memory_block desc info start]
//my_memory_block desc infos:
//[|my_memory_block1 desc  my_memory_block2 desc  my_memory_block3 desc  my_memory_block4 desc| my_memory_block1 data]
//my_memory_block data:
//[|my_memory_block1 data  my_memory_block2 data  my_memory_block3 data  my_memory_block4 data|]
class my_memory_pool {
public:
	my_memory_pool(void* pool_start, size_t total_size);
	void* myMalloc(size_t requestSize);
	bool myFree(void* ptr);
	bool spilteBlock(my_memory_block* memoryBlock, size_t sizeType);


	my_memory_block* pool_address; //内存池起始地址
	my_memory_block* blockInfoStartAddress; //所有内存块描述信息的起始地址
	my_memory_block* blockDataStartAddress; //所有内存块数据的起始地址
	my_memory_block* memoryBlocks; //内存块数组，记录每个内存块的信息
	size_t totalSize; //内存池总大小
	size_t blockCount; //块总数
};

my_memory_pool::my_memory_pool(void* pool_start, size_t total_size) {
	pool_address = (my_memory_block*)pool_start;
	totalSize = total_size;
	blockInfoStartAddress = pool_address + sizeof(my_memory_pool);
	blockCount = (totalSize - sizeof(my_memory_pool)) / (sizeof(my_memory_block) + g_pageSize);
	blockDataStartAddress = blockInfoStartAddress + blockCount * sizeof(my_memory_block);
	for (size_t i = 0; i < blockCount; ++i) {
		memoryBlocks[i].dataAddress = (void*)(blockDataStartAddress + i * g_pageSize);
		memoryBlocks[i].sizeType = 64 * 2 ^ i;
		memoryBlocks[i].isFinished = false;
		memoryBlocks[i].blockCount = 1;
		if (!spilteBlock(&memoryBlocks[i], memoryBlocks[i].sizeType)) {
			std::cerr << "Failed to split memory block of size " << memoryBlocks[i].sizeType << std::endl;
		}
	}
};

//将g_pageSize的块内存分割为多个sizeType大小的块内存，并返回分割后的块内存的起始地址
bool my_memory_pool::spilteBlock(my_memory_block* memoryBlock, size_t sizeType){
	if (sizeType > BYTE_4096 || sizeType < BYTE_64)
	{
		return false;
	}
	size_t blockCount = g_pageSize / sizeType;
	for (size_t i = 0; i < blockCount; ++i) {
		memoryBlock->childBlocks[i].dataAddress = (void*)((my_memory_block*)memoryBlock->dataAddress + i * sizeType);
		memoryBlock->childBlocks[i].sizeType = sizeType;
		memoryBlock->childBlocks[i].isFinished = false;
		memoryBlock->childBlocks[i].blockCount = blockCount;
		memoryBlock->childBlocks[i].childBlocks = {};
	}
	return true;
}

void* my_memory_pool::myMalloc(size_t requestSize) {
	//check size
	if (requestSize > BYTE_4096 || requestSize < BYTE_64)
	{
		return nullptr;
	}
	//find a suitable block
	for (size_t i = 0; i < blockCount; ++i) {
		if (memoryBlocks[i].sizeType >= requestSize) {
			if (memoryBlocks[i].isFinished || memoryBlocks[i].childBlocks.empty()) {
				std::cerr << "current memory block of size " << memoryBlocks[i].sizeType << " is fully allocated, try next block" << std::endl;
				continue;
			}
			else{
				for (size_t j = 0; j < memoryBlocks[i].childBlocks.size(); ++j) {
					if (memoryBlocks[i].childBlocks[j].blockCount && memoryBlocks[i].childBlocks[j].sizeType >= requestSize) {
						memoryBlocks[i].childBlocks[j].blockCount -= 1;
						if (memoryBlocks[i].childBlocks[j].blockCount == 0) {
							memoryBlocks[i].childBlocks[j].isFinished = true;
							memoryBlocks[i].isFinished = true;
						}
						return memoryBlocks[i].childBlocks[j].dataAddress;
					}
				}
			}
		}
	}
	//not found a suitable block
	return nullptr;
};

bool my_memory_pool::myFree(void* ptr){
	if (ptr == nullptr) {
		return false;
	}
	for (int i = 0; i < blockCount; ++i) {
		if (memoryBlocks[i].childBlocks.empty()) {
			continue;
		}
		for (int j = 0; j < memoryBlocks[i].childBlocks.size(); ++j) {
			if (memoryBlocks[i].childBlocks[j].dataAddress == ptr) {
				memset(memoryBlocks[i].childBlocks[j].dataAddress, 0, memoryBlocks[i].childBlocks[j].sizeType);
				ptr = nullptr;
				memoryBlocks[i].childBlocks[j].blockCount += 1;
				memoryBlocks[i].childBlocks[j].isFinished = false;
				memoryBlocks[i].isFinished = false;
				return true;
			}
		}
	}
	return false;
}