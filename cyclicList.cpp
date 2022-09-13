#include "cyclicList.h"

//���캯��
cyclicList::cyclicList()
{
	this->headnode = new cyclicnode[sizeof(cyclicnode)];
	this->headnode->data = NULL;
	this->headnode->pnext = this->headnode;
	this->size = 0;
}

//���뺯��
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
	//����������
	cyclicnode* newnode = new cyclicnode[sizeof(cyclicnode)];
	newnode->data = data;
	newnode->pnext = NULL;
	//���Ҳ���λ��
	cyclicnode* current = this->headnode;
	for (int i = 0; i < pos; i++)
	{
		current = current->pnext;
	}
	//����Ԫ��
	newnode->pnext = current->pnext;
	current->pnext = newnode;
	//������������
	this->size++;
}

//ɾ������
void cyclicList::era(int pos)  //����λ��ɾ��
{
	cyclicnode* current = this->headnode;
	//����λ��
	for (int i = 0; i < pos; i++)
	{
		current = current->pnext;
	}
	//ɾ��posλ�õĽ��
	current->pnext = current->pnext->pnext;
	this->size--;
}

void cyclicList::era(void* data)  //����ֵɾ��
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

//���Һ���
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

//��ʾ����
void cyclicList::show(print myPrint)
{
	//�������
	cyclicnode* current = this->headnode->pnext;
	for (int i = 0; i < this->size; i++)
	{
		myPrint(current->data);
		current = current->pnext;
	}
}

//��������
cyclicList::~cyclicList()
{
	if (this->headnode != NULL)
	{
		delete[] this->headnode;
		this->headnode = NULL;
	}
	this->size = 0;
}