#include "seqque.h"

//���캯��
seqque::seqque()
{
	for (int i = 0; i < max_size; i++)
	{
		this->data[i] = NULL;
	}
	this->size = 0;
}

//���
void seqque::push(void* data)
{
	if (data == NULL)
	{
		return;
	}
	//�����������ͷ
	this->data[this->size] = data;
	//�����ұ�����ͷ
	//this->data[max_size - 1 - this->size] = data;

	//����Ԫ����������
	this->size++;
}

//���ض�ͷԪ��
void* seqque::front()
{
	if (this->size == 0)
	{
		return NULL;
	}
	return this->data[0];
}

//���ض�βԪ��
void* seqque::back()
{
	if (this->size == 0)
	{
		return NULL;
	}
	return this->data[this->size - 1];
}

//���
void seqque::clear()
{
	for (int i = 0; i < this->size; i++)
	{
		this->data[i] = NULL;
	}
	this->size = 0;
}

//����,�������Ƚ��ȳ�
void seqque::pop()
{
	if (this->size == 0)
	{
		return;
	}
	for (int i = 0; i < this->size - 1; i++)
	{
		//�������Ƚ��ȳ������ÿ�ε�����Ӧ���Ƕ�ͷԪ��
		this->data[i] = this->data[i + 1];
	}
	this->size--;
}

//��������
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