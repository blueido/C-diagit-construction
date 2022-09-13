#include "seqStack.h"

//构造函数
seqStack::seqStack()
{
	for (int i = 0; i < max_size; i++)
	{
		this->data[i] = NULL;
	}
	this->size = 0;
}

//入栈操作
void seqStack::push_stack(void* data)
{
	if (this->size == max_size)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}
	this->data[this->size] = data;
	this->size++;
}

//返回栈顶元素
void* seqStack::front()
{
	if (this->size == 0)
	{
		return NULL;
	}
	return this->data[this->size - 1];
}

//出栈操作
void seqStack::pop_stack()
{
	if (this->size == 0)
	{
		return ;
	}
	this->data[this->size - 1] = NULL;
	this->size--;
}

//清空栈
void seqStack::clear()
{
	if (this->size == 0)
	{
		return;
	}
	for (int i = 0; i < this->size; i++)
	{
		this->data[i] = NULL;
	}
	this->size = 0;
}

//析构函数
seqStack::~seqStack()
{
	for (int i = 0; i < this->size; i++)
	{
		if (this->data != NULL)
		{
			this->data[i] = NULL;
		}
	}
	this->size = 0;
}