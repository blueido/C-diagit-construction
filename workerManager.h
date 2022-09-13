#pragma once   //��ֹͷ�ļ��ظ�����
#include <iostream>
#include <string>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "Boss.h"

#define FILENAME "ְ����Ϣ.txt"

using namespace std;

class WorkerManager
{
public:
	//���캯��
	WorkerManager();

	//�˵�����
	void ShowmMenu();

	//�˳�ϵͳ
	void ExitSystem();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	worker** m_EmpArray;

	//����ְ����Ϣ
	void AddWorker();

	//����Ƿ�����ظ�ID
	bool CheckID(int m_id);

	//������Ϣ����Ա����Ϣ���浽�ı��ļ���
	void save();

	//�ж��ļ��Ƿ�Ϊ�� ��־,false��ʾ�ļ���Ϊ�գ�true��ʾ�ļ�Ϊ��
	bool m_FileIsEmpty;

	//����ļ��Ƿ�Ϊ��
	bool checkFileIsEmpty();

	//ͳ���ļ���ְ������
	int getEmpNum();

	//��ʼ��ȫ���ļ��е�ְ������
	void init_EmpArray();

	//��ʾְ����Ϣ
	void ShowWorkers();

	//ɾ����ְְ��
	void DeleteWorker();

	//�ж�ְ���Ƿ���ڣ���������򷵻�ְ���������е�λ�ã����򷵻�-1��
	int check(int m_id);
	bool check(string m_name);

	//�޸�ְ����Ϣ
	void ModifyWorker();

	//����ְ����Ϣ
	void SearchWorker();

	//����ְ��ID����
	void SortWorker();

	//�����������
	void CleanAllWorker();

	//��������
	~WorkerManager();
};
