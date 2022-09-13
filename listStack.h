#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class listStackNode
{
public:
	listStackNode* pnext;
};

class listStack
{
public:
	//���캯��
	listStack();

	//��ջ
	void push(listStackNode* data);

	//��ջ
	void pop();

	//����ջ��Ԫ��
	listStackNode* front();

	//���ջ
	void clear();

	//��������
	~listStack();

	listStackNode* head;
	int size;
};