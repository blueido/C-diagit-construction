#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include "globalFile.h"

using namespace std;

class OrderFile
{
public:
	//���캯��
	OrderFile();
	
	//����ԤԼ��¼
	void updateOrder();

	//��¼ԤԼ����
	int m_size;

	//��¼����ԤԼ��Ϣ������   key��¼����   value �����¼��ֵ����Ϣ
	vector<string> vs;
	map<int, vector<string>> m_order;
};