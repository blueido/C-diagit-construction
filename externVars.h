#pragma once
#include <atomic>
#include <map>
#include <thread>

//全局变量声明
extern size_t g_pageSize = 4096; //内存页面大小
enum MemoryBlockSize {
	BYTE_START = 0,
	BYTE_64 = 64,
	BYTE_128 = 128,
	BYTE_256 = 256,
	BYTE_512 = 512,
	BYTE_1024 = 1024,
	BYTE_2048 = 2048,
	BYTE_4096 = 4096,
	BYTE_END
};
//记录不同大小内存块的数量
const int g_blockSizeMap[7][3] = {
	{BYTE_64, 0xFFFFFFFFFFFFFFFF, g_pageSize / 64},
	{BYTE_128, 0xFFFFFFFF, g_pageSize / 128},
	{BYTE_256, 0xFFFF, g_pageSize / 256},
	{BYTE_512, 0xFF, g_pageSize / 512},
	{BYTE_1024, 0xF, g_pageSize / 1024},
	{BYTE_2048, 0x3, g_pageSize / 2048},
	{BYTE_4096, 0x1, g_pageSize / 4096}
};
//内存计数器，记录当前申请的内存数量
extern std::atomic<int> g_memoryCounter(0);
//内存池，记录每个线程申请的内存地址
extern std::map<std::thread::id, void*> g_memoryPool;
//内存池起始地址，记录内存池的起始地址
extern void* g_memoryStartAddress;
//内存池当前地址，记录内存池当前可用的地址
extern void* g_memoryCurrentAddress;
//线程计数器，记录当前创建的线程数量
extern std::atomic<long long> g_pthreadCounter(0);