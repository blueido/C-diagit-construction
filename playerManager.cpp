#include "playerManager.h"

playerManager::playerManager()
{

}

void playerManager::showMenu()
{
	cout << "****************************************************" << endl;
	cout << "********************演讲管理系统********************" << endl;
	cout << "****************** 0.退出管理系统 ******************" << endl;
	cout << "****************** 1.开始演讲比赛 ******************" << endl;
	cout << "****************** 2.查看往届记录 ******************" << endl;
	cout << "****************** 3.清空比赛记录 ******************" << endl;
	cout << "****************************************************" << endl;
}

void playerManager::exitSystem()
{
	cout << "即将退出系统" << endl;
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}


void playerManager::createPlayer1(vector<player1>& py)
{
	string name1[] = { "赵一","钱二","孙三","李四","周五","吴六","郑七","王八","冯九", "陈十", "褚十一", "卫十二" };
	string sex1[] = { "男","男","女","女","女","女","男","男","女", "男", "女", "男" };
	srand((unsigned)time(NULL));
	for (int i = 0; i < this->num_player1; i++)
	{
		int id = 10001;
		id = id + i;
		int age = 0;
		age = rand() % 5 + 20;  //20-25
		player1 p(id, age, name1[i], sex1[i], 0);
		py.push_back(p);
	}
}

void playerManager::show_player1(vector<player1>& py)
{
	for (vector<player1>::iterator it = py.begin(); it < py.end(); it++)
	{
		cout << "编号：" << (*it).m_id << "  年纪：" << (*it).m_age << "  姓名：" << (*it).m_name << "  性别：" << (*it).m_sex << "  成绩：" << (*it).m_grade << endl;
	}
	cout << endl;
}

void playerManager::createGrade(player1& p)
{
	double grade = 0;
	deque<double>PingWei;
	//随机生成num_pingwei1位评委的打分
	for (int i = 0; i < num_pingwei1; i++)
	{
		grade = (rand() % 301 + 700.0) /10.f;
		//将分数存储到deque容器中
		PingWei.push_front(grade);
	}
	//对分数进行排序
	sort(PingWei.begin(), PingWei.end());

	//去除最高分和最高分，可以用erase，亦可以使用pop_font和pop_back;
	PingWei.erase(PingWei.begin());
	PingWei.erase(PingWei.end() - 1);
	//cout << "去除最高分与最低分，结果如下：" << endl;
	//showdeque(PingWei);

	//对分数进行累加
	grade = accumulate(PingWei.begin(), PingWei.end(), 0);
	grade /= PingWei.size();
	//将得到的分数赋给player
	p.m_grade = grade;

}

void playerManager::giveGrade()
{
	vector<player1> m;
	if (index == 1)
	{
		m = py1;
	}
	else
	{
		m = py2;
	}
	int num = 0;
	multimap<double, player1, greater<double>> time_m1;  //临时容器
	for (vector<player1>::iterator it = m.begin(); it != m.end(); it++)
	{
		//给选手成绩
		createGrade(*it);

		time_m1.insert(make_pair((*it).m_grade, *it));
		num++;
		//6人一组
		if (num % 6 == 0)
		{
			int count = 0;
			cout << "第" << num / 6 << "小组成绩如下:" << endl;
			for (multimap<double, player1, greater<double>>::iterator mit = time_m1.begin(); mit != time_m1.end(); mit++)
			{
				cout << "编号：" << (*mit).second.m_id << "  年纪：" << (*mit).second.m_age << "  姓名：" << (*mit).second.m_name << "  性别：" << (*mit).second.m_sex << "  成绩：" << (*mit).second.m_grade << endl;
			}
			cout << "第" << num / 6 << "小组前三名如下:" << endl;
			for (multimap<double, player1, greater<double>>::iterator mit = time_m1.begin(); mit != time_m1.end() && count < 3; mit++)
			{
				cout << "编号：" << (*mit).second.m_id << "  年纪：" << (*mit).second.m_age << "  姓名：" << (*mit).second.m_name << "  性别：" << (*mit).second.m_sex << "  成绩：" << (*mit).second.m_grade << endl;
				if (index == 1)
				{
					//将前三名选手信息写入py2容器中
					py2.push_back((*mit).second);
				}
				else
				{
					//将前三名选手信息写入py2容器中
					py3.push_back((*mit).second);
				}

				count++;
			}
			//清空临时容器
			time_m1.clear();
		}
	}
}

