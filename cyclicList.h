#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class cyclicnode
{
public:
	void* data;
	cyclicnode* pnext;
};

typedef void (*print) (void*);

class cyclicList
{
public:
	//构造函数
	cyclicList();

	//插入函数
	void insert(int pos, void* data);

	//删除函数
	void era(int pos);    //根据位置删除
	void era(void* data); //根据值删除

	//查找函数
	int findIt(void* data);

	//显示函数
	void show(print myPrint);
	
	//析构函数
	~cyclicList();

	cyclicnode* headnode;
	int size;
};