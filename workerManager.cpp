#include "workerManager.h"


WorkerManager::WorkerManager()
{
	//1、第一次使用，文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化员工数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//2、文件存在，但是被清空了，文件中没有数据只有空文件
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		cout << "文件为空!" << endl;
		//初始化属性
        //初始化记录人数
		this->m_EmpNum = 0;
		//初始化员工数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3、当文件存在，并且记录数据
	int num = getEmpNum();
	cout << "职工人数为：" << num << endl;
	//初始化员工人数
	this->m_EmpNum = num;
	//初始化员工数组指针
	//开辟空间
	this->m_EmpArray = new worker * [this->m_EmpNum];
	//将员工信息转入到新的数组中
	this->init_EmpArray();
	//显示所有员工信息
	this->ShowWorkers();
}

void WorkerManager::ShowmMenu()
{
	cout << "****************************************************" << endl;
	cout << "********************职工管理系统********************" << endl;
	cout << "****************** 0.退出管理系统 ******************" << endl;
	cout << "****************** 1.增加职工信息 ******************" << endl;
	cout << "****************** 2.显示职工信息 ******************" << endl;
	cout << "****************** 3.删除离职职工 ******************" << endl;
	cout << "****************** 4.修改职工信息 ******************" << endl;
	cout << "****************** 5.查找职工信息 ******************" << endl;
	cout << "****************** 6.按照编号排序 ******************" << endl;
	cout << "****************** 7.清空所有文档 ******************" << endl;
	cout << "****************************************************" << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::AddWorker()
{
	int addNum = 0;
	cout << "请输入添加职工的数量：";
	cin >> addNum;
	if (addNum > 0)
	{
		//添加职工
		//先计算添加新空间的大小，防止储存空间不够
		int newSize = this->m_EmpNum + addNum;  //这个newSize 计算可能不太规范
		//开辟新空间
		worker** newSpace = new worker * [newSize];
		//将原来空间中的员工数据转到新空间
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//添加新员工数据
		for (int i = 0; i < addNum; i++)
		{
			int type = 0;
			int id,age;
			bool right = true;
			string name, sexy;
			worker* work1 = NULL;
			//检查输入ID是否重复
			while (right)
			{
				cout << "请输入第" << this->m_EmpNum + i + 1 << "职工ID：";
				cin >> id;
				right = CheckID(id);
			}
			cout << "请输入职工姓名：";
			cin >> name;
			cout << "请输入职工性别：";
			cin >> sexy;
			cout << "请输入职工年纪：";
			cin >> age;
			cout << "请输入第" << this->m_EmpNum + i + 1 << "职工的岗位：1--员工 2--经理 3--总裁" << endl;
			cin >> type;
			switch (type)
			{
			case 1:
				work1 = new employee(id, name, sexy, age); break;
			case 2:
				work1 = new Manager(id, name, sexy, age); break;
			case 3:
				work1 = new Boss(id, name, sexy, age); break;
			default:
				system("cls");
				break;
			}
			//将新职工添加到数组newSpace中
			newSpace[this->m_EmpNum + i] = work1;
		}
		//释放原有空间
		delete[] this->m_EmpArray;
		//更改newSpace的指向
		this->m_EmpArray = newSpace;
		//更新职工人数
		this->m_EmpNum = newSize;
		//更新职工文件状态，将文件标志m_FileIsEmpty设定为false
		this->m_FileIsEmpty = false;
		//将职工信息写到文件中
		this->save();
		//提示添加成功
		cout << "成功添加了" << addNum << "名职工" << endl;

		//释放newspace申请的空间
		//delete[] newSpace;
	}
	else
	{
		cout << "输入人数有误" << endl;
	}

	//更新职工文件状态
	this->m_FileIsEmpty = this->checkFileIsEmpty();

	//清屏返回上级目录
	system("pause");
	system("cls");
}

//检查是否存在重复ID
bool WorkerManager::CheckID(int m_id)
{
	bool right = false;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (m_id == this->m_EmpArray[i]->id)
		{
			cout << "员工ID重复，请重新输入：" << endl;
			right = true;
		}
	}
	return right;
}

