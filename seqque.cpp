#include "seqque.h"

//构造函数
seqque::seqque()
{
	for (int i = 0; i < max_size; i++)
	{
		this->data[i] = NULL;
	}
	this->size = 0;
}

//入队
void seqque::push(void* data)
{
	if (data == NULL)
	{
		return;
	}
	//数组左边做队头
	this->data[this->size] = data;
	//数组右边做队头
	//this->data[max_size - 1 - this->size] = data;

	//队列元素数量更新
	this->size++;
}

//返回队头元素
void* seqque::front()
{
	if (this->size == 0)
	{
		return NULL;
	}
	return this->data[0];
}

//返回队尾元素
void* seqque::back()
{
	if (this->size == 0)
	{
		return NULL;
	}
	return this->data[this->size - 1];
}

//清空
void seqque::clear()
{
	for (int i = 0; i < this->size; i++)
	{
		this->data[i] = NULL;
	}
	this->size = 0;
}

//出队,队列是先进先出
void seqque::pop()
{
	if (this->size == 0)
	{
		return;
	}
	for (int i = 0; i < this->size - 1; i++)
	{
		//队列是先进先出，因此每次弹出的应该是队头元素
		this->data[i] = this->data[i + 1];
	}
	this->size--;
}

//析构函数
seqque::~seqque()
{
	for (int i = 0; i < this->size; i++)
	{
		if (this->data[i] != NULL)
		{
			delete this->data[i];
			this->data[i] = NULL;
		}
	}
	this->size = 0;
}