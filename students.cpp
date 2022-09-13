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


	cout << "��ӭ��¼ѧ��ϵͳ��" << endl;
	while (true)
	{
		ifstream ifs;
		ifs.open(STUDENTS_FILE, ios::in);
		if (!ifs.is_open())
		{
			cout << "�ļ�������!" << endl;
			ifs.close();
			return;
		}

		//�����֤
		if (time == 0)
		{
			cout << "�������˺����룡" << endl;
			cout << "ѧ��: ";
			cin >> id;
			cout << "����: ";
			cin >> name;
			cout << "����: ";
			cin >> password;
		}
		if (num == 0 && time > 0)
		{
			cout << "�˻��������������" << endl;
			cout << "�����������˺����룡" << endl;
			cout << "ѧ��: ";
			cin >> id;
			cout << "����: ";
			cin >> name;
			cout << "����: ";
			cin >> password;
		}
		while (ifs >> fid && ifs >> fname && ifs >> fpassword) //���ļ��ж�ȡ��Ϣ
		{
			if ((id == fid) && (name == fname) && (password == fpassword))  //��ȡ����Ϣ��������Ϣ�Ա�
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
	cout << "��ӭʹ��ѧ��ϵͳ!" << endl;
	cout << "-------------------------" << endl;
	cout << "****** 1������ԤԼ ******" << endl;
	cout << "****** 2���鿴ԤԼ ******" << endl;
	cout << "****** 3��ȡ��ԤԼ ******" << endl;
	cout << "****** 4���˳�ϵͳ ******" << endl;

	cout << "��ѡ������ʹ�õĹ���: " << endl;

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

	string time1[7] = { "��һ","�ܶ�", "����", "����", "����", "����", "����" };
	string time2[2] = { "����","����" };
	while (true)
	{
		cout << "��ѡ�����ڣ�1����һ��2���ܶ���...��7������" << endl;
		cin >> i;
		if (i >= 0 && i < 8)
		{
			time = time1[i - 1]; break;
		}
		cout << "�����������������룡" << endl;
	}
	while (true)
	{
		cout << "��ѡ��ʱ�Σ�1�����磻2������" << endl;
		cin >> j;
		if (j >= 1 && j < 3)
		{
			timePeriod = time2[j - 1]; break;
		}
		cout << "�����������������룡" << endl;
	}
	while (true)
	{
		cout << "��ѡ�������1��2��3" << endl;
		cin >> room;
		if (room >= 1 && room < 4)
		{
			 break;
		}
		cout << "�����������������룡" << endl;
	}

	Apply ap(time, timePeriod, room);

	//����Ϣ����������
	statusUpdate(room);
	if (rest > 0)
	{
		this->va.push_back(ap);
		status = "1";
		cout << "ԤԼ�ɹ����ȴ���ˣ�";
	}
	else
	{
		status = "0";
		cout << "ԤԼʧ�ܣ�";
		cout << "����" << room << "��ʣ�࣡" << endl;
	}

	//������Ϣ
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
		ofile1 << (*it).m_time << "," << (*it).m_timePeriod << "," << this->m_id << "," << this->m_name << "," << "����" << (*it).m_room << "," << rest << "," << status << ",";
	}
	ofile1.close();
	//���������va��һ�������ڻ����е���������һ�����õ���ʱ��������ˣ�ÿ��ʹ�����Ҫ���
	this->va.clear();
	cout << "������ϣ�" << endl;
}

//��ѯԤԼ����
void students::inquireApply()
{
	cout << "��ѡ���ѯ����:" << endl;
	cout << "1����ѯ�ҵ�ԤԼ  2����ѯ����ԤԼ" << endl;
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
			cout << "ԤԼ��¼Ϊ�գ�" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			//to_string--��intת��Ϊstring����
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
								cout << "��˲�ͨ��" << " ";
							}
							else if (*vis == "1")
							{
								cout << "�����" << " ";
							}
							else if (*vis == "2")
							{
								cout << "���ͨ��" << " ";
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
				cout << "δ�鵽���ԤԼ��¼��" << endl;
			}
		}
	}
	if(choice == 2)
	{
		OrderFile of;
		if (of.m_order.size() == 0)
		{
			cout << "ԤԼ��¼Ϊ�գ�" << endl;
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
							cout << "��˲�ͨ��" << " ";
						}
						else if (*vis == "1")
						{
							cout << "�����" << " ";
						}
						else if (*vis == "2")
						{
							cout << "���ͨ��" << " ";
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
	//to_string--��intת��Ϊstring����
	id = to_string(this->m_id);

	OrderFile of;
	if (of.m_order.size() == 0)
	{
		cout << "ԤԼ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼��" << endl;
	cout << endl;

	vector<int> v;  //���orderFile��map�������±���
	int index = 1;
	int i = 1;
	for (map<int, vector<string>>::iterator it = of.m_order.begin(); it != of.m_order.end(); it++)
	{
		//���ж��Ƿ�Ϊ����ѧ��
		if (*((it->second.begin()) + 2) == id)
		{
			//���ж�ԤԼ״̬
			//"1"��ʾ����У�"2"��ʾԤԼ�ɹ�
			if ((*((it->second.end()) - 1) == "1") || (*((it->second.end()) - 1) == "2"))
			{
				v.push_back(i);
				cout << index++ << "�� ";
				cout << "ԤԼ���ڣ�" << *(it->second.begin()) << " ";
				cout << "ʱ��Σ�" << *((it->second.begin()) + 1) << " ";
				cout << "������ţ�" << *((it->second.begin()) + 4) << " ";
				string status;
				if (*((it->second.end()) - 1) == "1")
				{
					status = "�����";
				}
				else if (*((it->second.end()) - 1) == "2")
				{
					status = "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
			++num;
		}
		++i;
	}
	cout << endl;
	cout << "������ȡ���ļ�¼������ 0 ���أ�" << endl;
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
					//ɾ�� map ������ keyֵΪ c �Ķ�������
					of.m_order.erase(c);

					//��ʾɾ������
					cout << "ʣ��ȫ��ԤԼ�������£�" << endl;
					for (map<int, vector<string>>::iterator it = of.m_order.begin(); it != of.m_order.end(); it++)
					{
						for (vector<string>::iterator vis = (it->second).begin(); vis != (it->second).end(); vis++)
						{
							cout << *vis << " ";
						}
						cout << endl;
					}
					//���� APPLY_FILE �ļ�
					of.updateOrder();
					cout << "��ȡ����ԤԼ!" << endl;
					break;
				}
			}
			cout << "�����������������룡" << endl;
		}
	}
	else
	{
		cout << "����ԤԼ��¼��Ϊ�գ�" << endl;
	}
	
	//�����ʱ����
	v.clear();

	system("pause");
	system("cls");
}