void playerManager::speech()
{
	giveGrade(); 
}

void playerManager::savePlayer()
{
	string mingci[3] = { "冠军","亚军","季军" };
	ofstream fl1;
	fl1.open("play_info.csv", ios::out | ios::app);
	int i = 0;
	for (vector<player1>::iterator it = py3.begin(); it != py3.end(); it++)
	{
		fl1 << mingci[i] << "," << (*it).m_id << "," << (*it).m_age << "," << (*it).m_name << "," << (*it).m_sex << "," << (*it).m_grade << ",";
		i++;
	}
	fl1.close();
	cout << "记录保存完毕！" << endl;
}

void playerManager::startSpeech()
{
	//创建选手
	createPlayer1(py1);
	//show_player1(py1);
	//第一轮
	index = 1;
	//抽签
	random_shuffle(py1.begin(), py1.end());
	//show_player1(py1);
	
	//比赛
	speech();

	//第二轮
	index = 2;
	//抽签
	random_shuffle(py2.begin(), py2.end());
	//比赛
	speech();

	//保存到文件
	savePlayer();

	//清空容器
	py1.clear();
	py2.clear();
	py3.clear();

	system("pause");
	system("cls");
}


void playerManager::findInfo()
{
	multimap<int, vector<string>> m;
	vector<string> vs;
	ifstream ifl1;
	int index = 0; //表示第几届
	ifl1.open("play_info.csv", ios::in);
	if (!ifl1.is_open())
	{
		cout << "play_info.csv打开失败！" << endl;
		ifl1.close();
		return;
	}
	char ch;
	ifl1 >> ch;
	if (ifl1.eof())
	{
		cout << "play_info.csv 为空文件！" << endl;
		ifl1.close();
		return;
	}

	ifl1.putback(ch);  //将上面读取的单个字符放回去

	string data;
	ifl1 >> data;
	int pos = -1;
	int start = 0;
	int count = 0;
	while (!data.empty())
	{
		pos = data.find(",", start);
		count++; //统计读取了多少次
		if (pos == -1)
		{
			cout << "文件读取完毕！" << endl;
			break;
		}
		//接受18个数据
		vs.push_back(data.substr(start, pos - start));
		//读18次为一组，因为每届3个选手，每个选手6个信息，存到容器中
		if (count % 18 == 0)
		{
			index = count / 18;
			m.insert(make_pair(index, vs));
			//清空容器准备接受新一组的18个数据
			vs.clear();
		}
		start = pos + 1;
	}
	ifl1.close();

	for (multimap<int, vector<string>>::iterator mit = m.begin(); mit != m.end(); mit++)
	{
		cout << "第" << (*mit).first << "届前三名选手信息如下：" << endl;
		for (vector<string>::iterator vsit = (*mit).second.begin(); vsit != (*mit).second.end(); vsit++)
		{
			cout << *vsit << " ";
		}
		cout << endl;
	}

	system("pause");
	system("cls");
}

void playerManager::clearRecord()
{
	cout << "您即将清空所有记录！" << endl;
	cout << "是否确定？ 1--确定  2--取消" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		ofstream ofl2;
		ofl2.open("play_info.csv", ios::trunc);
		if (ofl2.is_open())
		{
			cout << "play_info.csv 删除成功！" << endl;
			ofl2.close();
		}
		ofl2.close();
		system("pause");
	}
	else if (choice == 2)
	{
		system("pause");
	}
	system("cls");
}

playerManager::~playerManager()
{

}
