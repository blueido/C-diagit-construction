#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "player1.h"
#include <algorithm>
#include <map>
#include <deque>
#include <numeric>
#include <time.h>
#include <Windows.h>

using namespace std;

class playerManager
{
public:

	//���캯��
	playerManager();

	//��ʾ�˵�
	void showMenu();
	
	//�˳�ϵͳ
	void exitSystem();

	//����ѡ��
	void createPlayer1(vector<player1>& py);

	//��ʾѡ����Ϣ
	void show_player1(vector<player1>& py);

	//��ʼ�ݽ�����
	void startSpeech();

	//��ί���
	void createGrade(player1& p);
	void giveGrade();

	//����
	void speech();

	//����ѡ����Ϣ
	void savePlayer();

	//�鿴������Ϣ
	void findInfo();

	//��ձ�������
	void clearRecord();

	//��������
	~playerManager();

	vector<player1> py1;  //��ŵ�һ���е�ѡ��
	vector<player1> py2;  //��Ž����ڶ��ֵ�ѡ��
	vector<player1> py3;  //��ŵڶ��ֻ�ʤ��ǰ����ѡ����Ϣ
	int num_player1;
	int num_pingwei1;
	int index;  //������ǰ�ִ�
};