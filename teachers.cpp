#include "teachers.h"

using namespace std;


//Ĭ�Ϲ���
teachers::teachers()
{

}

//���ع���
teachers::teachers(string name, int id, double password)
{
	this->m_name = name;
	this->m_id = id;
	this->m_password = password;
}

//��¼����
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

	cout << "��ӭ��¼��ʦϵͳ��" << endl;
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

void teachers::subMenu()
{
	cout << "��ӭʹ�ý�ʦϵͳ!" << endl;
	cout << "-------------------------" << endl;
	cout << "****** 1���鿴ԤԼ ******" << endl;
	cout << "****** 2�����ԤԼ ******" << endl;
	cout << "****** 3���˳�ϵͳ ******" << endl;

	cout << "��ѡ������ʹ�õĹ���: " << endl;

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

//�鿴ԤԼ
void teachers::checkApply()
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
	system("pause");
	system("cls");
}

//���ԤԼ
void teachers::auditApply()
{
	OrderFile of;
	vector<int> v;
	if (of.m_order.size() == 0)
	{
		cout << "ԤԼΪ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����˵�����ԤԼ��¼���£�" << endl;
	int i = 1;
	int num = 0;
	int index = 1;
	for (map<int, vector<string>>::iterator it = of.m_order.begin(); it != of.m_order.end(); it++)
	{
		if (*(it->second.end() - 1) == "1")
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
			cout << status << endl;
			num++;
		}
		i++;
	}

	if (num == 0)
	{
		cout << "�޴���˵����룡" << endl;
	}
	else
	{
		int choice;
		int result;
		cout << "�����������˵�������ţ�0 �˳�" << endl;
		while (true)
		{
			cin >> choice;
			if (choice >= 0 && choice <= v.size())
			{
				if (choice == 1)
				{
					cout << "  ��������˽�� " << endl;
					cout << "1--ͨ����2--��ͨ��" << endl;
					cin >> result;
					if (result == 1)
					{
						int c = v[choice - 1];
						vector<string>::iterator it = of.m_order[c].begin();
						*(it + 6) = "2"; //status=2,��ͨ��
					}
					if (result == 2)
					{
						int c = v[choice - 1];
						vector<string>::iterator it = of.m_order[c].begin();
						*(it + 6) = "0"; //status=0,����ͨ��
					}
					//���� APPLY_FILE �ļ�
					of.updateOrder();
					break;
				}
				else if (choice == 0)
				{
					break;
				}
			}
			
			cout << "�����������������:" << endl;
			
		}
	}
	//�����ʱ����
	v.clear();

	system("pause");
	system("cls");
}

//ע����¼
int teachers::exitTeh()
{
	cout << "ллʹ�ã�" << endl;
	system("pause");
	system("cls");
	return flag = 0;
}

//��������
teachers::~teachers()
{

}