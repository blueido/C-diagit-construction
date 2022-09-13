#pragma once
#include <iostream>
#include <string>
#include <fstream>

//template <class T>
class listNode
{
public:
	//T data;
	//void* ��ʾһ��������ָ�룬����ָ���κ����ͣ������ģ����һ���Ĺ���
	void* data;   //��ֵ��
	listNode* pnode;   //ָ����
};

//����ָ�룬������Ϊ�����������β�
typedef void (*PRINTLISTNODE) (void*);

class linkList
{
public:
	//���캯��
	linkList();

	//���Һ���
	int findIt(void* data);

	//���뺯��
	void insert(int pos, void* data);

	//ɾ������
	void era(int pos);

	//��ʾ����
	void show(PRINTLISTNODE print);

	//��������
	~linkList();

	listNode* headnode;  //��һ��ͷ���
	int size;     //����Ԫ�ظ���

	//ע��������Ҫ������������Ϊ�������������һ���Ͳ���һ����û�������ĸ���
};