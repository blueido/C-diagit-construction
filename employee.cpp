#include "employee.h"
#include <fstream>

employee ::employee(int m_id, string m_name, string m_sexy, int m_age)
{
	//cout << "请输入职工ID：";
	this->id = m_id;
	//cout << "请输入职工姓名：";
	this->name = m_name;
	//cout << "请输入职工性别：";
	this->sexy = m_sexy;
	//cout << "请输入职工年纪：";
	this->age = m_age;
	occupation = getOccupation();

	//fstream file1;
	//file1.open("职工信息.txt", ios::app);
	//file1<<worker1
}

void employee::ShowInfo()
{
	cout << "职工ID：" << this->id << " "
		<< "\t职工姓名: " << this->name << " "
		<< "\t职工性别: " << this->sexy << " "
		<< "\t职工年纪: " << this->age << " "
		<< "\t职工岗位: " << getOccupation() << endl;
}

string employee::getOccupation()
{
	return string("员工");
}

employee::~employee()
{

}