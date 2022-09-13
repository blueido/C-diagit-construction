#pragma once   //防止头文件重复包含
#include <iostream>
#include <string>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "Boss.h"

#define FILENAME "职工信息.txt"

using namespace std;

class WorkerManager
{
public:
	//构造函数
	WorkerManager();

	//菜单界面
	void ShowmMenu();

	//退出系统
	void ExitSystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	worker** m_EmpArray;

	//增加职工信息
	void AddWorker();

	//检查是否存在重复ID
	bool CheckID(int m_id);

	//保存信息，将员工信息保存到文本文件中
	void save();

	//判断文件是否为空 标志,false表示文件不为空，true表示文件为空
	bool m_FileIsEmpty;

	//检查文件是否为空
	bool checkFileIsEmpty();

	//统计文件中职工人数
	int getEmpNum();

	//初始化全新文件中的职工数组
	void init_EmpArray();

	//显示职工信息
	void ShowWorkers();

	//删除离职职工
	void DeleteWorker();

	//判断职工是否存在，如果存在则返回职工在数组中的位置，否则返回-1；
	int check(int m_id);
	bool check(string m_name);

	//修改职工信息
	void ModifyWorker();

	//查找职工信息
	void SearchWorker();

	//按照职工ID排序
	void SortWorker();

	//清除所有数据
	void CleanAllWorker();

	//析构函数
	~WorkerManager();
};
