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