//将员工信息保存到文本文件中
void WorkerManager::save()
{
	ofstream file1;
	file1.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		file1 << this->m_EmpArray[i]->id << " "
			<< this->m_EmpArray[i]->name << " "
			<< this->m_EmpArray[i]->sexy << " "
			<< this->m_EmpArray[i]->age << " "
			<< this->m_EmpArray[i]->occupation << " " << endl;
	}
	file1.close();
}

bool WorkerManager::checkFileIsEmpty()
{
	bool flag = false;
	if (this->getEmpNum() == 0)
	{
		flag = true;
	}
	return flag;
}

int WorkerManager::getEmpNum()
{
	ifstream ifs;
	int num = 0;
	int age;
	int id;
	string name;
	string sexy;
	string occupation;
	ifs.open(FILENAME, ios::in);
	while (ifs >> id && ifs >> name && ifs >> sexy && ifs >> age && ifs >> occupation)
	{
		num++;
	}
	return num;
}

void WorkerManager::init_EmpArray()
{
	ifstream ifs;
	int num = 0;
	int index = 0;
	int age;
	int id;
	string name;
	string sexy;
	string occupation;
	ifs.open(FILENAME, ios::in);
	while (ifs >> id && ifs >> name && ifs >> sexy && ifs >> age && ifs >> occupation)
	{
		worker* work2 = NULL;
		if (occupation == "员工")
		{
			work2 = new employee(id, name, sexy, age);
		}
		if (occupation == "经理")
		{
			work2 = new Manager(id, name, sexy, age);
		}
		if (occupation == "总裁")
		{
			work2 = new Boss(id, name, sexy, age);
		}
		this->m_EmpArray[index] = work2;
		index++;
	}
	ifs.close();
}

void WorkerManager::ShowWorkers()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else 
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态显示职工信息
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	//更新职工文件状态
	this->m_FileIsEmpty = this->checkFileIsEmpty();

	//清屏返回上级目录
	system("pause");
	system("cls");
}

//数组中的删除，其本质就是数据前移
void WorkerManager::DeleteWorker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	int index;
	int id = 0;
	//职工信息存在，对其进行删除操作---即数据前移
	cout << "请输入想要删除的职工ID:";
	cin >> id;
	index = this->check(id);
	if (index != -1)
	{
		for (int i = index+1; i < this->m_EmpNum; i++)
		{
			//数据前移
			this->m_EmpArray[i-1] = this->m_EmpArray[i];
		}
		//更新职工总人数
		this->m_EmpNum--;
		//更新职工文件中的信息
		this->save();
		//检查文件是否成为空文件
		if (this->getEmpNum()==0)
		{
			this->m_FileIsEmpty = true;
		}
		cout << "删除成功" << endl;
	}
	else
	{
		cout << "删除失败，该员工数据不存在" << endl;
	}
	//更新职工文件状态
	this->m_FileIsEmpty = this->checkFileIsEmpty();

	system("pause");
	system("cls");
}

//判断职工是否存在，如果存在则返回职工在数组中的位置，否则返回-1；
int WorkerManager::check(int m_id)
{
	//职工不存在 
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		//职工存在
		if (this->m_EmpArray[i]->id == m_id)
		{
			index = i;
			break;
		}
	}
	return index;
}

bool WorkerManager::check(string m_name)
{
	//职工不存在 
	bool flage = false;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		//职工存在
		if (this->m_EmpArray[i]->name == m_name)
		{
			this->m_EmpArray[i]->ShowInfo();
			flage = true;
		}
	}
	return flage;
}

