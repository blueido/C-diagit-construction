#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "globalFile.h"
#include "computerRoom.h"

using namespace std;

//������
class Apply
{
public:
	Apply()
	{

	}
	Apply(string time, string timePeriod, int room)
	{
		this->m_time = time;
		this->m_timePeriod = timePeriod;
		this->m_room = room;
	}
	string m_time;        //��һ~����
	string m_timePeriod;  //���������
	int m_room;           //������1~3
};

class personManager
{
public:
	virtual void load() = 0;

	void save();

	void statusUpdate();

	string m_name;
	double m_password;
	
	vector<Apply> va;
};

