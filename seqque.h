#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define max_size 1024

class seqque
{
public:
	//���캯��
	seqque();

	//���
	void push(void* data);

	//���ض�ͷԪ��
	void* front();

	//���ض�βԪ��
	void* back();

	//���
	void clear();

	//����
	void pop();

	//��������
	~seqque();

	void* data[max_size];
	int size;
};