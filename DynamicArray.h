#pragma once
#include <iostream>
#include <string>

using namespace std;


class dynamicArray
{
public:

	//构造函数
	dynamicArray();
	dynamicArray(int capacity);

	//插入Push_Back
	void push_back(int value);

	//删除erase
	void era_pos(int pos);  //按位置删除
	void era_value(int value);  //按值删除

	//查找
	int findIt(int value);

	//清空
	void clearIt();

	//显示
	void show();

	//获取容量
	int get_capacity();

	//获取元素数量
	int get_size();

	//析构函数
	~dynamicArray();

	int m_capacity; //当前数组最大容纳的元素个数
	int m_size;     //当前数组中存放的数据个数
	int* m_pArray;  //存放数据的地址
};