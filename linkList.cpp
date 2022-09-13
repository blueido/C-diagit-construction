#include "linkList.h"

using namespace std;

//���캯��
linkList::linkList()
{
	this->size = 0;
	//ͷ�ڵ㣬ͷ�ڵ��ǲ��������ݵ�
	//����this->headnode��һ��listNode��Ķ�����ˣ���ʼ��ʱ��Ҫ���������ڴ����
	this->headnode = new listNode[sizeof(listNode)];
	this->headnode->data = 0;
	this->headnode->pnode = NULL;
}

//���Һ���
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

//���뺯��
void linkList::insert(int pos, void* data)
{
	if (data == NULL)
	{
		return;
	}

	//�ж�pos�Ƿ�Խ��
	if (pos < 0 || pos > this->size)
	{
		pos = this->size;
	}

	//����һ���µĽ��
	listNode* newnode = new listNode[sizeof(listNode)];
	newnode->data = data;
	newnode->pnode = NULL;

	//����Ҫ�����λ�ú͸�λ�õ�ǰһ�����
	listNode* node_current;
	node_current = this->headnode;

	for (int i = 0; i < pos; i++)
	{
		node_current = node_current->pnode;
	}

	//���½���������
	newnode->pnode = node_current->pnode;
	node_current->pnode = newnode;

	//����Ԫ������
	this->size++;
}

//ɾ������
void linkList::era(int pos)
{
	if (pos == NULL || pos < 0 || pos >= this->size)
	{
		return;
	}

	//����ɾ������ǰһ�����
	listNode* pcurrent = this->headnode;
	for (int i = 0; i < pos; i++)
	{
		pcurrent = pcurrent->pnode;
	}

	//����ɾ���Ľ��
	listNode* pdel = pcurrent->pnode;
	pcurrent->pnode = pdel->pnode;
	free(pdel);
	this->size--;
}

//��ʾ����
void linkList::show(PRINTLISTNODE print)
{
	//����ָ�����
	listNode* pcurrent = this->headnode->pnode;
	for (int i = 0; i < this->size; i++)
	{
		print(pcurrent->data);
		pcurrent = pcurrent->pnode;
	}
}

//��������
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