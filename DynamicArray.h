#pragma once
#include <iostream>
#include <string>

using namespace std;


class dynamicArray
{
public:

	//���캯��
	dynamicArray();
	dynamicArray(int capacity);

	//����Push_Back
	void push_back(int value);

	//ɾ��erase
	void era_pos(int pos);  //��λ��ɾ��
	void era_value(int value);  //��ֵɾ��

	//����
	int findIt(int value);

	//���
	void clearIt();

	//��ʾ
	void show();

	//��ȡ����
	int get_capacity();

	//��ȡԪ������
	int get_size();

	//��������
	~dynamicArray();

	int m_capacity; //��ǰ����������ɵ�Ԫ�ظ���
	int m_size;     //��ǰ�����д�ŵ����ݸ���
	int* m_pArray;  //������ݵĵ�ַ
};