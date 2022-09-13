#include "linkList.h"

using namespace std;

//构造函数
linkList::linkList()
{
	this->size = 0;
	//头节点，头节点是不保存数据的
	//由于this->headnode是一个listNode类的对象，因此，初始化时需要对它进行内存分配
	this->headnode = new listNode[sizeof(listNode)];
	this->headnode->data = 0;
	this->headnode->pnode = NULL;
}

//查找函数
int linkList::findIt(void* data)
{
	if (data == NULL)
	{
		return -1;
	}
	int pos = -1;
	listNode* current_node;
	current_node = this->headnode->pnode;
	for (int i = 0; i < this->size; i++)
	{
		if (current_node->data == data)
		{
			pos = i;
			break;
		}
		current_node = current_node->pnode;
	}
	return pos;
}

//插入函数
void linkList::insert(int pos, void* data)
{
	if (data == NULL)
	{
		return;
	}

	//判断pos是否越界
	if (pos < 0 || pos > this->size)
	{
		pos = this->size;
	}

	//创建一个新的结点
	listNode* newnode = new listNode[sizeof(listNode)];
	newnode->data = data;
	newnode->pnode = NULL;

	//查找要插入的位置和该位置的前一个结点
	listNode* node_current;
	node_current = this->headnode;

	for (int i = 0; i < pos; i++)
	{
		node_current = node_current->pnode;
	}

	//将新结点放入链表
	newnode->pnode = node_current->pnode;
	node_current->pnode = newnode;

	//更新元素数量
	this->size++;
}

//删除函数
void linkList::era(int pos)
{
	if (pos == NULL || pos < 0 || pos >= this->size)
	{
		return;
	}

	//查找删除结点的前一个结点
	listNode* pcurrent = this->headnode;
	for (int i = 0; i < pos; i++)
	{
		pcurrent = pcurrent->pnode;
	}

	//缓存删除的结点
	listNode* pdel = pcurrent->pnode;
	pcurrent->pnode = pdel->pnode;
	free(pdel);
	this->size--;
}

//显示函数
void linkList::show(PRINTLISTNODE print)
{
	//辅助指针变量
	listNode* pcurrent = this->headnode->pnode;
	for (int i = 0; i < this->size; i++)
	{
		print(pcurrent->data);
		pcurrent = pcurrent->pnode;
	}
}

//析构函数
linkList::~linkList()
{
	while (this->headnode != NULL)
	{
		listNode* next = this->headnode->pnode;
		delete[] this->headnode;
		this->headnode = next;
	}
	this->size = 0;
}