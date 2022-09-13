#include "teachers.h"

using namespace std;


//默认构造
teachers::teachers()
{

}

//重载构造
teachers::teachers(string name, int id, double password)
{
	this->m_name = name;
	this->m_id = id;
	this->m_password = password;
}

//登录函数
void teachers::load()
{
	flag = 1;
	int num = 0;
	int time = 0;
	int id;
	string name;
	double password;
	int fid;
	string fname;
	double fpassword;
	string data;

	cout << "欢迎登录教师系统！" << endl;
	while (true)
	{
		ifstream ifs;
		ifs.open(STUDENTS_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "文件不存在!" << endl;
			ifs.close();
			return;
		}

		//身份验证
		if (time == 0)
		{
			cout << "请输入账号密码！" << endl;
			cout << "学号: ";
			cin >> id;
			cout << "姓名: ";
			cin >> name;
			cout << "密码: ";
			cin >> password;
		}
		if (num == 0 && time > 0)
		{
			cout << "账户与密码输入错误！" << endl;
			cout << "请重新输入账号密码！" << endl;
			cout << "学号: ";
			cin >> id;
			cout << "姓名: ";
			cin >> name;
			cout << "密码: ";
			cin >> password;
		}
		while (ifs >> fid && ifs >> fname && ifs >> fpassword) //从文件中读取信息
		{
			if ((id == fid) && (name == fname) && (password == fpassword))  //读取的信息与输入信息对比
			{
				num++;
				this->m_id = id;
				this->m_name = name;
				this->m_password = password;
				system("cls");
				while (flag)
				{
					this->subMenu();
				}
				return;
			}
		}
		time++;
		ifs.close();
	}
}

void teachers::subMenu()
{
	cout << "欢迎使用教师系统!" << endl;
	cout << "-------------------------" << endl;
	cout << "****** 1、查看预约 ******" << endl;
	cout << "****** 2、审核预约 ******" << endl;
	cout << "****** 3、退出系统 ******" << endl;

	cout << "请选择你想使用的功能: " << endl;

	int teh_choice;
	cin >> teh_choice;
	switch (teh_choice)
	{
	case 1: checkApply(); break;
	case 2: auditApply(); break;
	case 3: exitTeh(); break;
	default:
		break;
	}
}

//查看预约
void teachers::checkApply()
{
	OrderFile of;
	if (of.m_order.size() == 0)
	{
		cout << "预约记录为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = of.m_order.begin(); it != of.m_order.end(); it++)
		{
			for (vector<string>::iterator vis = (it->second).begin(); vis != (it->second).end(); vis++)
			{
				if (vis == ((it->second).end() - 1))
				{
					if (*vis == "0")
					{
						cout << "审核不通过" << " ";
					}
					else if (*vis == "1")
					{
						cout << "审核中" << " ";
					}
					else if (*vis == "2")
					{
						cout << "审核通过" << " ";
					}
				}
				else 
				{
					cout << *vis << " ";
				}
				
			}
			cout << endl;
		}
	}
	system("pause");
	system("cls");
}

//审核预约
void teachers::auditApply()
{
	OrderFile of;
	vector<int> v;
	if (of.m_order.size() == 0)
	{
		cout << "预约为空！" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "待审核的申请预约记录如下：" << endl;
	int i = 1;
	int num = 0;
	int index = 1;
	for (map<int, vector<string>>::iterator it = of.m_order.begin(); it != of.m_order.end(); it++)
	{
		if (*(it->second.end() - 1) == "1")
		{
			v.push_back(i);
			cout << index++ << "、 ";
			cout << "预约日期：" << *(it->second.begin()) << " ";
			cout << "时间段：" << *((it->second.begin()) + 1) << " ";
			cout << "机房编号：" << *((it->second.begin()) + 4) << " ";
			string status;
			if (*((it->second.end()) - 1) == "1")
			{
				status = "审核中";
			}
			cout << status << endl;
			num++;
		}
		i++;
	}

	if (num == 0)
	{
		cout << "无待审核的申请！" << endl;
	}
	else
	{
		int choice;
		int result;
		cout << "请输入进行审核的申请序号，0 退出" << endl;
		while (true)
		{
			cin >> choice;
			if (choice >= 0 && choice <= v.size())
			{
				if (choice == 1)
				{
					cout << "  请输入审核结果 " << endl;
					cout << "1--通过，2--不通过" << endl;
					cin >> result;
					if (result == 1)
					{
						int c = v[choice - 1];
						vector<string>::iterator it = of.m_order[c].begin();
						*(it + 6) = "2"; //status=2,即通过
					}
					if (result == 2)
					{
						int c = v[choice - 1];
						vector<string>::iterator it = of.m_order[c].begin();
						*(it + 6) = "0"; //status=0,即不通过
					}
					//更新 APPLY_FILE 文件
					of.updateOrder();
					break;
				}
				else if (choice == 0)
				{
					break;
				}
			}
			
			cout << "输入错误！请重新输入:" << endl;
			
		}
	}
	//清空临时容器
	v.clear();

	system("pause");
	system("cls");
}

//注销登录
int teachers::exitTeh()
{
	cout << "谢谢使用！" << endl;
	system("pause");
	system("cls");
	return flag = 0;
}

//析构函数
teachers::~teachers()
{

}