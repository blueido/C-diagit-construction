#pragma once
#include <iostream>
#include <string>
#include <fstream>

//template <class T>
class listNode
{
public:
	//T data;
	//void* 表示一个无类型指针，可以指向任何类型，这个和模板是一样的功能
	void* data;   //数值域
	listNode* pnode;   //指针域
};

//函数指针，用于作为其他函数的形参
typedef void (*PRINTLISTNODE) (void*);

class linkList
{
public:
	//构造函数
	linkList();

	//查找函数
	int findIt(void* data);

	//插入函数
	void insert(int pos, void* data);

	//删除函数
	void era(int pos);

	//显示函数
	void show(PRINTLISTNODE print);

	//析构函数
	~linkList();

	listNode* headnode;  //第一个头结点
	int size;     //链表元素个数

	//注意链表不需要容量，这是因为链表的数据是有一个就插入一个，没有容量的概念
};