int students::exitStd()
{
	cout << "ллʹ�ã�" << endl;
	system("pause");
	system("cls");
	return flag = 0;
}

//���»���״̬
void students::statusUpdate(int room_num)
{
	computerRoom cR1;
	vector<computerRoom> vcr1;
	vcr1.clear();
	int num[3] = { 0, 0, 0 };
	char c;

	restUpdate();

	//�� ROOM_FILE �е���Ϣ������vcr1������
	ifstream ifs;
	ifs.open(ROOM_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "ROOM_FILE �ļ���ʧ�ܣ�" << endl;
		ifs.close();
		return;
	}
	while (ifs >> cR1.m_id && ifs >> cR1.m_number && ifs >> cR1.m_rest)
	{
		vcr1.push_back(cR1);
	}
	ifs.close();

	//�� APPLY_FILE �е���Ϣ����������ͳ��ÿ��������ԤԼ����
	ifstream ifs1;
	ifs1.open(APPLY_FILE, ios::in);
	if (!ifs1.is_open())
	{
		cout << "APPLY_FILE �ļ���ʧ�ܣ�" << endl;
		ifs1.close();
		return;
	}
	//ͳ��ÿ������ԤԼ�ĸ���
	string data;
	string room_number;

	int pos = -1;
	int start = 0;
	int count = 0;
	int time = 1;

	//�� APPLY_FILE �е���Ϣ���� data ��
	ifs1 >> data;

	while (!data.empty())
	{
		pos = data.find(",", start);
		count++;
		if (pos == -1)
		{
			cout << "�ļ���ȡ��ϣ�" << endl;
			break;
		}
		if (count == 5 || time == 7)
		{
			room_number = data.substr(start, pos - start);
			if (room_number == "����1")
			{
				num[0]++;
			}
			else if (room_number == "����2")
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

	//��������vcr1�еĻ���ʣ��Ĵ�С
	int i = 0;
	for (vector<computerRoom>::iterator it = vcr1.begin(); it != vcr1.end(); it++)
	{
		it->m_rest = it->m_number - num[i];
		i++;
	}
	//�� ROOM_FILE �е���Ϣ���
	ofstream ofs1;
	ofs1.open(ROOM_FILE, ios::trunc);
	ofs1.close();

	//������vcr1�е���Ϣд�� ROOM_FILE ��
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

	//�� ROOM_FILE �е���Ϣ������vcr1������
	ifstream ifs;
	ifs.open(ROOM_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "ROOM_FILE �ļ���ʧ�ܣ�" << endl;
		ifs.close();
		return;
	}
	while (ifs >> cR1.m_id && ifs >> cR1.m_number && ifs >> cR1.m_rest)
	{
		vcr1.push_back(cR1);
	}
	ifs.close();

	//�� APPLY_FILE �е���Ϣ������va1�����У�����ͳ��ÿ��������ԤԼ����
	ifstream ifs1;
	ifs1.open(APPLY_FILE, ios::in);
	if (!ifs1.is_open())
	{
		cout << "APPLY_FILE �ļ���ʧ�ܣ�" << endl;
		ifs1.close();
		return;
	}
	//ͳ��ÿ������ԤԼ�ĸ���
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
			cout << "�ļ���ȡ��ϣ�" << endl;
			break;
		}
		if (count == 5 || time == 7)
		{
			room_number = data.substr(start, pos - start);
			if (room_number == "����1")
			{
				num[0]++;
			}
			else if (room_number == "����2")
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

	//��������vcr1�еĻ���ʣ��Ĵ�С
	int i = 0;
	for (vector<computerRoom>::iterator it = vcr1.begin(); it != vcr1.end(); it++)
	{
		it->m_rest = it->m_number - num[i];
		i++;
	}
	//�� ROOM_FILE �е���Ϣ���
	ofstream ofs1;
	ofs1.open(ROOM_FILE, ios::trunc);
	ofs1.close();

	//������vcr1�е���Ϣд�� ROOM_FILE ��
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