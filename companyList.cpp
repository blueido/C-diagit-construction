#include "companyList.h"

//构造函数
companylist::companylist()
{
	//分配内存
	this->head = new linknode[sizeof(linknode)];
	//初始化
	this->head->pnext = NULL;
	this->size = 0;
}

//插入函数
void companylist::insert(int pos, linknode* data)
{
	if (data == NULL)
	{
		return;
	}
	if (pos<0 || pos>this->size)
	{
		pos = this->size;
	}

	//查找插入位置
	linknode* current_node = this->head;
	for (int i = 0; i < pos; i++)
	{
		current_node = current_node->pnext;
	}

	//插入新节点
	data->pnext = current_node->pnext;
	current_node->pnext = data;

	this->size++;
}

//删除函数
void companylist::era(int pos)
{
	if (pos<0 || pos>this->size)
	{
		return;
	}
	//辅助指针变量
	linknode* current_node = this->head;
	for (int i = 0; i < pos; i++)
	{
		current_node = current_node->pnext;
	}

	//删除结点
	current_node->pnext = current_node->pnext->pnext;

	this->size--;
}

//显示函数
void companylist::show(PRINTNODE myprint)
{
	//辅助指针
	linknode* current_node = this->head->pnext;
	for (int i = 0; i < this->size; i++)
	{
		myprint(current_node);
		current_node = current_node->pnext;
	}
}

//查找函数
int companylist::findIt(linknode* data)
{
	int pos = -1;
	if (data == NULL)
	{
		return -1;
	}
	//辅助指针
	linknode* current_node = this->head->pnext;
	for (int i = 0; i < this->size; i++)
	{
		if (current_node == data)
		{
			pos = i;
			break;
		}
		current_node = current_node->pnext;
	}
	return pos;
}

int companylist::findIt(linknode* data, compare myCompare)
{
	int pos = -1;
	if (data == NULL)
	{
		return -1;
	}
	//辅助指针
	linknode* current_node = this->head->pnext;
	for (int i = 0; i < this->size; i++)
	{
		if (myCompare(current_node, data)==0)
		{
			pos = i;
			break;
		}
		current_node = current_node->pnext;
	}
	return pos;
}

//析构函数
companylist::~companylist()
{
	if (this->head != NULL)
	{
		delete[] this->head;
		this->head = NULL;
	}
	this->size = 0;
}