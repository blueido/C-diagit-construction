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
	
	//��ʾ������Ϣ
	virtual void ShowInfo() = 0;
	//��ȡ��λ����
	virtual string getOccupation() = 0;
};