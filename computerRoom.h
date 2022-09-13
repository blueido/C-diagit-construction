#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class computerRoom
{
public:
	//默认构造
	computerRoom();
	//有参构造
	computerRoom(int id, int number, int rest);
	//析构函数
	~computerRoom();

	int m_id;
	int m_number;
	int m_rest;
};