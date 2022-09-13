#include "admirManagers.h"

//Ĭ�Ϲ��캯��
admirManagers::admirManagers()
{

}

//���ع��캯��
admirManagers::admirManagers(string name, int id, double password)
{
	this->m_name = name;
	this->m_password = password;
	this->m_id = id;
}

//��¼����
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
		cout << "�ļ�������!" << endl;
		ifs.close();
		return;
	}
	cout << "��ӭ��¼����Աϵͳ��" << endl;
	//�����֤
	while (ifs >> fid && ifs >> fname && ifs >> fpassword) //���ļ��ж�ȡ��Ϣ
	{
		cout << "����: ";
		cin >> id;
		cout << "����: ";
		cin >> name;
		cout << "����: ";
		cin >> password;

		if ((id == fid) && (name == fname) && (password == fpassword))  //��ȡ����Ϣ��������Ϣ�Ա�
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
			cout << "�˻��������������" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

	ifs.close();
}

//�˵�����
void admirManagers::subMenu()
{
	cout << "��ӭʹ�ù���Աϵͳ!" << endl;
	cout << "-------------------------" << endl;
	cout << "****** 1������˻� ******" << endl;
	cout << "****** 2���鿴�˻� ******" << endl;
	cout << "****** 3���鿴���� ******" << endl;
	cout << "****** 4�����ԤԼ ******" << endl;
	cout << "****** 5��ע����¼ ******" << endl;


	cout << "��ѡ������ʹ�õĹ���: " << endl;

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

//����˻�
void admirManagers::addAccount()
{
	cout << "����������˻�������:" << endl;
	cout << "ѧ��---1�� ��ʦ---2" << endl;
	int id;
	string name;
	int password;
	cin >> type;

	cout << "����/ѧ��: ";
	cin >> id;
	//����ظ�id
	checkRepeat(id);
	cout << "����: ";
	cin >> name;
	cout << "����: ";
	cin >> password;
	ofstream ofs;
	if (type == 1)  //���ѧ���˻�
	{
		ofs.open(STUDENTS_FILE, ios::out | ios::app);
	}
	if (type == 2)  //���ѧ���˻�
	{
		ofs.open(TEACHERS_FILE, ios::out | ios::app);
	}
	
	ofs << id << " " << name << " " << password << endl;
	ofs.close();
	cout << "�����ɹ���" << endl;
	system("pasue");
	system("cls");
}

//��ʼ����������
void admirManagers::initvector()
{
	vst.clear();
	vte.clear();

	//��ȡѧ������ʦ����Ϣ
	ifstream ifs;
	ifs.open(STUDENTS_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��!" << endl;
		ifs.close();
		return;
	}
	ifstream ifs1;
	ifs1.open(TEACHERS_FILE, ios::in);
	if (!ifs1.is_open())
	{
		cout << "�ļ���ȡʧ��!" << endl;
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
	cout << "��ǰѧ��������" << vst.size() << endl;

	while (ifs1 >> t.m_id && ifs1 >> t.m_name && ifs1 >> t.m_password)
	{
		vte.push_back(t);
	}
	ifs1.close();
	cout << "��ǰ��ʦ������" << vte.size() << endl;
}

//���غ���
void admirManagers::checkRepeat(int& id)
{
	//��ʼ������
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
					cout << "id�ظ�������������: ";
					cin >> id;
					flag1 = 1; break;//����forѭ��
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
					cout << "id�ظ�������������: ";
					cin >> id;
					flag1 = 1; break;//����forѭ��
				}
			}
		}
	}
}

