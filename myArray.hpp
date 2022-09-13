#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T>
class myArray
{
public:
	//构造函数
	myArray(T m_capacity)
	{
		this->m_capacity = m_capacity;
		this->m_size = 0;
		this->m_apointer = new T[this->m_capacity];
		//cout << "构造函数" << endl;
	}

	//拷贝函数
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
		//cout << "拷贝函数" << endl;
	}

	//重写=号，operator=
	T& operator=(myArray& arr)
	{
		//先判断内存空间是否已经释放
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
		//cout << "深拷贝构造" << endl;
		return *this;
	}

	//尾增法，给数组添加数据
	void array_Add(const T & value)
	{
		if (this->m_size == this->m_capacity)
		{
			cout << "容量不足" << endl;
			return;
		}
		else
		{
			this->m_apointer[this->m_size] = value;
			this->m_size++;  //更新数组中的元素个数
		}
	}

	//尾删法
	void array_delet()
	{
		if (this->m_size == 0)
		{
			cout << "数组为空" << endl;
			return;
		}
		else
		{ 
			delete this->m_apointer[this->m_size];
			this->m_size--;  //更新数组中的元素个数
		}
	}

	//重载[],通过下标访问数组元素
	T& operator[] (const int index)
	{
		return this->m_apointer[index];
	}

	//获取数组容量
	int getCpacity()
	{
		return this->m_capacity;
	}
	//获取数组元素个数
	int getSize()
	{
		return this->m_size;
	}

	//析构函数
	~myArray()
	{
		if (this->m_apointer != NULL)
		{
			delete[] this->m_apointer;
			this->m_apointer = NULL;
		}
		//cout << "析构函数" << endl;
	}

private:
	//数组容量
	T m_capacity;
	//数组指针，指向堆区开辟的数组空间
	T* m_apointer;
	//数组元素数
	T m_size;
};