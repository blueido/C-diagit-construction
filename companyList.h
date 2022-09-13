#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class linknode
{
public:
	linknode* pnext;
};

//函数指针定义
typedef void (*PRINTNODE)(linknode*);
typedef int (*compare)(linknode* , linknode* );

class companylist
{
public:
	//构造函数
	companylist();

	//插入函数
	void insert(int pos, linknode* data);

	//删除函数
	void era(int pos);

	//显示函数
	void show(PRINTNODE myprint);

	//查找函数
	int findIt(linknode* data);
	int findIt(linknode* data, compare myCompare);

	//析构函数
	~companylist();

	linknode* head;
	int size;
};