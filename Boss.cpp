#include "Boss.h"


using namespace std;

//���캯��
Boss::Boss(int m_id, string m_name, string m_sexy, int m_age)
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
void Boss::ShowInfo()
{
	cout << "ְ��ID��" << this->id << " "
		<< "\tְ������: " << this->name << " "
		<< "\tְ���Ա�: " << this->sexy << " "
		<< "\tְ�����: " << this->age << " "
		<< "\tְ����λ: " << getOccupation() << endl;
}
//��ȡ��λ����
string Boss::getOccupation()
{
	return string("�ܲ�");
}
//��������
Boss::~Boss()
{

}