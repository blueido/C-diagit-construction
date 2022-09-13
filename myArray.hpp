#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T>
class myArray
{
public:
	//���캯��
	myArray(T m_capacity)
	{
		this->m_capacity = m_capacity;
		this->m_size = 0;
		this->m_apointer = new T[this->m_capacity];
		//cout << "���캯��" << endl;
	}

	//��������
	myArray(myArray &arr)
	{
		if (this->m_apointer != NULL)
		{
			delete[] this->m_apointer;
			this->m_apointer = NULL;
		}

		this->m_capacity = arr.m_capacity;
		this->m_size = arr.m_size;
		this->m_apointer = new T[arr.m_capacity];

		for (int i = 0; i < this->m_size; i++)
		{
			this->m_apointer[i] = arr.m_apointer[i];
		}
		//cout << "��������" << endl;
	}

	//��д=�ţ�operator=
	T& operator=(myArray& arr)
	{
		//���ж��ڴ�ռ��Ƿ��Ѿ��ͷ�
		if (this->m_apointer != NULL)
		{
			delete[] this->m_apointer;
			this->m_apointer = NULL;
			this->m_capacity = 0;
			this->m_size = 0;
		}

		this->m_capacity = arr.m_capacity;
		this->m_size = arr.m_size;
		this->m_apointer = new T[arr.m_capacity];

		for (int i = 0; i < this->m_size; i++)
		{
			this->m_apointer[i] = arr.m_apointer[i];
		}
		//cout << "�������" << endl;
		return *this;
	}

	//β�������������������
	void array_Add(const T & value)
	{
		if (this->m_size == this->m_capacity)
		{
			cout << "��������" << endl;
			return;
		}
		else
		{
			this->m_apointer[this->m_size] = value;
			this->m_size++;  //���������е�Ԫ�ظ���
		}
	}

	//βɾ��
	void array_delet()
	{
		if (this->m_size == 0)
		{
			cout << "����Ϊ��" << endl;
			return;
		}
		else
		{ 
			delete this->m_apointer[this->m_size];
			this->m_size--;  //���������е�Ԫ�ظ���
		}
	}

	//����[],ͨ���±��������Ԫ��
	T& operator[] (const int index)
	{
		return this->m_apointer[index];
	}

	//��ȡ��������
	int getCpacity()
	{
		return this->m_capacity;
	}
	//��ȡ����Ԫ�ظ���
	int getSize()
	{
		return this->m_size;
	}

	//��������
	~myArray()
	{
		if (this->m_apointer != NULL)
		{
			delete[] this->m_apointer;
			this->m_apointer = NULL;
		}
		//cout << "��������" << endl;
	}

private:
	//��������
	T m_capacity;
	//����ָ�룬ָ��������ٵ�����ռ�
	T* m_apointer;
	//����Ԫ����
	T m_size;
};