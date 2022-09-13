#include "listStack.h"

//构造函数
listStack::listStack()
{
	this->head = new listStackNode[sizeof(listStackNode)];
	this->head->pnext = NULL;
	this->size = 0;
}

//入栈
void listStack::push(listStackNode* data)
{
	if (data == NULL)
	{
		return;
	}	
	//插入结点
	data->pnext = this->head->pnext;
	this->head->pnext = data;
	//更新元素个数
	this->size++;
}

//出栈
void listStack::pop()
{
	if (this->size == 0)
	{
		return;
	}
 	this->head->pnext = this->head->pnext->pnext;
	this->size--;
}

//返回栈顶元素
listStackNode* listStack::front()
{
	if (this->size == 0)
	{
		return NULL;
	}
	return this->head->pnext;
}

//清空栈
void listStack::clear()
{
	if (this->size == 0)
	{
		return;
	}
	this->head->pnext = NULL;
	this->size = 0;
}

//析构函数
listStack::~listStack()
{
	if (this->head->pnext != NULL)
	{
		this->head->pnext = this->head->pnext->pnext;
		//delete this->head->pnext;
		this->head->pnext = NULL;
	}
	this->size = 0;
}