#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class computerRoom
{
public:
	//Ĭ�Ϲ���
	computerRoom();
	//�вι���
	computerRoom(int id, int number, int rest);
	//��������
	~computerRoom();

	int m_id;
	int m_number;
	int m_rest;
};