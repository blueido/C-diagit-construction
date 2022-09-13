#include "cyclicList.h"

//构造函数
cyclicList::cyclicList()
{
	this->headnode = new cyclicnode[sizeof(cyclicnode)];
	this->headnode->data = NULL;
	this->headnode->pnext = this->headnode;
	this->size = 0;
}

//插入函数
void cyclicList::insert(int pos, void* data)
{
	if (data == NULL)
	{
		return;
	}
	if (pos<0 || pos>this->size)
	{
		pos = this->size;
	}
	//缓存新数据
	cyclicnode* newnode = new cyclicnode[sizeof(cyclicnode)];
	newnode->data = data;
	newnode->pnext = NULL;
	//查找插入位置
	cyclicnode* current = this->headnode;
	for (int i = 0; i < pos; i++)
	{
		current = current->pnext;
	}
	//插入元素
	newnode->pnext = current->pnext;
	current->pnext = newnode;
	//更新容器参数
	this->size++;
}

//删除函数
void cyclicList::era(int pos)  //根据位置删除
{
	cyclicnode* current = this->headnode;
	//查找位置
	for (int i = 0; i < pos; i++)
	{
		current = current->pnext;
	}
	//删除pos位置的结点
	current->pnext = current->pnext->pnext;
	this->size--;
}

void cyclicList::era(void* data)  //根据值删除
{
	int pos = -1;
	if (data == NULL)
	{
		return;
	}
	cyclicnode* current = this->headnode->pnext;
	for (int i = 0; i < this->size; i++)
	{
		if (current->data == data)
		{
			pos = i;
			break;
		}
		current = current->pnext;
	}
	this->era(pos);
}

//查找函数
int cyclicList::findIt(void* data)
{
	int pos = -1;
	if (data == NULL)
	{
		return pos;
	}
	cyclicnode* current = this->headnode->pnext;
	for (int i = 0; i < this->size; i++)
	{
		if (current->data == data)
		{
			pos = i;
			break;
		}
		current = current->pnext;
	}
	return pos;
}

//显示函数
void cyclicList::show(print myPrint)
{
	//辅助结点
	cyclicnode* current = this->headnode->pnext;
	for (int i = 0; i < this->size; i++)
	{
		myPrint(current->data);
		current = current->pnext;
	}
}

//析构函数
cyclicList::~cyclicList()
{
	if (this->headnode != NULL)
	{
		delete[] this->headnode;
		this->headnode = NULL;
	}
	this->size = 0;
}