//�鿴�˻�
//����һЩ�ı��ļ��е���Ϣ��ȡ����һЩ��Ҫ�鿴ĳЩ�������Ϣʱ�����ǿ��Խ�������Ƴ�һ���࣬Ȼ����������������Ϣ�������У��ٽ������������������������ʾ����һЩ������Ϣ�����Ǵ洢���ı��ļ���ʱ�����ǿ����Ƚ��ı��ļ��е���Ϣ�����������࣬�������ǾͿ��Խ��������������ʾ�����ˡ�
void admirManagers::checkAccount()
{
	initvector();
	int flag1 = 1;
	while (flag1)
	{
		cout << "��ӭʹ�ù���Ա����ϵͳ" << endl;
		cout << "1���鿴����ѧ���˻�" << endl;
		cout << "2���鿴������ʦ�˻�" << endl;
		cout << "3������ѧ���˻�" << endl;
		cout << "4��������ʦ�˻�" << endl;
		cout << "5���˳�" << endl;
		cout << "��ѡ������Ҫ�鿴���˻���";
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

//��ʾ����
void admirManagers::show(int s_or_t)
{
	if (s_or_t == 1)
	{
		for (vector<students>::iterator it = vst.begin(); it != vst.end(); it++)
		{
			cout << "ID: " << it->m_id << " " << "����: " << it->m_name << " " << "����: " << it->m_password << " " << endl;
		}
	}
	else if (s_or_t == 2)
	{
		for (vector<teachers>::iterator it = vte.begin(); it != vte.end(); it++)
		{
			cout << "ID: " << it->m_id << " " << "����: " << it->m_name << " " << "����: " << it->m_password << " " << endl;
		}
	}
	else
	{
		cout << "�������!" << endl;
		cout << "������1��ѧ���� �� 2����ʦ��!" << endl;
	}
}

//���Һ���
void admirManagers::findsort(int s_or_t)
{
	int id = 0;
	int num = 0;
	cout << "��������ҵ���ԱID�ţ�" << endl;
	cin >> id;
	if (s_or_t == 1)
	{
		for (vector<students>::iterator it = vst.begin(); it != vst.end(); it++)
		{
			if (id == it->m_id)
			{
				num++;
				cout << "ID: " << it->m_id << " " << "����: " << it->m_name << " " << "����: " << it->m_password << " " << endl;
			}
		}
		if (num <= 0)
		{
			cout << "���޴��ˣ�" << endl;
		}
	}
	else if (s_or_t == 2)
	{
		for (vector<teachers>::iterator it = vte.begin(); it != vte.end(); it++)
		{
			if (id == it->m_id)
			{
				num++;
				cout << "ID: " << it->m_id << " " << "����: " << it->m_name << " " << "����: " << it->m_password << " " << endl;
			}
		}
		if (num <= 0)
		{
			cout << "���޴��ˣ�" << endl;
		}
	}
	else
	{
		cout << "�������!" << endl;
		cout << "������1��ѧ���� �� 2����ʦ��!" << endl;
	}
}

//�˳�
int admirManagers::exitcheck(int& flag1)
{
	cout << "ллʹ�ã�" << endl;
	system("pause");
	system("cls");
	flag1 = 0;
	return flag1;
}

//���»���״̬
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
		if (count == 5||time == 7)
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


//�鿴����
void admirManagers::checkRoom()
{
	//�ȸ��»���״̬
	statusUpdate();
	
	//�ȴ���һ�������࣬�洢������ź�ʣ������
	computerRoom cR;

	//�������
	vcr.clear();

	//��������Ϣ���ı��ļ��ж���
	ifstream ifs;
	ifs.open(ROOM_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "ROOM_FILE �ļ���ʧ��!" << endl;
		ifs.close();
		return;
	}
	while (ifs >> cR.m_id && ifs >> cR.m_number && ifs >> cR.m_rest)
	{
		vcr.push_back(cR);
	}

	for (vector<computerRoom>::iterator it = vcr.begin(); it != vcr.end(); it++)
	{
		cout << "����" << it->m_id << " " <<"���� " << it->m_number << " " << "ʣ�� " << it->m_rest << endl;
	}
}

//���ԤԼ
void admirManagers::clearApply()
{
	ofstream ofs;
	ofs.open(APPLY_FILE, ios::trunc);
	ofs.close();
	cout << "��ճɹ���" << endl;
}

//ע����¼
int admirManagers::exitAdm()
{
	//delete this;
	cout << "ллʹ�ã�" << endl;
	system("pause");
	system("cls");
	return flag = 0;
}

//��������
admirManagers::~admirManagers()
{

}