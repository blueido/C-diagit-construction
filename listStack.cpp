#include "listStack.h"

//���캯��
listStack::listStack()
{
	this->head = new listStackNode[sizeof(listStackNode)];
	this->head->pnext = NULL;
	this->size = 0;
}

//��ջ
void listStack::push(listStackNode* data)
{
	if (data == NULL)
	{
		return;
	}	
	//������
	data->pnext = this->head->pnext;
	this->head->pnext = data;
	//����Ԫ�ظ���
	this->size++;
}

//��ջ
void listStack::pop()
{
	if (this->size == 0)
	{
		return;
	}
 	this->head->pnext = this->head->pnext->pnext;
	this->size--;
}

//����ջ��Ԫ��
listStackNode* listStack::front()
{
	if (this->size == 0)
	{
		return NULL;
	}
	return this->head->pnext;
}

//���ջ
void listStack::clear()
{
	if (this->size == 0)
	{
		return;
	}
	this->head->pnext = NULL;
	this->size = 0;
}

//��������
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