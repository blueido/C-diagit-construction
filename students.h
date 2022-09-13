#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "personManager.h"
#include "globalFile.h"
#include "computerRoom.h"
#include "OrderFile.h"


class students :public personManager
{
public:
	//Ĭ�Ϲ��캯��
	students();

	//���ع��캯��
	students(string name, int id, double password);

	//��¼����
	void load();

	//�˵�����
	void subMenu();

	//����ԤԼ
	void getApply();

	//���溯��
	void save();

	//�鿴ԤԼ
	void inquireApply();

	//ȡ��ԤԼ
	void cancelApply();

	//�˳���¼
	int exitStd();

	//���»���״̬
	void statusUpdate(int room_num);
	void restUpdate();

	//Ĭ����������
	~students();

	int m_id;
	int flag;
	int rest;
	string status;
};