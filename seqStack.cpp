#include "seqStack.h"

//���캯��
seqStack::seqStack()
{
	for (int i = 0; i < max_size; i++)
	{
		this->data[i] = NULL;
	}
	this->size = 0;
}

//��ջ����
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

//����ջ��Ԫ��
void* seqStack::front()
{
	if (this->size == 0)
	{
		return NULL;
	}
	return this->data[this->size - 1];
}

//��ջ����
void seqStack::pop_stack()
{
	if (this->size == 0)
	{
		return ;
	}
	this->data[this->size - 1] = NULL;
	this->size--;
}

//���ջ
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

//��������
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