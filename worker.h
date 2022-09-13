#pragma once
#include <iostream>
#include <string>

using namespace std;

class worker
{
public:
	int age;
	int id;
	string name;
	string sexy;
	string occupation;
	
	//显示个人信息
	virtual void ShowInfo() = 0;
	//获取岗位名称
	virtual string getOccupation() = 0;
};