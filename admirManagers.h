#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "personManager.h"
#include "students.h"
#include "teachers.h"
#include "computerRoom.h"

class admirManagers :public personManager
{
public:
	//Ĭ�Ϲ��캯��
	admirManagers();

	//���ع��캯��
	admirManagers(string name, int id, double password);

	//��¼����
	void load();

	//�˵�����
	void subMenu();

	//����˻�
	void addAccount();

	//��ʼ����������
	void initvector();

	//���غ���
	void checkRepeat(int& id);

	//�鿴�˻�
	void checkAccount();

	//��ʾ����
	void show(int s_or_t);

	//���Һ���
	void findsort(int s_or_t);

	//�˳�
	int exitcheck(int& flag1);

	//���»���״̬
	void statusUpdate();

	//�鿴����
	void checkRoom();

	//���ԤԼ
	void clearApply();

	//ע����¼
	int exitAdm();

	//��������
	~admirManagers();

	int m_id;
	int flag;
	int type;

	vector<students> vst;
	vector<teachers> vte;
	vector<computerRoom> vcr;
};