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
	//默认构造
	teachers();

	//重载构造
	teachers(string name, int id, double password);

	//登录函数
	void load();

	//菜单界面
	void subMenu();

	//查看预约
	void checkApply();

	//审核预约
	void auditApply();

	//注销登录
	int exitTeh();

	//析构函数
	~teachers();

	int m_id;
	int flag;
};