void WorkerManager::ModifyWorker()
{
	if (this->m_FileIsEmpty)
	{
		cout<< "文件不存在" << endl;
	}
	else
	{
		//查找要修改的职工
		int index;
		int id = 0;
		cout << "请输入想要修改的职工ID:";
		cin >> id;
		index = this->check(id);
		//职工存在，进行修改
		if (index != -1)
		{
			//先删除该员工信息
			delete this->m_EmpArray[index];
			//然后重新输入新的信息
			int type = 0;
			int id, age;
			string name, sexy;
			worker* work1 = NULL;
			cout << "请输入第" << index << "位职工ID：";
			cin >> id;
			cout << "请输入职工姓名：";
			cin >> name;
			cout << "请输入职工性别：";
			cin >> sexy;
			cout << "请输入职工年纪：";
			cin >> age;
			cout << "请输入第" <<index << "位职工的岗位：1--员工 2--经理 3--总裁" << endl;
			cin >> type;
			switch (type)
			{
			case 1:
				work1 = new employee(id, name, sexy, age); break;
			case 2:
				work1 = new Manager(id, name, sexy, age); break;
			case 3:
				work1 = new Boss(id, name, sexy, age); break;
			default:
				system("cls");
				break;
			}
			this->m_EmpArray[index] = work1;
			this->save();
			cout << "修改成功" << endl;
		}
		else   //职工不存在
		{
			cout << "该员工数据不存在" << endl;
		}

		//更新职工文件状态
		this->m_FileIsEmpty = this->checkFileIsEmpty();

		system("pause");
		system("cls");
	}
}

//查找职工信息，分为两种，1、按照职工ID查找；2、按照姓名查找
void WorkerManager::SearchWorker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		cout << "请选择查找方式:" << endl;
		cout << "1、根据ID查找" << endl;
		cout << "2、根据姓名查找" << endl;
		int choice = 0;
		cin >> choice;
		if (choice == 1)
		{
			int id, index;
			cout << "请输入职工ID：";
			cin >> id;
			//查询是否存在该职工
			if (this->check(id) != -1)  //存在该职工
			{
				index = this->check(id);
				this->m_EmpArray[index]->ShowInfo();
			}
			else
			{
				cout << "查无此人!" << endl;
			}
		}
		else if (choice == 2)
		{
			string name;
			int index;
			cout << "请输入职工姓名：";
			cin >> name;
			//查询是否存在该职工
			if (this->check(name) != false)  //存在该职工
			{

			}
			else
			{
				cout << "查无此人!" << endl;
			}
		}
	}

	//更新职工文件状态
	this->m_FileIsEmpty = this->checkFileIsEmpty();

	system("pause");
	system("cls");
}

//6.按照编号排序
void WorkerManager::SortWorker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工ID升序排列" << endl;
		cout << "2、按职工ID降序排列" << endl;
		int choice = 0;
		int mixormax;
		cin >> choice;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			mixormax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				//升序
				if (choice == 1)
				{
					if (this->m_EmpArray[j]->id < this->m_EmpArray[mixormax]->id)
					{
						mixormax = j;
					}
				}
				//降序
				if (choice == 2)
				{
					if (this->m_EmpArray[j]->id > this->m_EmpArray[mixormax]->id)
					{
						mixormax = j;
					}
				}
			}
			worker *worker1;
			if (i != mixormax)
			{
				worker1 = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[mixormax];
				this->m_EmpArray[mixormax] = worker1;
			}
		}
		//保存到文件中
		this->save();
		cout << "排序后职工信息如下：" << endl;
		//显示排序后职工信息
		this->ShowWorkers();
	}
	//更新职工文件状态
	this->m_FileIsEmpty = this->checkFileIsEmpty();
}

void WorkerManager::CleanAllWorker()
{
	cout << "是否清空所有数据？" << endl;
	cout << "1、是" << endl;
	cout << "2、否并返回" << endl;

	int choice;
	cin >> choice;
	if (choice == 1)
	{
		ofstream file1;
		file1.open(FILENAME, ios::trunc);  //删除原文件并重新创立同名空文件
		file1.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				//删除堆区所有职工
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区的数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			//更新职工信息文件状态
			this->m_FileIsEmpty = true;
		}
		else
		{
			cout << "数据已清空!" << endl;
		}
	}
	else if (choice == 2)
	{
		system("cls");
	}
	//更新职工文件状态
	this->m_FileIsEmpty = this->checkFileIsEmpty();
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}