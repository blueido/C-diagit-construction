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

//����ָ�붨��
typedef void (*PRINTNODE)(linknode*);
typedef int (*compare)(linknode* , linknode* );

class companylist
{
public:
	//���캯��
	companylist();

	//���뺯��
	void insert(int pos, linknode* data);

	//ɾ������
	void era(int pos);

	//��ʾ����
	void show(PRINTNODE myprint);

	//���Һ���
	int findIt(linknode* data);
	int findIt(linknode* data, compare myCompare);

	//��������
	~companylist();

	linknode* head;
	int size;
};