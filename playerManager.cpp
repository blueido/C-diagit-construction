#include "playerManager.h"

playerManager::playerManager()
{

}

void playerManager::showMenu()
{
	cout << "****************************************************" << endl;
	cout << "********************�ݽ�����ϵͳ********************" << endl;
	cout << "****************** 0.�˳�����ϵͳ ******************" << endl;
	cout << "****************** 1.��ʼ�ݽ����� ******************" << endl;
	cout << "****************** 2.�鿴�����¼ ******************" << endl;
	cout << "****************** 3.��ձ�����¼ ******************" << endl;
	cout << "****************************************************" << endl;
}

void playerManager::exitSystem()
{
	cout << "�����˳�ϵͳ" << endl;
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}


void playerManager::createPlayer1(vector<player1>& py)
{
	string name1[] = { "��һ","Ǯ��","����","����","����","����","֣��","����","���", "��ʮ", "��ʮһ", "��ʮ��" };
	string sex1[] = { "��","��","Ů","Ů","Ů","Ů","��","��","Ů", "��", "Ů", "��" };
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
		cout << "��ţ�" << (*it).m_id << "  ��ͣ�" << (*it).m_age << "  ������" << (*it).m_name << "  �Ա�" << (*it).m_sex << "  �ɼ���" << (*it).m_grade << endl;
	}
	cout << endl;
}

void playerManager::createGrade(player1& p)
{
	double grade = 0;
	deque<double>PingWei;
	//�������num_pingwei1λ��ί�Ĵ��
	for (int i = 0; i < num_pingwei1; i++)
	{
		grade = (rand() % 301 + 700.0) /10.f;
		//�������洢��deque������
		PingWei.push_front(grade);
	}
	//�Է�����������
	sort(PingWei.begin(), PingWei.end());

	//ȥ����߷ֺ���߷֣�������erase�������ʹ��pop_font��pop_back;
	PingWei.erase(PingWei.begin());
	PingWei.erase(PingWei.end() - 1);
	//cout << "ȥ����߷�����ͷ֣�������£�" << endl;
	//showdeque(PingWei);

	//�Է��������ۼ�
	grade = accumulate(PingWei.begin(), PingWei.end(), 0);
	grade /= PingWei.size();
	//���õ��ķ�������player
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
	multimap<double, player1, greater<double>> time_m1;  //��ʱ����
	for (vector<player1>::iterator it = m.begin(); it != m.end(); it++)
	{
		//��ѡ�ֳɼ�
		createGrade(*it);

		time_m1.insert(make_pair((*it).m_grade, *it));
		num++;
		//6��һ��
		if (num % 6 == 0)
		{
			int count = 0;
			cout << "��" << num / 6 << "С��ɼ�����:" << endl;
			for (multimap<double, player1, greater<double>>::iterator mit = time_m1.begin(); mit != time_m1.end(); mit++)
			{
				cout << "��ţ�" << (*mit).second.m_id << "  ��ͣ�" << (*mit).second.m_age << "  ������" << (*mit).second.m_name << "  �Ա�" << (*mit).second.m_sex << "  �ɼ���" << (*mit).second.m_grade << endl;
			}
			cout << "��" << num / 6 << "С��ǰ��������:" << endl;
			for (multimap<double, player1, greater<double>>::iterator mit = time_m1.begin(); mit != time_m1.end() && count < 3; mit++)
			{
				cout << "��ţ�" << (*mit).second.m_id << "  ��ͣ�" << (*mit).second.m_age << "  ������" << (*mit).second.m_name << "  �Ա�" << (*mit).second.m_sex << "  �ɼ���" << (*mit).second.m_grade << endl;
				if (index == 1)
				{
					//��ǰ����ѡ����Ϣд��py2������
					py2.push_back((*mit).second);
				}
				else
				{
					//��ǰ����ѡ����Ϣд��py2������
					py3.push_back((*mit).second);
				}

				count++;
			}
			//�����ʱ����
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
	string mingci[3] = { "�ھ�","�Ǿ�","����" };
	ofstream fl1;
	fl1.open("play_info.csv", ios::out | ios::app);
	int i = 0;
	for (vector<player1>::iterator it = py3.begin(); it != py3.end(); it++)
	{
		fl1 << mingci[i] << "," << (*it).m_id << "," << (*it).m_age << "," << (*it).m_name << "," << (*it).m_sex << "," << (*it).m_grade << ",";
		i++;
	}
	fl1.close();
	cout << "��¼������ϣ�" << endl;
}

void playerManager::startSpeech()
{
	//����ѡ��
	createPlayer1(py1);
	//show_player1(py1);
	//��һ��
	index = 1;
	//��ǩ
	random_shuffle(py1.begin(), py1.end());
	//show_player1(py1);
	
	//����
	speech();

	//�ڶ���
	index = 2;
	//��ǩ
	random_shuffle(py2.begin(), py2.end());
	//����
	speech();

	//���浽�ļ�
	savePlayer();

	//�������
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
	int index = 0; //��ʾ�ڼ���
	ifl1.open("play_info.csv", ios::in);
	if (!ifl1.is_open())
	{
		cout << "play_info.csv��ʧ�ܣ�" << endl;
		ifl1.close();
		return;
	}
	char ch;
	ifl1 >> ch;
	if (ifl1.eof())
	{
		cout << "play_info.csv Ϊ���ļ���" << endl;
		ifl1.close();
		return;
	}

	ifl1.putback(ch);  //�������ȡ�ĵ����ַ��Ż�ȥ

	string data;
	ifl1 >> data;
	int pos = -1;
	int start = 0;
	int count = 0;
	while (!data.empty())
	{
		pos = data.find(",", start);
		count++; //ͳ�ƶ�ȡ�˶��ٴ�
		if (pos == -1)
		{
			cout << "�ļ���ȡ��ϣ�" << endl;
			break;
		}
		//����18������
		vs.push_back(data.substr(start, pos - start));
		//��18��Ϊһ�飬��Ϊÿ��3��ѡ�֣�ÿ��ѡ��6����Ϣ���浽������
		if (count % 18 == 0)
		{
			index = count / 18;
			m.insert(make_pair(index, vs));
			//�������׼��������һ���18������
			vs.clear();
		}
		start = pos + 1;
	}
	ifl1.close();

	for (multimap<int, vector<string>>::iterator mit = m.begin(); mit != m.end(); mit++)
	{
		cout << "��" << (*mit).first << "��ǰ����ѡ����Ϣ���£�" << endl;
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
	cout << "������������м�¼��" << endl;
	cout << "�Ƿ�ȷ���� 1--ȷ��  2--ȡ��" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		ofstream ofl2;
		ofl2.open("play_info.csv", ios::trunc);
		if (ofl2.is_open())
		{
			cout << "play_info.csv ɾ���ɹ���" << endl;
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
