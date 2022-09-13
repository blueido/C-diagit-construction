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
	//默认构造函数
	students();

	//重载构造函数
	students(string name, int id, double password);

	//登录函数
	void load();

	//菜单界面
	void subMenu();

	//申请预约
	void getApply();

	//保存函数
	void save();

	//查看预约
	void inquireApply();

	//取消预约
	void cancelApply();

	//退出登录
	int exitStd();

	//更新机房状态
	void statusUpdate(int room_num);
	void restUpdate();

	//默认析构函数
	~students();

	int m_id;
	int flag;
	int rest;
	string status;
};