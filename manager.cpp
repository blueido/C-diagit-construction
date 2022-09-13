#include "manager.h"


using namespace std;

//构造函数
Manager::Manager(int m_id, string m_name, string m_sexy, int m_age)
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
}
//显示个人信息
void Manager::ShowInfo()
{
	cout << "职工ID：" << this->id << " "
		<< "\t职工姓名: " << this->name << " "
		<< "\t职工性别: " << this->sexy << " "
		<< "\t职工年纪: " << this->age << " "
		<< "\t职工岗位: " << getOccupation() << endl;
}
//获取岗位名称
string Manager::getOccupation()
{
	return string("经理");
}
//析构函数
Manager::~Manager()
{

}