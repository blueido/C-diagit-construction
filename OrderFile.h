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
	//构造函数
	OrderFile();
	
	//更新预约记录
	void updateOrder();

	//记录预约条数
	int m_size;

	//记录所有预约信息的容器   key记录条数   value 具体记录键值对信息
	vector<string> vs;
	map<int, vector<string>> m_order;
};