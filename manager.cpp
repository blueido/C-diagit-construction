#include "manager.h"


using namespace std;

//���캯��
Manager::Manager(int m_id, string m_name, string m_sexy, int m_age)
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
}
//��ʾ������Ϣ
void Manager::ShowInfo()
{
	cout << "ְ��ID��" << this->id << " "
		<< "\tְ������: " << this->name << " "
		<< "\tְ���Ա�: " << this->sexy << " "
		<< "\tְ�����: " << this->age << " "
		<< "\tְ����λ: " << getOccupation() << endl;
}
//��ȡ��λ����
string Manager::getOccupation()
{
	return string("����");
}
//��������
Manager::~Manager()
{

}