#include "companyList.h"

//���캯��
companylist::companylist()
{
	//�����ڴ�
	this->head = new linknode[sizeof(linknode)];
	//��ʼ��
	this->head->pnext = NULL;
	this->size = 0;
}

//���뺯��
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

	//���Ҳ���λ��
	linknode* current_node = this->head;
	for (int i = 0; i < pos; i++)
	{
		current_node = current_node->pnext;
	}

	//�����½ڵ�
	data->pnext = current_node->pnext;
	current_node->pnext = data;

	this->size++;
}

//ɾ������
void companylist::era(int pos)
{
	if (pos<0 || pos>this->size)
	{
		return;
	}
	//����ָ�����
	linknode* current_node = this->head;
	for (int i = 0; i < pos; i++)
	{
		current_node = current_node->pnext;
	}

	//ɾ�����
	current_node->pnext = current_node->pnext->pnext;

	this->size--;
}

//��ʾ����
void companylist::show(PRINTNODE myprint)
{
	//����ָ��
	linknode* current_node = this->head->pnext;
	for (int i = 0; i < this->size; i++)
	{
		myprint(current_node);
		current_node = current_node->pnext;
	}
}

//���Һ���
int companylist::findIt(linknode* data)
{
	int pos = -1;
	if (data == NULL)
	{
		return -1;
	}
	//����ָ��
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
	//����ָ��
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

//��������
companylist::~companylist()
{
	if (this->head != NULL)
	{
		delete[] this->head;
		this->head = NULL;
	}
	this->size = 0;
}