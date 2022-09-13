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
	//���캯��
	cyclicList();

	//���뺯��
	void insert(int pos, void* data);

	//ɾ������
	void era(int pos);    //����λ��ɾ��
	void era(void* data); //����ֵɾ��

	//���Һ���
	int findIt(void* data);

	//��ʾ����
	void show(print myPrint);
	
	//��������
	~cyclicList();

	cyclicnode* headnode;
	int size;
};