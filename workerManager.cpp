#include "workerManager.h"


WorkerManager::WorkerManager()
{
	//1����һ��ʹ�ã��ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ��Ա������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//2���ļ����ڣ����Ǳ�����ˣ��ļ���û������ֻ�п��ļ�
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ��!" << endl;
		//��ʼ������
        //��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ��Ա������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3�����ļ����ڣ����Ҽ�¼����
	int num = getEmpNum();
	cout << "ְ������Ϊ��" << num << endl;
	//��ʼ��Ա������
	this->m_EmpNum = num;
	//��ʼ��Ա������ָ��
	//���ٿռ�
	this->m_EmpArray = new worker * [this->m_EmpNum];
	//��Ա����Ϣת�뵽�µ�������
	this->init_EmpArray();
	//��ʾ����Ա����Ϣ
	this->ShowWorkers();
}

void WorkerManager::ShowmMenu()
{
	cout << "****************************************************" << endl;
	cout << "********************ְ������ϵͳ********************" << endl;
	cout << "****************** 0.�˳�����ϵͳ ******************" << endl;
	cout << "****************** 1.����ְ����Ϣ ******************" << endl;
	cout << "****************** 2.��ʾְ����Ϣ ******************" << endl;
	cout << "****************** 3.ɾ����ְְ�� ******************" << endl;
	cout << "****************** 4.�޸�ְ����Ϣ ******************" << endl;
	cout << "****************** 5.����ְ����Ϣ ******************" << endl;
	cout << "****************** 6.���ձ������ ******************" << endl;
	cout << "****************** 7.��������ĵ� ******************" << endl;
	cout << "****************************************************" << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::AddWorker()
{
	int addNum = 0;
	cout << "���������ְ����������";
	cin >> addNum;
	if (addNum > 0)
	{
		//���ְ��
		//�ȼ�������¿ռ�Ĵ�С����ֹ����ռ䲻��
		int newSize = this->m_EmpNum + addNum;  //���newSize ������ܲ�̫�淶
		//�����¿ռ�
		worker** newSpace = new worker * [newSize];
		//��ԭ���ռ��е�Ա������ת���¿ռ�
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//�����Ա������
		for (int i = 0; i < addNum; i++)
		{
			int type = 0;
			int id,age;
			bool right = true;
			string name, sexy;
			worker* work1 = NULL;
			//�������ID�Ƿ��ظ�
			while (right)
			{
				cout << "�������" << this->m_EmpNum + i + 1 << "ְ��ID��";
				cin >> id;
				right = CheckID(id);
			}
			cout << "������ְ��������";
			cin >> name;
			cout << "������ְ���Ա�";
			cin >> sexy;
			cout << "������ְ����ͣ�";
			cin >> age;
			cout << "�������" << this->m_EmpNum + i + 1 << "ְ���ĸ�λ��1--Ա�� 2--���� 3--�ܲ�" << endl;
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
			//����ְ����ӵ�����newSpace��
			newSpace[this->m_EmpNum + i] = work1;
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		//����newSpace��ָ��
		this->m_EmpArray = newSpace;
		//����ְ������
		this->m_EmpNum = newSize;
		//����ְ���ļ�״̬�����ļ���־m_FileIsEmpty�趨Ϊfalse
		this->m_FileIsEmpty = false;
		//��ְ����Ϣд���ļ���
		this->save();
		//��ʾ��ӳɹ�
		cout << "�ɹ������" << addNum << "��ְ��" << endl;

		//�ͷ�newspace����Ŀռ�
		//delete[] newSpace;
	}
	else
	{
		cout << "������������" << endl;
	}

	//����ְ���ļ�״̬
	this->m_FileIsEmpty = this->checkFileIsEmpty();

	//���������ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//����Ƿ�����ظ�ID
bool WorkerManager::CheckID(int m_id)
{
	bool right = false;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (m_id == this->m_EmpArray[i]->id)
		{
			cout << "Ա��ID�ظ������������룺" << endl;
			right = true;
		}
	}
	return right;
}

//��Ա����Ϣ���浽�ı��ļ���
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
		if (occupation == "Ա��")
		{
			work2 = new employee(id, name, sexy, age);
		}
		if (occupation == "����")
		{
			work2 = new Manager(id, name, sexy, age);
		}
		if (occupation == "�ܲ�")
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
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else 
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//���ö�̬��ʾְ����Ϣ
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	//����ְ���ļ�״̬
	this->m_FileIsEmpty = this->checkFileIsEmpty();

	//���������ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//�����е�ɾ�����䱾�ʾ�������ǰ��
void WorkerManager::DeleteWorker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}
	int index;
	int id = 0;
	//ְ����Ϣ���ڣ��������ɾ������---������ǰ��
	cout << "��������Ҫɾ����ְ��ID:";
	cin >> id;
	index = this->check(id);
	if (index != -1)
	{
		for (int i = index+1; i < this->m_EmpNum; i++)
		{
			//����ǰ��
			this->m_EmpArray[i-1] = this->m_EmpArray[i];
		}
		//����ְ��������
		this->m_EmpNum--;
		//����ְ���ļ��е���Ϣ
		this->save();
		//����ļ��Ƿ��Ϊ���ļ�
		if (this->getEmpNum()==0)
		{
			this->m_FileIsEmpty = true;
		}
		cout << "ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "ɾ��ʧ�ܣ���Ա�����ݲ�����" << endl;
	}
	//����ְ���ļ�״̬
	this->m_FileIsEmpty = this->checkFileIsEmpty();

	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ���ڣ���������򷵻�ְ���������е�λ�ã����򷵻�-1��
int WorkerManager::check(int m_id)
{
	//ְ�������� 
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		//ְ������
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
	//ְ�������� 
	bool flage = false;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		//ְ������
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
		cout<< "�ļ�������" << endl;
	}
	else
	{
		//����Ҫ�޸ĵ�ְ��
		int index;
		int id = 0;
		cout << "��������Ҫ�޸ĵ�ְ��ID:";
		cin >> id;
		index = this->check(id);
		//ְ�����ڣ������޸�
		if (index != -1)
		{
			//��ɾ����Ա����Ϣ
			delete this->m_EmpArray[index];
			//Ȼ�����������µ���Ϣ
			int type = 0;
			int id, age;
			string name, sexy;
			worker* work1 = NULL;
			cout << "�������" << index << "λְ��ID��";
			cin >> id;
			cout << "������ְ��������";
			cin >> name;
			cout << "������ְ���Ա�";
			cin >> sexy;
			cout << "������ְ����ͣ�";
			cin >> age;
			cout << "�������" <<index << "λְ���ĸ�λ��1--Ա�� 2--���� 3--�ܲ�" << endl;
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
			cout << "�޸ĳɹ�" << endl;
		}
		else   //ְ��������
		{
			cout << "��Ա�����ݲ�����" << endl;
		}

		//����ְ���ļ�״̬
		this->m_FileIsEmpty = this->checkFileIsEmpty();

		system("pause");
		system("cls");
	}
}

