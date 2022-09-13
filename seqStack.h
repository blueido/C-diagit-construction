#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define max_size 1024

class seqStack
{
public:
	//构造函数
	seqStack();

	//入栈操作
	void push_stack(void* data);

	//返回栈顶元素
	void* front();

	//出栈操作
	void pop_stack();

	//清空栈
	void clear();

	//析构函数
	~seqStack();

	void* data[max_size];
	int size;

};