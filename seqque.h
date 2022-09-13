#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define max_size 1024

class seqque
{
public:
	//构造函数
	seqque();

	//入队
	void push(void* data);

	//返回队头元素
	void* front();

	//返回队尾元素
	void* back();

	//清空
	void clear();

	//出队
	void pop();

	//析构函数
	~seqque();

	void* data[max_size];
	int size;
};