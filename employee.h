#pragma once
#include <iostream>
#include "worker.h"

using namespace std;

class employee :public worker
{
public:
	//���캯��
	employee(int m_id, string m_name, string m_sexy, int m_age);
	//��ʾ������Ϣ
	virtual void ShowInfo();
	//��ȡ��λ����
	virtual string getOccupation();
	//��������
	~employee();
};
