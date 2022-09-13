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
	//默认构造函数
	admirManagers();

	//重载构造函数
	admirManagers(string name, int id, double password);

	//登录函数
	void load();

	//菜单界面
	void subMenu();

	//添加账户
	void addAccount();

	//初始化容器函数
	void initvector();

	//查重函数
	void checkRepeat(int& id);

	//查看账户
	void checkAccount();

	//显示函数
	void show(int s_or_t);

	//查找函数
	void findsort(int s_or_t);

	//退出
	int exitcheck(int& flag1);

	//更新机房状态
	void statusUpdate();

	//查看机房
	void checkRoom();

	//清空预约
	void clearApply();

	//注销登录
	int exitAdm();

	//析构函数
	~admirManagers();

	int m_id;
	int flag;
	int type;

	vector<students> vst;
	vector<teachers> vte;
	vector<computerRoom> vcr;
};