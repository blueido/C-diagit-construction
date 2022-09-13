#include "students.h"
using namespace std;

students::students()
{

}

students::students(string name, int id, double password)
{
	this->m_name = name;
	this->m_id = id;
	this->m_password = password;
}


void students::load()
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


	cout << "欢迎登录学生系统！" << endl;
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


void students::subMenu()
{
	cout << "欢迎使用学生系统!" << endl;
	cout << "-------------------------" << endl;
	cout << "****** 1、申请预约 ******" << endl;
	cout << "****** 2、查看预约 ******" << endl;
	cout << "****** 3、取消预约 ******" << endl;
	cout << "****** 4、退出系统 ******" << endl;

	cout << "请选择你想使用的功能: " << endl;

	int std_choice;
	cin >> std_choice;
	switch (std_choice)
	{
	case 1: getApply(); break;
	case 2: inquireApply(); break;
	case 3: cancelApply(); break;
	case 4: exitStd(); break;
	default:
		system("cls");
		break;
	}
}




void students::getApply()
{
	int i = 0, j = 0;
	int room;
	string time;
	string timePeriod;

	string time1[7] = { "周一","周二", "周三", "周四", "周五", "周六", "周日" };
	string time2[2] = { "上午","下午" };
	while (true)
	{
		cout << "请选择日期：1、周一；2、周二；...；7、周日" << endl;
		cin >> i;
		if (i >= 0 && i < 8)
		{
			time = time1[i - 1]; break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	while (true)
	{
		cout << "请选择时段：1、上午；2、下午" << endl;
		cin >> j;
		if (j >= 1 && j < 3)
		{
			timePeriod = time2[j - 1]; break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	while (true)
	{
		cout << "请选择机房：1、2、3" << endl;
		cin >> room;
		if (room >= 1 && room < 4)
		{
			 break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	Apply ap(time, timePeriod, room);

	//将信息填入容器中
	statusUpdate(room);
	if (rest > 0)
	{
		this->va.push_back(ap);
		status = "1";
		cout << "预约成功，等待审核！";
	}
	else
	{
		status = "0";
		cout << "预约失败！";
		cout << "机房" << room << "无剩余！" << endl;
	}

	//保存信息
	this->save();

	system("pause");
	system("cls");
}

void students::save()
{
	ofstream ofile1;
	ofile1.open(APPLY_FILE, ios::out | ios::app);
	for (vector<Apply>::iterator it = va.begin(); it != va.end(); it++)
	{
		ofile1 << (*it).m_time << "," << (*it).m_timePeriod << "," << this->m_id << "," << this->m_name << "," << "机房" << (*it).m_room << "," << rest << "," << status << ",";
	}
	ofile1.close();
	//清空容器，va是一个定义在基类中的容器，是一个公用的临时容器，因此，每次使用完后要清空
	this->va.clear();
	cout << "保存完毕！" << endl;
}

//查询预约函数
void students::inquireApply()
{
	cout << "请选择查询类型:" << endl;
	cout << "1、查询我的预约  2、查询所有预约" << endl;
	int choice;
	cin >> choice;
	int pos = 0;
	int start = 0;
	int count;
	string date;

	if (choice == 1)
	{
		int num = 0;
		string id;
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
			//to_string--将int转换为string类型
			id = to_string(this->m_id);
			for (map<int, vector<string>>::iterator it = of.m_order.begin(); it != of.m_order.end(); it++)
			{
				if (*((it->second.begin()) + 2) == id)
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
						num++;
					}
					cout << endl;
				}
			}
			if (num == 0)
			{
				cout << "未查到你的预约记录！" << endl;
			}
		}
	}
	if(choice == 2)
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
	}

	system("pause");
	system("cls");
}

void students::cancelApply()
{
	int num = 0;
	string id;
	//to_string--将int转换为string类型
	id = to_string(this->m_id);

	OrderFile of;
	if (of.m_order.size() == 0)
	{
		cout << "预约记录为空！" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中或预约成功的记录可以取消，请输入取消的记录！" << endl;
	cout << endl;

	vector<int> v;  //存放orderFile中map容器的下标编号
	int index = 1;
	int i = 1;
	for (map<int, vector<string>>::iterator it = of.m_order.begin(); it != of.m_order.end(); it++)
	{
		//先判断是否为自身学号
		if (*((it->second.begin()) + 2) == id)
		{
			//再判断预约状态
			//"1"表示审核中，"2"表示预约成功
			if ((*((it->second.end()) - 1) == "1") || (*((it->second.end()) - 1) == "2"))
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
				else if (*((it->second.end()) - 1) == "2")
				{
					status = "预约成功";
				}
				cout << status << endl;
			}
			++num;
		}
		++i;
	}
	cout << endl;
	cout << "请输入取消的记录，输入 0 返回！" << endl;
	int choice;
	if (num > 0)
	{
		while (true)
		{
			cin >> choice;

			if (choice >= 0 && choice <= v.size())
			{
				if (choice == 0)
				{
					break;
				}
				else
				{
					int c = v[choice - 1];
					//删除 map 容器中 key值为 c 的对组数据
					of.m_order.erase(c);

					//显示删除后结果
					cout << "剩余全部预约名单如下：" << endl;
					for (map<int, vector<string>>::iterator it = of.m_order.begin(); it != of.m_order.end(); it++)
					{
						for (vector<string>::iterator vis = (it->second).begin(); vis != (it->second).end(); vis++)
						{
							cout << *vis << " ";
						}
						cout << endl;
					}
					//更新 APPLY_FILE 文件
					of.updateOrder();
					cout << "已取消该预约!" << endl;
					break;
				}
			}
			cout << "输入有误，请重新输入！" << endl;
		}
	}
	else
	{
		cout << "您的预约记录已为空！" << endl;
	}
	
	//清空临时容器
	v.clear();

	system("pause");
	system("cls");
}

int students::exitStd()
{
	cout << "谢谢使用！" << endl;
	system("pause");
	system("cls");
	return flag = 0;
}

//更新机房状态
void students::statusUpdate(int room_num)
{
	computerRoom cR1;
	vector<computerRoom> vcr1;
	vcr1.clear();
	int num[3] = { 0, 0, 0 };
	char c;

	restUpdate();

	//将 ROOM_FILE 中的信息读出到vcr1容器中
	ifstream ifs;
	ifs.open(ROOM_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "ROOM_FILE 文件打开失败！" << endl;
		ifs.close();
		return;
	}
	while (ifs >> cR1.m_id && ifs >> cR1.m_number && ifs >> cR1.m_rest)
	{
		vcr1.push_back(cR1);
	}
	ifs.close();

	//将 APPLY_FILE 中的信息读出，并且统计每个机房的预约个数
	ifstream ifs1;
	ifs1.open(APPLY_FILE, ios::in);
	if (!ifs1.is_open())
	{
		cout << "APPLY_FILE 文件打开失败！" << endl;
		ifs1.close();
		return;
	}
	//统计每个机房预约的个数
	string data;
	string room_number;

	int pos = -1;
	int start = 0;
	int count = 0;
	int time = 1;

	//将 APPLY_FILE 中的信息传入 data 中
	ifs1 >> data;

	while (!data.empty())
	{
		pos = data.find(",", start);
		count++;
		if (pos == -1)
		{
			cout << "文件读取完毕！" << endl;
			break;
		}
		if (count == 5 || time == 7)
		{
			room_number = data.substr(start, pos - start);
			if (room_number == "机房1")
			{
				num[0]++;
			}
			else if (room_number == "机房2")
			{
				num[1]++;
			}
			else
			{
				num[2]++;
			}
			time = 0;
		}
		start = pos + 1;
		time++;
	}
	ifs1.close();

	//更新容器vcr1中的机房剩余的大小
	int i = 0;
	for (vector<computerRoom>::iterator it = vcr1.begin(); it != vcr1.end(); it++)
	{
		it->m_rest = it->m_number - num[i];
		i++;
	}
	//将 ROOM_FILE 中的信息清空
	ofstream ofs1;
	ofs1.open(ROOM_FILE, ios::trunc);
	ofs1.close();

	//将容器vcr1中的信息写入 ROOM_FILE 中
	ofstream ofs;
	ofs.open(ROOM_FILE, ios::out | ios::app);
	for (vector<computerRoom>::iterator it = vcr1.begin(); it != vcr1.end(); it++)
	{
		ofs << it->m_id << " " << it->m_number << " " << it->m_rest << endl;
	}
	ofs.close();
	vector<computerRoom>::iterator it = vcr1.begin();
	if (room_num == 1)
	{
		if (it->m_rest > 0)
		{
			rest = (it->m_rest) - 1;
		}
		else
		{
			rest = 0;
		}
	}
	if (room_num == 2)
	{
		if ((it+1)->m_rest > 0)
		{
			rest = ((it + 1)->m_rest) - 1;
		}
		else
		{
			rest = 0;
		}
	}
	if (room_num == 3)
	{
		if ((it + 2)->m_rest > 0)
		{
			rest = ((it + 2)->m_rest) - 1;
		}
		else
		{
			rest = 0;
		}
	}
}


void students::restUpdate()
{
	computerRoom cR1;
	Apply a1;
	students s1;
	vector<computerRoom> vcr1;
	vector<Apply> va1;
	vcr1.clear();
	va1.clear();
	int num[3] = { 0, 0, 0 };
	char c;

	//将 ROOM_FILE 中的信息读出到vcr1容器中
	ifstream ifs;
	ifs.open(ROOM_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "ROOM_FILE 文件打开失败！" << endl;
		ifs.close();
		return;
	}
	while (ifs >> cR1.m_id && ifs >> cR1.m_number && ifs >> cR1.m_rest)
	{
		vcr1.push_back(cR1);
	}
	ifs.close();

	//将 APPLY_FILE 中的信息读出到va1容器中，并且统计每个机房的预约个数
	ifstream ifs1;
	ifs1.open(APPLY_FILE, ios::in);
	if (!ifs1.is_open())
	{
		cout << "APPLY_FILE 文件打开失败！" << endl;
		ifs1.close();
		return;
	}
	//统计每个机房预约的个数
	string data;
	string room_number;
	ifs1 >> data;
	int pos = -1;
	int start = 0;
	int count = 0;
	int time = 1;

	while (!data.empty())
	{
		pos = data.find(",", start);
		count++;
		if (pos == -1)
		{
			cout << "文件读取完毕！" << endl;
			break;
		}
		if (count == 5 || time == 7)
		{
			room_number = data.substr(start, pos - start);
			if (room_number == "机房1")
			{
				num[0]++;
			}
			else if (room_number == "机房2")
			{
				num[1]++;
			}
			else
			{
				num[2]++;
			}
			time = 0;
		}
		start = pos + 1;
		time++;
	}
	ifs1.close();

	//更新容器vcr1中的机房剩余的大小
	int i = 0;
	for (vector<computerRoom>::iterator it = vcr1.begin(); it != vcr1.end(); it++)
	{
		it->m_rest = it->m_number - num[i];
		i++;
	}
	//将 ROOM_FILE 中的信息清空
	ofstream ofs1;
	ofs1.open(ROOM_FILE, ios::trunc);
	ofs1.close();

	//将容器vcr1中的信息写入 ROOM_FILE 中
	ofstream ofs;
	ofs.open(ROOM_FILE, ios::out | ios::app);
	for (vector<computerRoom>::iterator it = vcr1.begin(); it != vcr1.end(); it++)
	{
		ofs << it->m_id << " " << it->m_number << " " << it->m_rest << endl;
	}
	ofs.close();
}

students::~students()
{

}