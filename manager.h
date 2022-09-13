#pragma once
#include <iostream>
#include "worker.h"

using namespace std;

class Manager:public worker
{
public:
	//构造函数
	Manager(int m_id, string m_name, string m_sexy, int m_age);
	//显示个人信息
	virtual void ShowInfo();
	//获取岗位名称
	virtual string getOccupation();
	//析构函数
	~Manager();
};