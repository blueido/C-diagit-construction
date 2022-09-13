#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define max_size 1024

class seqStack
{
public:
	//���캯��
	seqStack();

	//��ջ����
	void push_stack(void* data);

	//����ջ��Ԫ��
	void* front();

	//��ջ����
	void pop_stack();

	//���ջ
	void clear();

	//��������
	~seqStack();

	void* data[max_size];
	int size;

};