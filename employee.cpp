#include "employee.h"
#include <fstream>

employee ::employee(int m_id, string m_name, string m_sexy, int m_age)
{
	//cout << "������ְ��ID��";
	this->id = m_id;
	//cout << "������ְ��������";
	this->name = m_name;
	//cout << "������ְ���Ա�";
	this->sexy = m_sexy;
	//cout << "������ְ����ͣ�";
	this->age = m_age;
	occupation = getOccupation();

	//fstream file1;
	//file1.open("ְ����Ϣ.txt", ios::app);
	//file1<<worker1
}

void employee::ShowInfo()
{
	cout << "ְ��ID��" << this->id << " "
		<< "\tְ������: " << this->name << " "
		<< "\tְ���Ա�: " << this->sexy << " "
		<< "\tְ�����: " << this->age << " "
		<< "\tְ����λ: " << getOccupation() << endl;
}

string employee::getOccupation()
{
	return string("Ա��");
}

employee::~employee()
{

}