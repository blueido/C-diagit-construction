#include "DynamicArray.h"

//��̬�����ڴ棬���� ��������ݵ��ڴ���ڶ���
//����Ҫ��չ�ڴ�ʱ��1�������¿ռ䣬2���������ݣ�3���ͷž��ڴ�
//����������Ҫ���� ����capacity����ǰ���������size

//���캯��
dynamicArray::dynamicArray()
{
	this->m_capacity = 1;
	this->m_pArray = NULL;
	this->m_size = 0;
}

dynamicArray::dynamicArray(int capacity)
{
	this->m_capacity = capacity;
	this->m_size = 0;
	//Ϊ������ռ��ʱ��������malloc�������ٲ��ҹ�������new ��������Ŀռ俪�ٵķ���
	//this->m_pArray = (int*)malloc(sizeof(int) * this->m_capacity);   //����malloc
	this->m_pArray = new int[sizeof(int) * this->m_capacity];          //����new
}

//����Push_Back
void dynamicArray::push_back(int value)
{
	if (this->m_pArray == NULL)
	{
		return;
	}

	//�жϿռ��ڴ��Ƿ��㹻
	if (this->m_size == this->m_capacity)
	{
		//1�������¿ռ�
		//int* newspace = (int*)malloc(sizeof(int) * this->m_capacity * 2);   //����malloc
		int* newspace = new int[sizeof(int) * this->m_capacity * 2];          //����new 
		//2����������
		memcpy(newspace, this->m_pArray, sizeof(int) * this->m_capacity);
		//3���ͷžɿռ�
		delete this->m_pArray;

		//��������
		this->m_capacity = this->m_capacity * 2;
		this->m_pArray = newspace;
	}

	//������Ԫ��
	this->m_pArray[this->m_size] = value;
	this->m_size++;

}

//ɾ��erase
void dynamicArray::era_pos(int pos)  //��λ��ɾ��������ǰ�Ʒ�ɾ��
{
	//�����Ѿ�Ϊ��
	if (this->m_pArray == NULL)
	{
		return;
	}

	if (pos > 0 && pos <= this->m_size)
	{
		for (int i = pos; i < this->m_size; i++)
		{
			this->m_pArray[i - 1] = this->m_pArray[i];  //ǰ�Ʒ�
		}
		this->m_size--;
	}
	else
	{
		return;
	}
}

void dynamicArray::era_value(int value)  //��ֵɾ��
{
	//�����Ѿ�Ϊ��
	if (this->m_pArray == NULL)
	{
		return;
	}

	int pos = -1;
	//ͨ��findIt����������valueֵ��λ��
	pos = this->findIt(value);
	if (pos == -1)
	{
		return;
	}
	else
	{
		//���ð�λ��ɾ��������ɾ��value
		this->era_pos(pos);
	}
}

//����
int dynamicArray::findIt(int value)
{
	//�����Ѿ�Ϊ��
	if (this->m_pArray == NULL)
	{
		return -1;
	}
	int pos = -1;
	for (int i = 0; i < this->m_size; i++)
	{
		if (this->m_pArray[i] == value)
		{
			//�ҵ��󣬽�value��λ�ü�¼
			pos = i + 1;
			break;
		}
	}
	return pos;
}


//���
void dynamicArray::clearIt()
{
	if (this->m_pArray == NULL)
	{
		return;
	}
	this->m_size = 0;
}

//��ʾ
void dynamicArray::show()
{
	if (this->m_pArray == NULL)
	{
		return;
	}
	for (int i = 0; i < this->m_size; i++)
	{
		cout << this->m_pArray[i] << " ";
	}
	cout << endl;
}

//��ȡ����
int dynamicArray::get_capacity()
{
	if (this->m_pArray == NULL)
	{
		return 0;
	}
	return this->m_capacity;
}

//��ȡԪ������
int dynamicArray::get_size()
{
	if (this->m_pArray == NULL)
	{
		return 0;
	}
	return this->m_size;
}

//��������
dynamicArray::~dynamicArray()
{
	if (this->m_pArray != NULL)
	{
		delete [] this->m_pArray;
		this->m_pArray = NULL;
	}
	this->m_capacity = 0;
	this->m_size = 0;
}
