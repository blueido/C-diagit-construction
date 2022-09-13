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

	//构造函数
	playerManager();

	//显示菜单
	void showMenu();
	
	//退出系统
	void exitSystem();

	//创建选手
	void createPlayer1(vector<player1>& py);

	//显示选手信息
	void show_player1(vector<player1>& py);

	//开始演讲比赛
	void startSpeech();

	//评委打分
	void createGrade(player1& p);
	void giveGrade();

	//比赛
	void speech();

	//保存选手信息
	void savePlayer();

	//查看往届信息
	void findInfo();

	//清空比赛数据
	void clearRecord();

	//析构函数
	~playerManager();

	vector<player1> py1;  //存放第一轮中的选手
	vector<player1> py2;  //存放晋级第二轮的选手
	vector<player1> py3;  //存放第二轮获胜的前三名选手信息
	int num_player1;
	int num_pingwei1;
	int index;  //比赛当前轮次
};