#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "personManager.h"
#include "globalFile.h"
#include "OrderFile.h"


class teachers:public personManager
{
public:
	//Ĭ�Ϲ���
	teachers();

	//���ع���
	teachers(string name, int id, double password);

	//��¼����
	void load();

	//�˵�����
	void subMenu();

	//�鿴ԤԼ
	void checkApply();

	//���ԤԼ
	void auditApply();

	//ע����¼
	int exitTeh();

	//��������
	~teachers();

	int m_id;
	int flag;
};