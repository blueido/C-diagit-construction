#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class listStackNode
{
public:
	listStackNode* pnext;
};

class listStack
{
public:
	//构造函数
	listStack();

	//入栈
	void push(listStackNode* data);

	//出栈
	void pop();

	//返回栈顶元素
	listStackNode* front();

	//清空栈
	void clear();

	//析构函数
	~listStack();

	listStackNode* head;
	int size;
};