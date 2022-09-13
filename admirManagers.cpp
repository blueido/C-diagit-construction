#include "admirManagers.h"

//默认构造函数
admirManagers::admirManagers()
{

}

//重载构造函数
admirManagers::admirManagers(string name, int id, double password)
{
	this->m_name = name;
	this->m_password = password;
	this->m_id = id;
}

//登录函数
void admirManagers::load()
{
	flag = 1;
	int id;
	string name;
	double password;
	int fid;
	string fname;
	double fpassword;
	string data;


	ifstream ifs;
	ifs.open(ADMIN_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在!" << endl;
		ifs.close();
		return;
	}
	cout << "欢迎登录管理员系统！" << endl;
	//身份验证
	while (ifs >> fid && ifs >> fname && ifs >> fpassword) //从文件中读取信息
	{
		cout << "工号: ";
		cin >> id;
		cout << "姓名: ";
		cin >> name;
		cout << "密码: ";
		cin >> password;

		if ((id == fid) && (name == fname) && (password == fpassword))  //读取的信息与输入信息对比
		{
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
		else
		{
			cout << "账户与密码输入错误！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

	ifs.close();
}

//菜单界面
void admirManagers::subMenu()
{
	cout << "欢迎使用管理员系统!" << endl;
	cout << "-------------------------" << endl;
	cout << "****** 1、添加账户 ******" << endl;
	cout << "****** 2、查看账户 ******" << endl;
	cout << "****** 3、查看机房 ******" << endl;
	cout << "****** 4、清空预约 ******" << endl;
	cout << "****** 5、注销登录 ******" << endl;


	cout << "请选择你想使用的功能: " << endl;

	int adm_choice;
	cin >> adm_choice;
	switch (adm_choice)
	{
	case 1: addAccount(); break;
	case 2: checkAccount(); break;
	case 3: checkRoom(); break;
	case 4: clearApply(); break;
	case 5: exitAdm(); break;
	default:
		system("cls");
		break;
	}
}

//添加账户
void admirManagers::addAccount()
{
	cout << "请输入添加账户的类型:" << endl;
	cout << "学生---1， 老师---2" << endl;
	int id;
	string name;
	int password;
	cin >> type;

	cout << "工号/学号: ";
	cin >> id;
	//检测重复id
	checkRepeat(id);
	cout << "姓名: ";
	cin >> name;
	cout << "密码: ";
	cin >> password;
	ofstream ofs;
	if (type == 1)  //添加学生账户
	{
		ofs.open(STUDENTS_FILE, ios::out | ios::app);
	}
	if (type == 2)  //添加学生账户
	{
		ofs.open(TEACHERS_FILE, ios::out | ios::app);
	}
	
	ofs << id << " " << name << " " << password << endl;
	ofs.close();
	cout << "创建成功！" << endl;
	system("pasue");
	system("cls");
}

//初始化容器函数
void admirManagers::initvector()
{
	vst.clear();
	vte.clear();

	//获取学生和老师的信息
	ifstream ifs;
	ifs.open(STUDENTS_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败!" << endl;
		ifs.close();
		return;
	}
	ifstream ifs1;
	ifs1.open(TEACHERS_FILE, ios::in);
	if (!ifs1.is_open())
	{
		cout << "文件读取失败!" << endl;
		ifs1.close();
		return;
	}

	students s;
	teachers t;

	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_password)
	{
		vst.push_back(s);
	}
	ifs.close();
	cout << "当前学生数量：" << vst.size() << endl;

	while (ifs1 >> t.m_id && ifs1 >> t.m_name && ifs1 >> t.m_password)
	{
		vte.push_back(t);
	}
	ifs1.close();
	cout << "当前老师数量：" << vte.size() << endl;
}

//查重函数
void admirManagers::checkRepeat(int& id)
{
	//初始化容器
	initvector();
	int flag1 = 1;
	if (type == 1)
	{
		while (flag1)
		{
			if (vst.size() == 0)
			{
				break;
			}
			for (vector<students>::iterator it = vst.begin(); it != vst.end(); it++)
			{
				flag1 = 0;
				if (id == it->m_id)
				{
					cout << "id重复，请重新输入: ";
					cin >> id;
					flag1 = 1; break;//跳出for循环
				}
			}
		}
	}
	if (type == 2)
	{
		while (flag1)
		{
			if (vte.size() == 0)
			{
				break;
			}
			for (vector<teachers>::iterator it = vte.begin(); it != vte.end(); it++)
			{
				flag1 = 0;
				if (id == it->m_id)
				{
					cout << "id重复，请重新输入: ";
					cin >> id;
					flag1 = 1; break;//跳出for循环
				}
			}
		}
	}
}

//查看账户
//对于一些文本文件中的信息获取或者一些需要查看某些对象的信息时，我们可以将对象设计出一个类，然后将这个对象的所有信息放入类中，再将类放入容器，利用容器来显示；当一些对象信息被我们存储到文本文件中时，我们可以先将文本文件中的信息读出并赋给类，这样我们就可以将类存入容器并显示出来了。
void admirManagers::checkAccount()
{
	initvector();
	int flag1 = 1;
	while (flag1)
	{
		cout << "欢迎使用管理员查找系统" << endl;
		cout << "1、查看所有学生账户" << endl;
		cout << "2、查看所有老师账户" << endl;
		cout << "3、查找学生账户" << endl;
		cout << "4、查找老师账户" << endl;
		cout << "5、退出" << endl;
		cout << "请选择你想要查看的账户：";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:show(1); break;
		case 2:show(2); break;
		case 3:findsort(1); break;
		case 4:findsort(2); break;
		case 5:exitcheck(flag1); break;
		default:
			system("cls");
			break;
		}
		system("pause");
		system("cls");
	}
}

//显示函数
void admirManagers::show(int s_or_t)
{
	if (s_or_t == 1)
	{
		for (vector<students>::iterator it = vst.begin(); it != vst.end(); it++)
		{
			cout << "ID: " << it->m_id << " " << "姓名: " << it->m_name << " " << "密码: " << it->m_password << " " << endl;
		}
	}
	else if (s_or_t == 2)
	{
		for (vector<teachers>::iterator it = vte.begin(); it != vte.end(); it++)
		{
			cout << "ID: " << it->m_id << " " << "姓名: " << it->m_name << " " << "密码: " << it->m_password << " " << endl;
		}
	}
	else
	{
		cout << "输入错误!" << endl;
		cout << "请输入1（学生） 或 2（老师）!" << endl;
	}
}

//查找函数
void admirManagers::findsort(int s_or_t)
{
	int id = 0;
	int num = 0;
	cout << "请输入查找的人员ID号！" << endl;
	cin >> id;
	if (s_or_t == 1)
	{
		for (vector<students>::iterator it = vst.begin(); it != vst.end(); it++)
		{
			if (id == it->m_id)
			{
				num++;
				cout << "ID: " << it->m_id << " " << "姓名: " << it->m_name << " " << "密码: " << it->m_password << " " << endl;
			}
		}
		if (num <= 0)
		{
			cout << "查无此人！" << endl;
		}
	}
	else if (s_or_t == 2)
	{
		for (vector<teachers>::iterator it = vte.begin(); it != vte.end(); it++)
		{
			if (id == it->m_id)
			{
				num++;
				cout << "ID: " << it->m_id << " " << "姓名: " << it->m_name << " " << "密码: " << it->m_password << " " << endl;
			}
		}
		if (num <= 0)
		{
			cout << "查无此人！" << endl;
		}
	}
	else
	{
		cout << "输入错误!" << endl;
		cout << "请输入1（学生） 或 2（老师）!" << endl;
	}
}

//退出
int admirManagers::exitcheck(int& flag1)
{
	cout << "谢谢使用！" << endl;
	system("pause");
	system("cls");
	flag1 = 0;
	return flag1;
}

//更新机房状态
void admirManagers::statusUpdate()
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
		if (count == 5||time == 7)
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


//查看机房
void admirManagers::checkRoom()
{
	//先更新机房状态
	statusUpdate();
	
	//先创建一个机房类，存储机房编号和剩余容量
	computerRoom cR;

	//清空容器
	vcr.clear();

	//将机房信息从文本文件中读出
	ifstream ifs;
	ifs.open(ROOM_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "ROOM_FILE 文件打开失败!" << endl;
		ifs.close();
		return;
	}
	while (ifs >> cR.m_id && ifs >> cR.m_number && ifs >> cR.m_rest)
	{
		vcr.push_back(cR);
	}

	for (vector<computerRoom>::iterator it = vcr.begin(); it != vcr.end(); it++)
	{
		cout << "机房" << it->m_id << " " <<"总量 " << it->m_number << " " << "剩余 " << it->m_rest << endl;
	}
}

//清空预约
void admirManagers::clearApply()
{
	ofstream ofs;
	ofs.open(APPLY_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功！" << endl;
}

//注销登录
int admirManagers::exitAdm()
{
	//delete this;
	cout << "谢谢使用！" << endl;
	system("pause");
	system("cls");
	return flag = 0;
}

//析构函数
admirManagers::~admirManagers()
{

}