//����ְ����Ϣ����Ϊ���֣�1������ְ��ID���ң�2��������������
void WorkerManager::SearchWorker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{
		cout << "��ѡ����ҷ�ʽ:" << endl;
		cout << "1������ID����" << endl;
		cout << "2��������������" << endl;
		int choice = 0;
		cin >> choice;
		if (choice == 1)
		{
			int id, index;
			cout << "������ְ��ID��";
			cin >> id;
			//��ѯ�Ƿ���ڸ�ְ��
			if (this->check(id) != -1)  //���ڸ�ְ��
			{
				index = this->check(id);
				this->m_EmpArray[index]->ShowInfo();
			}
			else
			{
				cout << "���޴���!" << endl;
			}
		}
		else if (choice == 2)
		{
			string name;
			int index;
			cout << "������ְ��������";
			cin >> name;
			//��ѯ�Ƿ���ڸ�ְ��
			if (this->check(name) != false)  //���ڸ�ְ��
			{

			}
			else
			{
				cout << "���޴���!" << endl;
			}
		}
	}

	//����ְ���ļ�״̬
	this->m_FileIsEmpty = this->checkFileIsEmpty();

	system("pause");
	system("cls");
}

//6.���ձ������
void WorkerManager::SortWorker()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ��ID��������" << endl;
		cout << "2����ְ��ID��������" << endl;
		int choice = 0;
		int mixormax;
		cin >> choice;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			mixormax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				//����
				if (choice == 1)
				{
					if (this->m_EmpArray[j]->id < this->m_EmpArray[mixormax]->id)
					{
						mixormax = j;
					}
				}
				//����
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
		//���浽�ļ���
		this->save();
		cout << "�����ְ����Ϣ���£�" << endl;
		//��ʾ�����ְ����Ϣ
		this->ShowWorkers();
	}
	//����ְ���ļ�״̬
	this->m_FileIsEmpty = this->checkFileIsEmpty();
}

void WorkerManager::CleanAllWorker()
{
	cout << "�Ƿ�����������ݣ�" << endl;
	cout << "1����" << endl;
	cout << "2���񲢷���" << endl;

	int choice;
	cin >> choice;
	if (choice == 1)
	{
		ofstream file1;
		file1.open(FILENAME, ios::trunc);  //ɾ��ԭ�ļ������´���ͬ�����ļ�
		file1.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				//ɾ����������ְ��
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ������������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			//����ְ����Ϣ�ļ�״̬
			this->m_FileIsEmpty = true;
		}
		else
		{
			cout << "���������!" << endl;
		}
	}
	else if (choice == 2)
	{
		system("cls");
	}
	//����ְ���ļ�״̬
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