#include<iostream>
#include<fstream>
#include<string>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "Boss.h"
#include "police.hpp"
#include "myArray.hpp"
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <random>
#include <cstdlib>
#include <algorithm>  //��׼�㷨ͷ�ļ�
#include <functional>
#include <numeric>
#include <windows.h>
#include "playerManager.h"
#include "personManager.h"
#include "students.h"
#include "teachers.h"
#include "admirManagers.h"
#include "OrderFile.h"

using namespace std;


//����
//+����������أ�operator+��
class person
{
	public:
		int p_m;
		int p_n;
		//1��ͨ����Ա��������+��
		//person operator+ (person& p)
		//{
		//	person temp;
		//	temp.p_m = this->p_m + p.p_m;
		//	temp.p_n = this->p_n + p.p_n;
		//	return temp;
		//}
		//��Ա��������<<�Ż��������ã���Ϊ����ʵ��cout��<<���
};
//2��ͨ��ȫ�ֺ�������+�ţ���+�ŵ�����ֻ��ʹ�ú�����operator+
//person operator+ (person &p1, person &p2)
//{
//	person p3;
//	p3.p_m = p1.p_m + p2.p_m;
//	p3.p_n = p1.p_n + p2.p_n;
//	return p3;
//}


//ȫ�ֺ�������<<��
//���operator֮ǰû��ȡַ����������Һ��������趨Ϊvoid������Ҫreturn�������ڵ���<<ʱ���������ڽ�βʹ��<<endl��
//������Ϊ<<���غ������ͱ��趨Ϊ��void�����Բ������endl��
//ostream & operator<<(ostream &cout, person &temp)
//{
//	cout << temp.p_m <<endl;
//	cout << temp.p_n <<endl;
//	return cout;
//}

void test01()
{
	person p1, p2;
	p1.p_m = 10;
	p1.p_n = 5;
	p2.p_m = 11;
	p2.p_n = 6;

	person p3;
	//p3 = p1 + p2;
	//cout << p3.p_m << endl;
	//cout << p3 <<endl;
}

class Interl
{
	friend void test01();
	friend void test02();
	friend ostream& operator<<(ostream& cout, Interl temp);
	friend int main();
private:
	int num = 0;
	//����ǰ��++�����
public:
	Interl& operator++ ()
	{
		Interl int1;
		int1.num = this->num++;
		return *this;
	}
	//���غ���++�����
	Interl operator++ (int)
	{
		Interl int1;
		//�ȼ�¼��ǰֵ
		int1 = *this;
		//�ٵ���
		num++;
		//�ٷ��ؼ�¼ֵ
		return int1;
	}
};

ostream& operator<<(ostream& cout, Interl temp)
{
	cout << temp.num;
	return cout;
}

void test02()
{
	Interl int2;
	int2.num = 2;
	for(int i=0;i<2;i++)
	{
		cout << int2++ << endl;
	}
}


class person1:public person
{
public:
	person1(int age)
	{
		m_age = new int(age);
	}
	int* m_age;

	person1& operator=(person1& p)
	{
		//���ж��Ƿ��ڴ�ռ��Ѿ��ͷ�
		if (m_age != NULL)
		{
			delete m_age;
			m_age = NULL;
		}
		//���
		m_age = new int(*p.m_age);
		return *this;
	}
};

void test03()
{
	person1 p1(10);
	person1 p2(20);
	person1 p3(30);
	
	p3 = p2 = p1;
	cout << *p3.m_age << endl;
	cout << *p2.m_age << endl;
	cout << *p1.m_age << endl;
}


//�̳���ͬ�������ĵ���
class father
{
public:
	static int age; //��̬���������������������ʼ��
	static void test04()
	{
		cout << "���׵����Ϊ��" << age << endl;
	}
private:
	string name;
};
int father::age = 30;
class son :public father
{
public:
	son(int s_age)
	{
		age = s_age;
	}
	int age;
	void test04()
	{
		cout << "���ӵ����Ϊ��" << age << endl;
	}
private:
	string name;
};
void test05()
{
	father dad1;
	dad1.test04();
    son::father s1;
	son s2(18);
	s1.test04();
	s2.test04();
	s2.father::test04();
	cout<<s1.age<<endl;
}


//��̬
//��̬������
//1���м̳й�ϵ��2������Ҫ��д������麯��
//���غ���д�Ĳ�ͬ���ڣ���д��Ҫ�������ͣ���������������������һ���ģ������Ǻ�����һ�£�������һ��
//��̬������
//ͨ���Ը����ָ�����������ɶ�����Ĳ��������������dospeak�Ĳ����������õĸ���animal����ɶ�����cat�Ĳ�����
class animal
{
public:
	virtual void speak()  //�麯��,ͨ���麯������ɶ�̬�������ڳ�������֮ǰ����ַû����ǰ�󶨣�
		//virtual��ʹ����������ʱ���е�ַ�󶨣���ͨ�ĺ�����ʹ����������֮ǰ��ֱ�Ӱ��˵�ַ����ˣ�����dospeak��
		//���������ʲô�����������ִ�С�������˵������
	{
		cout << "������˵����" << endl;
	}
};
//�̳й�ϵ
class cat:public animal
{
	//��д�����е��麯��speak����
	void speak();
};

void cat::speak()
{
	cout << "è��˵����" << endl;
}

void dospeak(animal& animal)
{
	animal.speak();
}

void test06()
{
	cat cat1;
	dospeak(cat1);
}


//��̬����---������
//��ͨ����
class calculator
{
public:
	double getresult(string open)
	{
		if (open == "+")
		{
			num3 = num1 + num2;
		}
		else if(open == "-")
		{
			num3 = num1 - num2;
		}
		else if (open == "*")
		{
			num3 = num1 * num2;
		}
		return num3;
	}
	double num1, num2, num3;
};
void test07()
{
	calculator c;
	c.num1 = 10, c.num2 = 100;
	cout << "num1+num2=" << c.getresult("+") << endl;
	cout << "num1-num2=" << c.getresult("-") << endl;
	cout << "num1*num2=" << c.getresult("*") << endl;
}

//ʹ�ö�̬
//��̬����������1������̳в���д����ĺ�����2�������ָ���������ָ������Ķ���
class abstractcalculator
{
public:
	virtual double getresult()
	{
		return 0;
	}
	double num1, num2;
};
//�ӷ�
class addcalculator :public abstractcalculator
{
public:
	double getresult()           //1��������д�˸����еĺ���
	{
		return num1 + num2;
	}
};
//����
class deletecalculator :public abstractcalculator
{
public:
	double getresult()           //1��������д�˸����еĺ���
	{
		return num1 - num2;
	}
};

void test08()
{
	abstractcalculator* abs = new addcalculator;  //2�������ָ�� *absָ������Ķ���addcalculator,�ͷ����˶�̬
	abs->num1 = 10;
	abs->num2 = 100;
	cout << abs->getresult() << endl;
	delete abs;
}


//���麯���������
class Base    //������
{
public:
	//���麯��
	//ֻҪ��һ�����麯�����������ǳ�����
	//1�����������޷�ʵ��������ģ�
	//2������������������д�����еĴ��麯��������Ҳ�ǳ����ࣻ
	virtual void func() = 0;
};

class son2 :public Base 
{
public:
	void func()
	{
		cout << "�ⲻ��һ��������" << endl;
	}
};

void test09()
{
	son2 s;
	s.func();
}


//��̬����---������װ
class CPU  //������
{
public:
	virtual void calculator() = 0;
};
class videocard  //������
{
public:
	virtual void display() = 0;
};
class memory  //������
{
public:
	virtual void storagy() = 0;
};
//�����д�����麯��
//Intel
class Intelcpu :public CPU
{
public:
	void calculator()
	{
		cout << "Intel CPU��ʼ����" << endl;
	}
};

class Intelvideocard :public videocard
{
public:
	void display()
	{
		cout << "Intel videocard��ʼ����" << endl;
	}
};

class Intelmemory :public memory
{
public:
	void storagy()
	{
		cout<< "Intel memory��ʼ����" << endl;
	}
};

//Lenovo
class Lenovocpu :public CPU
{
public:
	void calculator()
	{
		cout << "Lenovo CPU��ʼ����" << endl;
	}
};

class Lenovovideocard :public videocard
{
public:
	void display()
	{
		cout << "Lenovo videocard��ʼ����" << endl;
	}
};

class Lenovomemory :public memory
{
public:
	void storagy()
	{
		cout << "Lenovo memory��ʼ����" << endl;
	}
};

//�ุ��̳�
//class Intel:public Intelcpu, public Intelvideocard, public Intelmemory
//{
//public:
//	CPU* cpu = new Intelcpu;
//	videocard* vcard = new Intelvideocard;
//	memory* mem = new Intelmemory;
//};

class computer
{
public:
	//���캯��,�ṩ��������Ľӿ�
	computer(CPU* cpu, videocard* vcard, memory* mem)
	{
		m_cpu = cpu;
		m_vcard = vcard;
		m_mem = mem;
	}
	//��������
	~computer()
	{
		if (m_cpu != NULL)
		{
			delete m_cpu;
			m_cpu = NULL;
		}
		if (m_vcard != NULL)
		{
			delete m_vcard;
			m_vcard = NULL;
		}
		if (m_mem != NULL)
		{
			delete m_mem;
			m_mem = NULL;
		}
	}
	//��������
	void work()
	{
		m_cpu->calculator();
		m_vcard->display();
		m_mem->storagy();
	}
private:
	CPU* m_cpu;
	videocard* m_vcard;
	memory* m_mem;
};

void test10()
{
	//Intel
	//ʵ�������
	CPU* intelcpu = new Intelcpu;
	videocard* vcard = new Intelvideocard;
	memory* mem = new Intelmemory;
	//ʵ��������
	computer* c = new computer(intelcpu, vcard, mem);
	//���е���
	c->work();
	delete c;
	//Lenovo
	//ʵ�������
	CPU* lenovocpu = new Lenovocpu;
	videocard* lenovovcard = new Lenovovideocard;
	memory* lenovomem = new Lenovomemory;
	//ʵ��������
	computer* c1 = new computer(lenovocpu, lenovovcard, lenovomem);
	//���е���
	c1->work();
	delete c1;
}

//�ļ�д�����ȡ
void test11()
{
	//д��
	//����������
	ofstream file1;
	//ָ�����·�����ļ����Լ�д�뷽ʽ
	file1.open("file1.txt",ios::app);
	//д������
	file1 << "����֮����������" << endl;
	//�ر��ļ���
	file1.close();

	//��ȡ
    //����������
	ifstream file2;
	//ָ����·�����ļ����Լ��򿪷�ʽ
	file2.open("file1.txt", ios::in);
	//�ж��Ƿ�򿪳ɹ�
	if(!file2.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
	}
	//��ȡ����
	//��һ��
	//char buf[1024] = { 0 };
	//while (file2 >> buf)
	//{
	//	cout << buf << endl;
	//}
	//�ڶ���
	//char buf[1024] = { 0 };
	//while (file2.getline(buf, sizeof(buf)))
	//{
	//	cout << buf << endl;
	//}
	//�����֣��Ƽ�
	string buff;
	while (getline(file2, buff))
	{
		cout << buff << endl;
	}
	//������,���Ƽ�
	//char buff;
	//while ((buff = file2.get()) != EOF)
	//{
	//	cout << buff;
	//}
	//�ر��ļ���
	file2.close();
}

//�����ƶ�д�ļ�
class persong
{
public:
	char name[1024];
	int age;
};
void test12()
{
	persong p = { "����",18 };
	fstream file3;
	file3.open("person.txt", ios::out | ios::binary);
	file3.write((const char*) &p, sizeof(persong));
	file3.close();

	ifstream file4;
	file4.open("person.txt", ios::in | ios::binary);
	if (!file4.is_open())
	{
		cout << "���ļ�ʧ��" << endl;
		return ;
	}
	file4.read((char*)&p, sizeof(persong));
	cout << "������"<<p.name << endl;
	cout << "��ͣ�"<<p.age << endl;
	file4.close();
}


//ģ��
//����ģ��
template<typename T>   //�����T��ʾһ�ַ��࣬��ʾ����һ����������
void mySwap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
	//cout << "��������a=" << a << endl;
	//cout << "��������b=" << b << endl;
}

void test13()
{
	int a = 10;
	int b = 20;
	//ģ��ĵ��÷�ʽ
	//1���Զ������ƶ�
	//mySwap(a, b);
	//2����ʽָ������
	mySwap<int>(a, b);  //�����<int>��ʾ�ɱ����ָ��T=int���ͣ��������
	//opencv��ʹ�õ���constraction����Χ����0~255���е�����ָ��
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
}

//ģ�����̳��Լ����⺯������
template <class T>
class dad1
{
public:
	T name;
};

//ģ��̳�
template <class T1,class T2>
class son1:public dad1<T1>
{
public:
	son1(T1 m_name, T2 m_age);

	T2 age;
	void showInfo();
};
//���⺯������
template <class T1, class T2>
son1<T1, T2>::son1(T1 m_name, T2 m_age)
{
	this->name = m_name;
	this->age = m_age;
}
template <class T1, class T2>
void son1<T1,T2>::showInfo()
{
	cout << "name:" << this->name <<" "<< "age" << this->age << endl;
}

void test14()
{
	son1 <string, int>s2("��˽�",90);
	s2.showInfo();
}

//����ģ����ļ���д---��Ϊ.cpp��.h�����ļ�,��Դ����.cpp��ͷ�ļ�.h�ֿ�д����ģ���еĳ�Ա�����Ĵ��������ڵ����ڼ�
//��������������ֻ����.h�ļ�ʱ
//������ֻ��ȥ�鿴.h��������ȥ����.cpp�����Ի�����ⲿ�޷���������
//�������
//1��ֱ������.cpp�ļ�
//#include "police.cpp"
//2����.cpp�е�����д��.h�У���.h��Ϊ.hpp��������
//#include "police.hpp"
//void test15()
//{
//	police<string, int>p1("ʯԭ",24);
//	p1.showInfo();
//}


//ģ��������Ԫ������ʵ��

//2������ʵ��
template<class T1, class T2, class T3>
class policeman;

template<class T1, class T2, class T3>
void showInfo2(policeman<T1, T2, T3> &p)
{
	cout << "����ʵ��--������" << p.m_name << endl;
}

//1������ʵ��
template<class T1, class T2>
class persons
{
public:
	T1 m_age;
	T2 m_name;
};
template<class T1, class T2, class T3>
class policeman :public persons<T1, T2>
{
public:
	policeman(T1 age, T2 name, T3 sexy)
	{
		this->m_name = name;
		this->m_age = age;
		this->m_sexy = sexy;
	}
	//1������������ʵ��
	friend void showInfo1(policeman<T1,T2,T3> &p)
	{
		cout << "����ʵ��--������" << p.m_name << endl;
	}
	//2����������������ʵ��
	//�����ģ������б�
	//�����Ա������ ����ʵ�֣�����Ҫ����ǰ�����������ñ�����֪��
	friend void showInfo2<>(policeman<T1, T2, T3> &p);

	T3 m_sexy;
};

void test16()
{
	//1������ʵ��
	policeman<int, string, string>p(18, "peter","��");
	showInfo1(p);

	//2������ʵ��
	policeman<int, string, string>p1(18, "joy", "��");
	showInfo2(p1);
}


void test17()
{
	myArray<int> arr1(10);
	myArray<int> arr3(10);
	myArray<int> arr2(arr1);
	//arr3 = arr2;
	for (int i = 0; i < arr1.getCpacity(); i++)
	{
		arr1.array_Add(i);
		cout << arr1[i] << endl;
	}
	arr3[1] = 1;
}



void myPrint(int value)
{
	cout << value << endl;
}

//STL--standrad temple library
//���� --vector
//���������������
void test18()
{
	//����һ��vector����
	vector<int> v;

	//�������в�������
	//β�巨
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);


	//��һ�ֱ�����ʽ
	//ͨ�����������������е�����
	//vector<int>::iterator itBegin = v.begin();  //��ʼ��������v.begin()ָ������v�еĵ�һ��Ԫ��
	//vector<int>::iterator itEnd = v.end();  //������������v.begin()ָ������v�е����һ��Ԫ�ص���һ��λ��

	//while (itBegin != itBegin)
	//{
	//	cout << *itBegin << endl;
	//	itBegin++;
	//}

	//�ڶ��ֱ�����ʽ
	//for(vector<int>::iterator it = v.begin();it!=v.end();it++)
	//{
	//	cout << *it << endl;
	//}

	//�����ֱ�����ʽ������STL�ṩ�ı����㷨
	for_each (v.begin(),v.end(),myPrint);

}


//����ʵ��
//��ί��֣�5��ѡ��ABCDE��10����ί�����֣�ȥ����ͷֺ���߷֣�ȡƽ��
class people
{
public:
	people(string name, double score)
	{
		this->m_name = name;
		this->m_score = score;
	}
	string m_name;
	double m_score;
};

void showdeque(deque<double> &d)
{
	for (deque<double>::iterator it = d.begin(); it < d.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void showvector(vector<people>& d)
{
	for (vector<people>::iterator it = d.begin(); it < d.end(); it++)
	{
		cout << (*it).m_name << " "<< (*it).m_score;
	}
	cout << endl;
}

void creatPeople(vector<people>& p)
{
	string name = "ABCDE";
	int i = 0;
	for (int i = 0; i < 5; i++)
	{
		string name1 = "ѡ��";
		name1 += name[i];
		people p1(name1, 0);
		p.push_back(p1);
	}
}

void test19()
{
	deque<double>PingWei;
	vector<people>xuanshou;

	//�������ѡ�֣�������vector������
	////��һ�ַ���
	//people p1("A", 0);
	//people p2("B", 0);
	//people p3("C", 0);
	//people p4("D", 0);
	//people p5("E", 0);
	//xuanshou.push_back(p1);
	//xuanshou.push_back(p2);
	//xuanshou.push_back(p3);
	//xuanshou.push_back(p4);
	//xuanshou.push_back(p5);
	//�ڶ��ַ���
	creatPeople(xuanshou);
	//showvector(xuanshou);

	for (vector<people>::iterator it = xuanshou.begin(); it < xuanshou.end(); it++)
	{
		double fenshu;
		cout << "������ί������";
		for (int de = 0; de < 10; de++)
		{
			cin >> fenshu;
			PingWei.push_front(fenshu);
		}
		cout << "��ί������£�" << endl;
		showdeque(PingWei);
		//�Է�����������
		sort(PingWei.begin(), PingWei.end());
		cout << "�����������£�" << endl;
		showdeque(PingWei);
		//ȥ����߷ֺ���߷֣�������erase�������ʹ��pop_font��pop_back;
		PingWei.erase(PingWei.begin());
		PingWei.erase(PingWei.end()-1);
		cout << "ȥ����߷�����ͷ֣�������£�" << endl;
		showdeque(PingWei);
		                         
		for (deque<double>::iterator de1 = PingWei.begin(); de1 < PingWei.end(); de1++)
		{
			(*it).m_score += *de1;
		}
		cout << (*it).m_name << "�ܷ�Ϊ��" << (*it).m_score << endl;
		(*it).m_score /= PingWei.size();
		cout << (*it).m_name << "�ķ���Ϊ��" << (*it).m_score << endl;
		PingWei.clear();
	}
}

//��c++��stack��queue��priority_queue������������֧�ֵ������������Ա���

//��list�������������ɵģ��������ɽڵ㹹�ɣ��ڵ����������ֹ���--��������ָ��������������洢���ǵ�ǰ�ڵ�����ݣ�
//��ָ����洢������ָ�룬�ֱ���ָ����һ���ڵ��ǰһ���ڵ�ĵ�ַ��������������list����������������ɾ��Ԫ�أ�����
//���������洢���ݵĵ�ַ�����������ģ��ҵ�ǰ�ڵ�Ķ�ȡ��Ҫ����ǰһ���ڵ��е�ָ�룬������Ķ�ȡ�ٶȺ���������ռ�ÿռ����ͬʱ�������Ĵ洢�ռ䲻������Ҳ������ĵ�����iteratorֻ֧��ǰ������ƣ�����˫��������������������ȡ��
//ͬʱ��list��vector���ڷ����ڴ�ʱ���ڰ�����䣬�ж���Ԫ�ؾͷ�����ͬ���ڴ���У�����������ռ䡣�ڲ����ɾ��Ԫ��ʱ��ֻ����ԭ�еķ���ռ��н��У���vector��Ҫ���´���һ���µĿռ䣬����������ݿ����;ɿռ�������

//list����
//��list���и�ֵ�ͽ������鿴��С�������ɾ��
void listPrint(const list<int>& L)
{
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void test20()
{
	//list��ֵ
	list<int> L;
	L.push_back(10);
	L.push_back(20);
	L.push_back(30);
	L.push_back(40);

	list<int> L2;
	L2 = L;
	//listPrint(L2);

	list<int> L3;
	L3.assign(L2.begin(), L2.end());
	//listPrint(L3);

	list<int> L4;
	L4.assign(10, 100);
	//listPrint(L4);

	//list����
	L4.swap(L3);
	//listPrint(L4);
	//listPrint(L3);

	//�鿴L4�Ƿ�Ϊ�գ����鿴L4�Ĵ�С
	if (!L4.empty())
	{
		cout << "L4��Ϊ��" << endl;
		listPrint(L4);
		cout << "L4��Ԫ�ظ���Ϊ��" << L4.size() << endl;
	}
	else
	{
		cout<< "L4Ϊ��" << endl;
	}

	////����ָ����С
	////�Ŵ�
	//L4.resize(5, 1000);
	//listPrint(L4);
	////��С
	//L4.resize(2);
	//listPrint(L4);

	//�����ɾ��
	//listPrint(L4);
	cout << "����Ԫ�غ�" << endl;
	//β��
	L4.push_back(50);
	//ͷ��
	L4.push_front(5);
	listPrint(L4);

	cout << "ɾ��Ԫ�غ�" << endl;
	//βɾ
	L4.pop_back();
	//ͷɾ
	L4.pop_front();
	listPrint(L4);

	//�����ɾ��������Ҫ���õ��������в�����
	//����
	list<int>::iterator it = L4.begin();
	//��L4.begin()֮�����1000
	L4.insert(++it, 1000);
	listPrint(L4);

	//ɾ��
	it = L4.begin();
	//ɾ��L4��ͷ��֮��ĵ�һ��Ԫ��
	L4.erase(++it);
	listPrint(L4);

	//�Ƴ�--remove
	L4.push_back(30);
	L4.remove(30);
	listPrint(L4);

	//���--clear
	L4.clear();
	listPrint(L4);
}

//list���ݴ�ȡ
bool delivery(int v1, int v2)
{
	return v1 > v2;
}

void test21()
{
	//list��ֵ
	list<int> L;
	L.push_back(10);
	L.push_back(20);
	L.push_back(30);
	L.push_back(40);

	//����list�еĵ�һ��Ԫ��
	//����ʹ��[]��.at����������
	//����list�����е�Ԫ�ط��ʣ�ֻ��ʹ��front(),back()�������õ���������˫�������������++������--������������ʹ�����������������+1��+2�Ȳ�������������Ϊlist����ʹ�����������
	cout<<"L�еĵ�һ��Ԫ�أ�"<<L.front()<<endl;

	cout << "L�е����һ��Ԫ�أ�" << L.back() << endl;

	//��ת--reverse
	cout << "��תǰ��" << endl;
	listPrint(L);
	//��ת
	L.reverse();
	cout << "��ת��" << endl;
	listPrint(L);

	//����--sort
	//���ڲ���ʹ��������ʵ����������������ڲ������Դ��ĳ�Ա��������������,��list.sort()��������vector�ȿ���ʹ��������ʵ��������������ԣ����ǵ�������ͨ��ʹ��ȫ�ֺ���sort����ʵ�ֵģ���sort(vector.begin(), vector.end());
	//����
	L.sort();
	listPrint(L);
	//���򣬶��ڳ�����������������򷽰�������ʹ��������ʵ�����������,��Ҫ�趨������򣬼�list.sort(sort regular);
	L.sort(delivery);
	listPrint(L);
}
  

//������
//��students�Զ����������ͽ�������student����������������͡����
//������򣺰�����ͽ������������ͬʱ�������߽��н�������
//���ȴ�����student
class student 
{
public:
	student(string name, int age, float high)
	{
		s_name = name;
		s_age = age;
		s_high = high;
	}
	string s_name;
	int s_age;
	float s_high;
};
void creatStudent(vector<student>& s)
{
	string name = "ABCDE";
	int age[5] = { 18,20,30,25,20 };
	float high[5] = { 170,175,173,180,170 };
	int i = 0;
	for (int i = 0; i < 5; i++)
	{
		string name1 = "ѧ��";
		name1 += name[i];
		student s1(name1, age[i], high[i]);
		s.push_back(s1);
	}
}
void showSvector(vector<student>& d)
{
	for (vector<student>::iterator it = d.begin(); it < d.end(); it++)
	{
		cout << (*it).s_name << " " << (*it).s_age << " " << (*it).s_high << endl;
	}
}

bool increas_age(student s1, student s2)  //������ͽ�����������
{
	if (s1.s_age == s2.s_age)    //�����������������ͬ���������߽��н�������
	{
		return s1.s_high > s2.s_high;
	}
	return s1.s_age < s2.s_age;
}

bool increas_high(student s1, student s2)  //������߽�����������
{
	if (s1.s_high == s2.s_high)    //�����������������ͬ��������ͽ��н�������
	{
		return s1.s_age > s2.s_age;
	}
	return s1.s_high < s2.s_high;
}

void test22()
{
	vector<student> v1;
	creatStudent(v1);
	//showSvector(v1);
	//���ڿ���ʹ��������ʵ�������������������ʹ��sort���ȫ�ֺ����������ڵĶ����������ʱ������ֱ�ӽ���������Ҫ��sort�������������������--�ȽϹ��������listʹ��sortʱ��Щ���ƣ�����ʹ�ñȽϹ�����бȽ�
	//increas_age--���ն�����ͽ����������У��������ͬʱ��������߽��н�������
	//sort(v1.begin(), v1.end(), increas_age);  //sort(vector.begin(), vector.end(), regular);
	//increas_high--���ն�����߽����������У��������ͬʱ��������ͽ��н�������
	sort(v1.begin(), v1.end(), increas_high);
	showSvector(v1);
	//����������ȽϹ���Ҳ����������list������������
}

//����set��multiset������
//set���ܲ����ظ���Ԫ�أ�multiset���Բ����ظ�Ԫ��
//set��������ʱ�᷵�ز���������ʾ����ɹ�
//multiset���������ݣ���˿��Բ����ظ�����
void test23()
{
	set<int> s;
	//pair��ʾһ������--�����е������ǳɶԳ��ֵģ����һ��Ԫ����һ��set<int>������iterator���ڶ���Ԫ����һ���� s.insert���ص�bool���͵�����
	pair<set<int>::iterator, bool> ret = s.insert(10);
	//��set�У��������һ�����ݵ�ʱ�����᷵��һ�����������������bool���͵ģ���bool=true����ʾ����ɹ����������ʧ�ܡ�
	if (ret.second)
	{
		cout << "��һ��Ԫ�ز���ɹ���" << endl;
	}
	else
	{
		cout << "��һ��Ԫ�ز���ʧ�ܣ�" << endl;
	}
	ret = s.insert(20); //��ʱ��ret.first = ++s.begin()
	if (ret.second)
	{
		cout << "�ڶ���Ԫ�ز���ɹ���" << endl;
	}
	else
	{
		cout << "�ڶ���Ԫ�ز���ʧ�ܣ�" << endl;
	}
	s.insert(30);       //��ʱ��ret.first = ++s.begin(),Ҳ����˵��ʱ��ret����������ָ��s�ĵڶ���Ԫ������λ��
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << endl;
	}
	cout << *ret.first << endl;   //��ʱ��ʾ����s�еڶ���Ԫ������λ��
	ret.first = ++s.begin();      //����൱�ڻ�����ret������ָ��s�ĵڶ���Ԫ������λ�ã��������������һ��
	cout << &ret.first << endl;
}

//multiset����
void test24()
{
	multiset<int> ms;
	ms.insert(10);
	ms.insert(10);
	for (multiset<int>::iterator it = ms.begin(); it != ms.end(); it++)
	{
		cout << *it << " " << endl;
	}
	//�������10�����ʾmultiset������������ظ���ֵ
}

//set��������set�����ڲ�������֮��Ĭ�����������У����������Ҫ�������÷º�����ʵ���������������
//set�����ķ��Զ�������������int,string,double��
class MyCompare
{
public:
	//�º���--����ֵΪbool���ͣ�������()�������еĲ�������ȡ������Ҫ�õ��º����������е���������
	bool operator()(const int& v1, const int& v2) const //����ط�����Ҫ��const�����ڻ���֪��Ϊɶ
	{
		return v1 > v2;
	}
};
void test25()
{
	set<int> s;
	s.insert(10);
	s.insert(50);
	s.insert(30);
	s.insert(20);
	s.insert(40);
	//set����Ĭ������
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << endl;
	}

	//���set�е�Ԫ�ؽ��н�������
	//����setһ��������û�취�����������������˱����ڴ���ʱ����Ĭ��������򣬸��ķ��������������м���һ���º�������
	set<int, MyCompare> s1;
	s1.insert(10);
	s1.insert(50);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);
	for (set<int, MyCompare>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		cout << *it << endl;
	}
}
//set�������Զ�������������class��
//���ȴ���һ��person����
class person_set
{
public:
	person_set(int age, string name)
	{
		this->s_age = age;
		this->s_name = name;
	}
	int s_age;
	string s_name;
};
//�º���
class comparePersonset
{
public:
	bool operator()(const person_set& p1, const person_set& p2)const
	{
		//����person_set�еĶ�����������н�������
		return p1.s_age > p2.s_age;
	}
};
void test26()
{
	//�����Զ�����������Ͷ���Ҫָ���������
	set<person_set, comparePersonset> s;
	person_set p1(18, "Tom");
	person_set p2(19, "Hirry");
	person_set p3(16, "Tomas");
	s.insert(p1);
	s.insert(p2);
	s.insert(p3);

	for (set<person_set, comparePersonset>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << (*it).s_age << endl;
	}

}

//����---pair
//���ִ�����ʽ
//1��pair<type, type> p (value1, value2);
//2��pair<type, type> p = make_pair(value1, value2);
void test27()
{
	//��һ�ִ�����ʽ
	pair<string, int> p("Tom", 18);
	cout << "������" << p.first << " ��ͣ�" << p.second << endl;

	//�ڶ��ִ�����ʽ
	pair<string, int> p1 = make_pair("Jiry", 19);
	cout << "������" << p1.first << " ��ͣ�" << p1.second << endl;
}

//map/multimap����--map�������������ظ�Ԫ�أ�multimap���������ظ�Ԫ��
//map�е�����Ԫ�ض��Ƕ���(pair)��pair�еĵ�һ��Ԫ��Ϊ��ֵ(key)�����������ã��ڶ���Ԫ��Ϊʵֵ(value)
//�������뵽map�е�����Ԫ�ض������� key �Զ�����
void printfMap(const map<int, int>& m)
{
	for (map<int, int>::const_iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key: " << (*it).first << "  value:" << it->second << endl; //ע�⣬key��value�������ʽ���Ի��ã�
		//����һ�������ʽ��������key��value�ϣ����������������ַ���ֻ��Ϊ��˵������ķ�ʽ�����֡�
	}
	cout << endl;
}
void test28()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 10)); //��insert��map�����������ݲ���ʱ��ֻ��ʹ��������pair--û�����ƵĶ���
	m.insert(pair<int, int>(3, 30)); //pair�е�key��value�����ͱ�����mapһ��
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(5, 50));
	//���
	printfMap(m);

	//��������
	map<int, int> m1(m);
	//���
	cout << "�������죺" << endl;
	printfMap(m1);

	//��ֵ����
	map<int, int> m2;
	m2 = m;
	//���
	cout << "��ֵ���죺" << endl;
	printfMap(m2);
}

//map�����Ĵ�С�뽻��
void test29()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 10)); 
	m.insert(pair<int, int>(3, 30)); 
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(5, 50));

	if (m.empty())
	{
		cout << "map����Ϊ�գ�" << endl;
	}
	else
	{
		cout << "map������Ϊ�գ�" << endl;
		cout << "map�����Ĵ�СΪ��" << m.size() << endl;
	}

	//����
	map<int, int> m1(m);
	//Ϊ������m1��m����m1�ж����һ��Ԫ��
	m1.insert(pair<int, int>(7, 80));
	m.swap(m1);
	cout << "������� m��" << endl;
	printfMap(m);
	cout << "������� m1��" << endl;
	printfMap(m1);
}

//map�����Ĳ�����ɾ��
void test30() 
{
	//map���������ֲ���
	map<int, int> m;
	//1��insert(pair<type, type>)
	m.insert(pair<int, int>(1, 10));
	//2��insert(make_pair<type, type>)
	m.insert(make_pair<int, int>(3, 30));
	//3��map<type, type>::value_type
	m.insert(map<int, int>::value_type(2, 20));
	//4��map[key]
	m[4] = 40;

	//��ʾ���
	printfMap(m);

	//ɾ��
	//1��m.erase(key)
	//����value��Ч
	m.erase(3);
	printfMap(m);
	//2��m.erase(pos)
	m.erase(++m.begin());
	printfMap(m);
	
	//���
	m.erase(m.begin(), m.end());
	m.clear();
}
//map���Һ�ͳ��
//������ͳ�ƶ���ͨ��keyֵ�����еģ�����valueֵ����Ч��
void test31()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(3, 30));
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(5, 50));
	//���ң�����key������һ��������
	map<int, int>::iterator it = m.find(4);
	if (it != m.end())
	{
		cout << "���ҵ���Ԫ�أ�" << it->second << endl;
	}
	else
	{
		cout << "δ���ҵ���Ԫ�أ�" << endl;
	}
	//ͳ�ƣ�����key����һ������ֵ
	int num = m.count(3);
	cout << num << endl;
}

//map������,Ĭ��Ϊ����
//�������������setһ�����ڴ���map����ʱ���趨�Զ������
class compareMap //�º������º��������غ�������Ĳ�������ȡ���������д洢����������
{
public:
	bool operator()(int m1, int m2) const
	{
		return m1 > m2;
	}
};
class person_map
{
public:
	person_map(int age, string name, string sex)
	{
		this->m_age = age;
		this->m_name = name;
		this->m_sex = sex;
	}
	int m_age;
	string m_name;
	string m_sex;
};

//�º���
class compareMap1
{
public:
	const bool operator()(const person_map& p1, const person_map& p2) const
	{
		//����person_set�еĶ�����������н�������
		return p1.m_age > p2.m_age;
	}
};


void test32()
{
	//���Զ���������������
	map<int, int , compareMap> m;
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(3, 30));
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(5, 50));

	for (map<int, int, compareMap>::const_iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key: " << (*it).first << "  value:" << it->second << endl; 
	}
	cout << endl;

	//�Զ���������������
	//��map���������Զ����������͵��Զ�������ʱ����Ҫע��һ�㣬������Ĭ�ϵ���������ʱ����keyֵ���������ԣ��������Զ����������ʱ�����Ƿº����е�����һ����Ҫ��map�����е�keyֵ����һ��,���ԣ������ڴ���map����ʱ,��Ҫ�������Զ������������д�������������趨Ϊ���ǵ�keyֵ���͡�����������İ����У������ڴ����Զ�����������(�º���)ʱ�����Ǵ����������Ϊperson_map����������ڴ���map����ʱ��keyֵ����Ҳ�趨Ϊpersong_map��
	// const bool operator()(const person_map& p1, const person_map& p2) const
	// map<person_map, int, compareMap1> m1;
	//������ǽ�person_map�趨Ϊ�º�������������ͣ�keyֵ������Ϊ����,valueֵ������Ϊperson_map--( map<int, person_map, compareMap1> m1; )����ô�����ڱ���ʱ����ֱ���const person_map & �޷�ת��Ϊ keyֵ������(KTY)(int)��
	map<person_map, int, compareMap1> m1;
	person_map p1(20, "����", "��");
	person_map p2(24, "����", "��");
	person_map p3(18, "����", "��");
	person_map p4(22, "����", "��");
	
	m1.insert(pair<person_map, int>(p1, 100));
	m1.insert(pair<person_map, int>(p2, 10));
	m1.insert(pair<person_map, int>(p3, 1000));
	m1.insert(pair<person_map, int>(p4, 10000));

	for (map<person_map, int, compareMap1>::const_iterator it = m1.begin(); it != m1.end(); it++)
	{
		cout << "key: " << "��ͣ�" << (*it).first.m_age << " ������" << (*it).first.m_name << " �Ա�" << (*it).first.m_sex << "  value:" << (*it).second << endl;
	}
	cout << endl;
}

//����--Ա������
//��10��Ա��(ABCDEFGHIJ)���䵽3������(�߻����������з�)
//Ա����Ϣ������������

#define �з� 0
#define ���� 1
#define �߻� 2

//����һ��Ա����
class person_emp
{
public:
	person_emp(string name, int salary, int age)
	{
		this->p_name = name;
		this->p_salary = salary;
		this->p_age = age;
	}
	string p_name;
	int p_salary;
	int p_age;
};

//����Ա������
void creatEmp(multimap<int, person_emp>&m,int num_emp)
{
	string name = "ABCDEFGHIJ";
	srand((unsigned)time(NULL));
	for (int i = 0; i < num_emp; i++)
	{
		int salary = 0;
		int age = 0;
		int flag = 0;
		//�������2000-5000֮��Ĺ��ʺ�20-25�����
		salary = (int)rand() % 3000 + 2000;
		age = (int)rand() % 5 + 20;
		flag = (int)rand() % 3;
		string name1 = "Ա����";
		name1 = name1 + name[i];
		person_emp p(name1, salary, age);
		//����Ա������multimap�����У�������ȫ����Ϊ�գ��ȴ���������
		m.insert(pair<int, person_emp>(flag, p));
	}
}

//��ʾ������Ա��
void showOccupaEmp(multimap<int, person_emp>& m)
{
	int num_yanfa = 0;
	int num_meishu = 0;
	int num_cehua = 0;
	int index0 = 0;
	int index1 = 0;
	int index2 = 0;

	//ͳ�Ƹ�����Ա������
	num_yanfa = m.count(0);
	num_meishu = m.count(1);
	num_cehua = m.count(2);
	//��ʾ������Ա��
	cout << "�з����ţ�" << endl;
	for (multimap<int, person_emp>::iterator it = m.find(0); index0 < num_yanfa; index0++, it++)
	{
		cout << "������" << (*it).second.p_name << " ��ͣ�" << (*it).second.p_age << " ���ʣ�" << (*it).second.p_salary << endl;
	}
	cout << "--------------------------------" << endl;
	cout << "�������ţ�" << endl;
	for (multimap<int, person_emp>::iterator it = m.find(1); index1 < num_meishu; index1++, it++)
	{
		cout << "������" << (*it).second.p_name << " ��ͣ�" << (*it).second.p_age << " ���ʣ�" << (*it).second.p_salary << endl;
	}
	cout << "--------------------------------" << endl;
	cout << "�߻����ţ�" << endl;
	for (multimap<int, person_emp>::iterator it = m.find(2); index2 < num_cehua; index2++, it++)
	{
		cout << "������" << (*it).second.p_name << " ��ͣ�" << (*it).second.p_age << " ���ʣ�" << (*it).second.p_salary << endl;
	}
}
void test33()
{
	//�������Ǵ�����ʱ����Ա����Ϊkeyֵ�����Բ���Ҫ�������ظ�Ԫ�أ�����ʹ��map��������Ȼ���Է���һ�������ʹ��multimap
	multimap<int, person_emp> m;
	//����Ա�����󣬲�����multimap������
	creatEmp(m, 10);
	//��ʾԱ����Ϣ
	for (multimap<int, person_emp>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "������" << (*it).second.p_name << " ��ͣ�" << (*it).second.p_age << " ���ʣ�" << (*it).second.p_salary << " ���ţ�" << (*it).first << endl;
	}
	cout << endl;
	showOccupaEmp(m);
}

//��������---���غ������ò����� () ���࣬����󳣳�Ϊ��������
//��������ʹ������ () ʱ����Ϊ���ƺ������ã����Ҳ�зº���
//����������ʹ��ʱ��������ͨ�����������ã������в����������з���ֵ
//�������󳬳���ͨ�����ĸ����������������Լ���״̬
//�������������Ϊ��������
class fun_Printf
{
public:
	int operator()(int v1, int v2)
	{
		return v1 + v2;
	}
};

class fun_Printf1
{
public:
	fun_Printf1()
	{
		count = 0;
	}
	void operator() (string test)
	{
		cout << test << endl;
		count++;
	}
	int count;
};

class fun_Printf2
{
public:
	void operator()()
	{
		cout << "����һ���º�����" << endl;
	}
};
void show_fun_Printf2(fun_Printf2& f)
{
	f();
}
void test34()
{
	//����������ʹ��ʱ��������ͨ�����������ã������в����������з���ֵ
	fun_Printf fp;
	cout << fp(10, 20) << endl;
	//�������󳬳���ͨ�����ĸ����������������Լ���״̬
	fun_Printf1 fp1;
	fp1("Hello world!");
	cout << fp1.count << endl;
	//�������������Ϊ��������
	fun_Printf2 f;
	show_fun_Printf2(f);
}

//ν��--����bool���͵ķº���
//����()--operator()()�д������ֻ��һ��ʱ����ΪһԪν�ʣ��������Ϊ����ʱ����Ϊ��Ԫν��
//һԪν��--onePredicate
class onePredicate
{
public:
	bool operator()(int value)
	{
		if (value >= 0)
		{
			return true;

		}
		else
		{
			return false;
		}
	}
};
void test35()
{
	onePredicate op1;
	//bool����ת��Ϊint���ֱ��Ӧtrue--1,false--0
	cout << op1(2) << endl;
	cout << op1(-2) << endl;
}
//��Ԫν��--һ�����list��map���������������ʱ���õ�����ϸ�����ɲο������ map ��������


//�����º���--ʵ����������,������STL�У������Щ�º���ȫ������ģ�壬���ҵ�����Щ�º�������Ҫ����ͷ�ļ�#include <functional>
//����negate��һԪ����(ȡ���º�����ȡ����ʵ����ʵ���� �����ȥ��������ֵ)���������Ƕ�Ԫ����
void test36()
{
	//negate��һ����ģ��
	negate<int> n;
	n(20);
	cout << n(20) << endl;
	//plus--��Ԫ�������ģ��
	plus<int> p;
	p(10, 20);
	cout << p(10, 20) << endl;
}

//��ϵ�º���--ʵ�ֹ�ϵ�Ա�,������STL��
//�º���
class vgreater
{
public:
	bool operator()(int v1, int v2)
	{
		return v1 > v2;
	}
};

void test37()
{
	//����--greater
	vector<int> v;
	v.push_back(10);
	v.push_back(40);
	v.push_back(30);
	v.push_back(20);
	//��ʾvector��������
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
	//��������
	sort(v.begin(), v.end());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
	//�Լ������º�����ƽ������й���
	//sort(v.begin(), v.end(), vgreater());
	//for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	//{
	//	cout << *it << endl;
	//}
	//cout << endl;
	//����greater����ƽ������й���
	sort(v.begin(), v.end(), greater<int>());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
}

//�߼��º���--ʵ���߼�����---template<class T> bool logical_and<T> ;bool logical_or<T> ;bool logical_not<T>
void test38()
{
	//�߼���--bool logical_not<T>
	vector<bool> v;
	v.push_back(true);
	v.push_back(false);
	v.push_back(true);
	v.push_back(false);
	//��ʾ
	for (vector<bool>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
	//�����߼��ǽ���ȡ�����������ҽ�ȡ�����ֵ�����µ�����v2��
	vector<bool> v2;
	//���·���ռ�
	v2.resize(v.size());
	//���˺���--transform�����˵�������Сһ��ҪС�ڵ����µĴ洢�ռ�
	transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());
	for (vector<bool>::iterator it = v2.begin(); it != v2.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
}

//�����㷨--for_each
void print01(int value)
{
	cout << value << " ";
}

class print02
{
public:
	void operator()(int value)
	{
		cout << value << " ";
	}
};
void test39() 
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//for_each(v.begin(), v.end(), print01);
	for_each(v.begin(), v.end(), print02());//print02()�Ƿº����ഴ����ʵ��--��������
}

//�����㷨
class vector_predeitor //��������������
{
public:
	bool operator()(int value)
	{
		return value > 0;
	}
};
class person_find
{
public:
	person_find(string name, int salary, int age)
	{
		this->p_name = name;
		this->p_salary = salary;
		this->p_age = age;
	}
	//����== ʹ�õײ�find֪����ζԱ�person_find��������
	bool operator==(const person_find& p)
	{
		if (this->p_name == p.p_name && this->p_salary == p.p_salary && this->p_age == p.p_age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string p_name;
	int p_salary;
	int p_age;
};

class findagegreater20
{
public:
	bool operator()(const person_find& pf)
	{
		if (pf.p_age > 20)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
class numberGreater10
{
public:
	bool operator()(int value)
	{
		return value > 10;
	}
};
void test40()
{
	vector<int> v;
	vector<int>::iterator it;
	v.push_back(-10);
	v.push_back(-40);
	v.push_back(30);
	v.push_back(20);
	v.push_back(20);

	vector<person_find> v2;
	vector<person_find>::const_iterator it1;
	person_find p1("����", 1000, 20);
	person_find p2("����", 2000, 30);
	person_find p3("����", 3000, 40);
	v2.push_back(p1);
	v2.push_back(p2);
	v2.push_back(p3);
	person_find p4("����", 3000, 40);


	//find--����Ԫ��
	//�����������Ͳ���---int\stirng\double...
	it = find(v.begin(), v.end(), 20);
	cout << "find����������������: " << *it << endl;
	//�Զ����������Ͳ���---class����Ҫ����class�е�==
	it1 = find(v2.begin(), v2.end(), p4);
	cout << "find�����Զ�����������: " << (*it1).p_name << " " << (*it1).p_salary << " " << (*it1).p_age << endl;
	//find_if--����������Ԫ�� find_if(iterator beg, iterator end, _pred)
	//beg ��ʼ��������end ������������ _pred ��������ν��(����bool���͵ķº���)
	it = find_if(v.begin(), v.end(), vector_predeitor());
	cout << "find_if����������������: " << *it << endl;
	//�����Զ�����������
	it1 = find_if(v2.begin(), v2.end(), findagegreater20());
	cout << "find_if�����Զ�����������: " << (*it1).p_name << " " << (*it1).p_salary << " " << (*it1).p_age << endl;
	//adjacent_find--���������ظ�Ԫ��
	it = adjacent_find(v.begin(), v.end());
	cout << "adjacent_find: " << *it << endl;
	//binary_search--���ֲ��ҷ�������ָ��Ԫ�أ��ҵ�����true�����߷���false��������������������в�����
	//������vector�������У���Ҫʹ��binary_search����Ҫ�ȶ�������������
	sort(v.begin(), v.end());
	bool flag;
	flag = binary_search(v.begin(), v.end(), 20);
	cout << "binary_search: " << flag << endl;
	//count--ͳ��Ԫ�ظ���
	int num = 0;
	num = count(v.begin(), v.end(), -30);
	cout << "ͳ��������������Ԫ�ظ���: " << num << endl;
	//ͳ���Զ�����������Ԫ�ظ����������find�����Զ�����������һ������Ҫ�������е�==�š�
	num = count(v2.begin(), v2.end(), p4);
	cout << "ͳ���Զ�����������Ԫ�ظ���: " << num << endl;
	//count_if--������ͳ��Ԫ�ظ�����count_if(iterator beg, iterator end, _pred)
	int num_if1 = 0, num_if2 = 0;
	//ͳ��������������
	num_if1 = count_if(v.begin(), v.end(), numberGreater10());
	cout << "ͳ��������������Ԫ�ظ���: " << num_if1 << endl;
	//ͳ���Զ�����������
	num_if2 = count_if(v2.begin(), v2.end(), findagegreater20());
	cout << "ͳ���Զ�����������Ԫ�ظ���: " << num_if2 << endl;
}

//�����㷨--sort��random_shuffle��merge��reverse
void showvector_int(const vector<int>& v)
{
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

class myorder
{
public:
	bool operator()(int v1, int v2)
	{
		return v1 > v2;
	}
};

void test41()
{
	vector<int> v;
	vector<int>::iterator it;
	v.push_back(-10);
	v.push_back(-40);
	v.push_back(30);
	v.push_back(20);
	v.push_back(20);

	//random_shuffle--ָ����Χ�ڵ�Ԫ��˳���������
	srand((unsigned int)time(NULL));
	random_shuffle(v.begin(), v.end());
	cout << "random_shuffle--ָ����Χ�ڵ�Ԫ��˳���������: " << endl;
	showvector_int(v);

	//sort��������
	sort(v.begin(), v.end());
	cout << "sort��������: " << endl;
	showvector_int(v);
	//sort���н���
	//1�������Զ����������
	//sort(v.begin(), v.end(), delivery);
	//2���������õĺ�������(�º���)
	sort(v.begin(), v.end(), greater<int>());
	cout << "sort--�������õĺ�������(�º���)���н���: " << endl;
	showvector_int(v);

	//merge--����������Ԫ�غϲ�������������һ��������
	//ʹ��merge��ǰ����������������ͬʱ�������򣬻��߶��ǽ���ע�⣬����ʱ��Ҫ�Զ��彵�������������ʹ�����õĺ�������greater
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(100);
	v1.push_back(50);
	v1.push_back(90);
	sort(v1.begin(), v1.end(), greater<int>());
	cout << "����(����)���v1��" << endl;
	showvector_int(v1);

	vector<int> vTarget;
	vTarget.resize(v1.size() + v.size());
	//����
	merge(v1.begin(), v1.end(), v.begin(), v.end(), vTarget.begin(), greater<int>());
	//merge(v1.begin(), v1.end(), v.begin(), v.end(), vTarget.begin(), myorder());
	//����
	//merge(v1.begin(), v1.end(), v.begin(), v.end(), vTarget.begin());

	cout << "merge--ƴ������vector����: " << endl;
	showvector_int(vTarget);

	//reverse--��β��Ԫ�ضԵ�
	reverse(v.begin(), v.end());
	cout << "reverse--��β��Ԫ�ضԵ�: " << endl;
	showvector_int(v);
}

//���ÿ������滻�㷨--copy��replace��replace_if��swap
class valueGreater20
{
public:
	bool operator()(int value)
	{
		return value > 20;
	}
};
void test42()
{
	//copy--copy(iterator beg, iterator end, iterator dest);
	vector<int> v1;
	vector<int> v2;
	v1.push_back(10);
	v1.push_back(100);
	v1.push_back(50);
	v1.push_back(90);
	//copy֮ǰ��Ҫ�ȸ�Ŀ����������ռ�
	v2.resize(v1.size());
	copy(v1.begin(), v1.end(), v2.begin());
	cout << "copy֮���v2��" << endl;
	showvector_int(v2);

	//replace--replace(iterator beg, iterator end, oldvalue, newvalue); ��������ָ����Χ�ڵ�Ԫ���滻Ϊ�µ�Ԫ��
	replace(v2.begin(), v2.end(), 50, 20); //��v2������ͷ����β����Χ�ڵ�����Ԫ��50�滻Ϊ20
	replace(v2.begin() + 2, v2.end(), 10, 30); //��v2������ͷ������ڶ���Ԫ��λ�ÿ�ʼ��β����Χ�ڵ�����Ԫ��10�滻Ϊ30
	cout << "replace֮���v2��" << endl;
	showvector_int(v2);

	//replace_if--replace_if(iterator beg, iterator end, _pred, newvalue); �滻ָ����Χ�ڷ���ν�ʻ��ߺ�������_pred������Ԫ��Ϊ�µ�Ԫ��
	replace_if(v2.begin(), v2.end(), valueGreater20(), 10); //��v2������ͷ����β����Χ�ڵ�����ֵ����20��Ԫ���滻Ϊ10
	cout << "replace_if֮���v2��" << endl;
	showvector_int(v2);

	//swap--swap(container c1, container c2); ������������c1,c2�е�Ԫ��,�������������ͬ���͵�����
	v2.push_back(100);
	swap(v1, v2);
	cout << "�������v1��" << endl;
	showvector_int(v1);
	cout << "�������v2��" << endl;
	showvector_int(v2);
}

//�������������㷨--��Ҫ����ͷ�ļ�#include <numeric>
//��Ҫ���������㷨--accumulate,fill��ǰһ���Ǽ�������Ԫ���ۼ��ܺͣ���һ���������������Ԫ��
void test43()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(100);
	v1.push_back(50);
	v1.push_back(90);

	//accumulate(iterator beg, iterator end, value); ����value����ʼֵ
	int total_num = accumulate(v1.begin(), v1.end(), 1); //�����ͬ�� total_num = 1 + accumulate(v1.begin(), v1.end(), 0)
	cout << "�ۼ�ֵΪ: " << total_num << endl;

	//fill(iterator beg, iterator end, value); �����������ָ����Ԫ��
	fill(v1.begin(), v1.end(), 0);
	showvector_int(v1);
}

//���ü����㷨
//��Ҫ���������㷨--set_intersection��set_union��set_difference���������㷨�ֱ��������������Ľ������������
template <class T>
void myPrint(T value)
{
	cout << value << " ";
}
void test44()
{
	vector<int> v;
	//vector<int>::iterator it;
	v.push_back(-10);
	v.push_back(-40);
	v.push_back(30);
	v.push_back(20);
	v.push_back(20);

	vector<int> v1;
	v1.push_back(20);
	v1.push_back(100);
	v1.push_back(50);
	v1.push_back(90);

	vector<int> vTarget_inter;
	//ΪĿ��������ǰ���ٿռ䣬�ռ��СΪ���������пռ���С����һ���Ŀռ��С
	vTarget_inter.resize(min(v.size(), v1.size()));
	//set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);  ���У�dest��Ŀ�������Ŀ�ʼ������
	//ע�⣬������������������������У���merge��һ����
	sort(v.begin(), v.end());
	sort(v1.begin(), v1.end());
	cout << "v��" << endl;
	showvector_int(v);
	cout << "v1��" << endl;
	showvector_int(v1);
	//set_intersection�᷵�ؽ���������� vTarget_inter �����һ��Ԫ�صĵ�������ַvTarget_inter.end()
	cout << "����v��v1�Ľ������" << endl;
	vector<int>::iterator itEnd_inter = set_intersection(v.begin(), v.end(), v1.begin(), v1.end(), vTarget_inter.begin());
	for_each(vTarget_inter.begin(), itEnd_inter, myPrint<int>);
	cout << endl;

	//set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
	//ע�⣬������������������������У���merge��һ����
	vector<int> vTarget_union;
	vTarget_union.resize(v.size() + v1.size()); 
	//set_union�᷵�ز���������� vTarget_union �����һ��Ԫ�صĵ�������ַvTarget_union.end()
	cout << "����v��v1�Ĳ������" << endl;
	vector<int>::iterator itEnd_union = set_union(v.begin(), v.end(), v1.begin(), v1.end(), vTarget_union.begin());
	for_each(vTarget_union.begin(), itEnd_union, myPrint<int>);
	cout << endl;

	//set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
    //ע�⣬������������������������У���merge��һ����
	vector<int> vTarget_difference1;
	vector<int> vTarget_difference2;
	vTarget_difference1.resize(max(v.size(), v1.size()));
	vTarget_difference2.resize(max(v.size(), v1.size()));
	//��ɾ�����������д��ڵ��ظ�Ԫ��
	vector<int>::iterator it;
	it = unique(v.begin(), v.end());
	v.erase(it);

	cout << "v��v1�Ĳ: " << endl;
	vector<int>::iterator itEnd_difference1 = set_difference(v.begin(), v.end(), v1.begin(), v1.end(), vTarget_difference1.begin());
	for_each(vTarget_difference1.begin(), itEnd_difference1, myPrint<int>);
	cout << endl;

	cout << "v1��v�Ĳ: " << endl;
	vector<int>::iterator itEnd_difference2 = set_difference(v1.begin(), v1.end(), v.begin(), v.end(), vTarget_difference2.begin());
	for_each(vTarget_difference2.begin(), itEnd_difference2, myPrint<int>);
	cout << endl;

}

//����ʵ��--�ݽ�����
class player
{
public:
	player(int id, int age, string name, string sex, double grade)
	{
		this->m_id = id;
		this->m_age = age;
		this->m_name = name;
		this->m_sex = sex;
		this->m_grade = grade;
	}
	int m_id;
	int m_age;
	double m_grade;
	string m_name;
	string m_sex;
};
void createPlayer(vector<player>& py, int num_player)
{
	string name1[] = { "��һ","Ǯ��","����","����","����","����","֣��","����","���", "��ʮ", "��ʮһ", "��ʮ��" };
	string sex1[] = { "��","��","Ů","Ů","Ů","Ů","��","��","Ů", "��", "Ů", "��" };
	srand((unsigned)time(NULL));
	for (int i = 0; i < num_player; i++)
	{
		int id = 10001;
		id = id + i;
		int age = 0;
		age = rand() % 5 + 20;  //20-25
		player p(id, age, name1[i], sex1[i], 0);
		py.push_back(p);
	}
}
void show_player(vector<player>& py)
{
	for (vector<player>::iterator it = py.begin(); it < py.end(); it++)
	{
		cout << "��ţ�" << (*it).m_id << "  ��ͣ�" << (*it).m_age << "  ������" << (*it).m_name << "  �Ա�" << (*it).m_sex << "  �ɼ���" << (*it).m_grade << endl;
	}
	cout << endl;
}


void srandGenerator(int* sra, int rang)
{
	srand((unsigned)time(NULL));
	if(rang>1)
	{
		for (int i = 0; i < rang; i++)
		{
			sra[i] = i + 1;
		}
		for (int i = rang - 1; i > 0; i--)
		{
			swap(sra[i], sra[rand() % i]);
		}
	}
	else
	{
		cout << "rang����Ϊһ������1����������" << endl;
	}
}

//ѡ�ֳ�ǩ
void getOrder(vector<player>& py, multimap<int, player>& m, int num_player)
{
	int *sra = new int [num_player];
	srandGenerator(sra, num_player);
	int i = 0;
	for (vector<player>::iterator it = py.begin(); it != py.end(); it++)
	{
		m.insert(pair<int, player>(sra[i], *it));
		i++;
	}
	delete[] sra;
}

void createGrade(player& p, int num_pingwei)
{
	double grade = 0;
	deque<double>PingWei;
	//�������num_pingweiλ��ί�Ĵ��
	for (int i = 0; i < num_pingwei; i++)
	{
		grade = (rand() % 301 + 700.0) / 10.f;
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

//��дvector�����������

bool player_sort( player& p1, player& p2)
{
	if (p1.m_grade == p2.m_grade)
	{
		return p1.m_grade > p2.m_grade;
	}
	return p1.m_grade > p2.m_grade;
}

//��ѡ�ֽ�������
void giveGrade(multimap<int, player>& m, int num_pingwei)
{
	for (multimap<int, player>::iterator it = m.begin(); it != m.end(); it++)
	{
		createGrade((*it).second, num_pingwei);
		//cout << (*it).first << " " << (*it).second.m_name << " " << (*it).second.m_grade << " ";
		Sleep(1000);
	}
}


void test45()
{
	//��һ��
	vector<player> py;
	vector<player> py1;
	vector<player> py2;

	multimap<int, player> m1;   //��һ�ֵ�һ���ѡ������
	multimap<int, player> m2;   //��һ�ֵڶ����ѡ������
	multimap<int, player> m3;   //�ڶ��ֵ�ѡ������

	
	//����12��ѡ��
	createPlayer(py, 12);
	//show_player(py);
	py1 = py;
	py2 = py;
	//py1ֻȡpy��6λѡ�֣�py2ֻȡpyǰ6λѡ��
	py1.erase(py1.begin() + 6, py1.end());
	py2.erase(py2.begin(), py2.begin() + 6);

	//��һ���ǩ
	getOrder(py1, m1, 6);
	//�ڶ����ǩ
	getOrder(py2, m2, 6);

	//��ί���ɼ�
	giveGrade(m1, 12);
	giveGrade(m2, 12);
	//���py1��py2��׼����������
	py1.clear();
	py2.clear();

	for (multimap<int, player>::iterator it = m1.begin(); it != m1.end(); it++)
	{
		py1.push_back(it->second);
		cout << "��ţ�" << (*it).second.m_id << "  ��ͣ�" << (*it).second.m_age << "  ������" << (*it).second.m_name << "  �Ա�" << (*it).second.m_sex << "  �ɼ���" << (*it).second.m_grade << endl;
	}
	for (multimap<int, player>::iterator it = m2.begin(); it != m2.end(); it++)
	{
		py2.push_back(it->second);
		cout << "��ţ�" << (*it).second.m_id << "  ��ͣ�" << (*it).second.m_age << "  ������" << (*it).second.m_name << "  �Ա�" << (*it).second.m_sex << "  �ɼ���" << (*it).second.m_grade << endl;
	}

	//������ѡ�ְ��ɼ�����
	sort(py1.begin(), py1.end(), player_sort);
	sort(py2.begin(), py2.end(), player_sort);

	vector<player>::iterator it_py1 = py1.begin();
	vector<player>::iterator it_py2 = py2.begin();

	cout << "��һ���е�ǰ�����ֱ��ǣ�" << endl;
	for (; it_py1 != py1.begin() + 3; it_py1++)
	{
		cout << "��ţ�" << (*it_py1).m_id << "  ��ͣ�" << (*it_py1).m_age << "  ������" << (*it_py1).m_name << "  �Ա�" << (*it_py1).m_sex << "  �ɼ���" << (*it_py1).m_grade << endl;
	}

	cout << "����������������������������������������������������������������" << endl;
	cout << "�ڶ����е�ǰ�����ֱ��ǣ�" << endl;
	for (; it_py2 != py2.begin() + 3; it_py2++)
	{
		cout << "��ţ�" << (*it_py2).m_id << "  ��ͣ�" << (*it_py2).m_age << "  ������" << (*it_py2).m_name << "  �Ա�" << (*it_py2).m_sex << "  �ɼ���" << (*it_py2).m_grade << endl;
	}

	//ȡpy1��py2�и��Ե�ǰ��������py
	py.clear();

	for (int i = 0; i < 3; i++)
	{
		py.push_back(*(py1.begin() + i));
		py.push_back(*(py2.begin() + i));
	}
	cout << "����������������������������������������������������������������" << endl;
	cout<< "����ڶ��ֵ�6��ѡ������: " << endl;
	show_player(py);

	//�ڶ���
	//�ڶ��ֳ�ǩ
	getOrder(py, m3, 6);
	//��ί���ɼ�
	giveGrade(m3, 12);
	//���py��׼����������
	py.clear();

	cout << "����������������������������������������������������������������" << endl;
	cout << "6��ѡ�ֵĵڶ��ֳɼ�����: " << endl;
	for (multimap<int, player>::iterator it = m3.begin(); it != m3.end(); it++)
	{
		py.push_back(it->second);
		cout << "��ţ�" << (*it).second.m_id << "  ��ͣ�" << (*it).second.m_age << "  ������" << (*it).second.m_name << "  �Ա�" << (*it).second.m_sex << "  �ɼ���" << (*it).second.m_grade << endl;
	}
	//������ѡ�ְ��ɼ�����
	sort(py.begin(), py.end(), player_sort);
	cout << "����������������������������������������������������������������" << endl;
	cout << "6��ѡ�ֵĵڶ��ֳɼ������" << endl;
	show_player(py);

	vector<player>::iterator it_py = py.begin();
	cout << "����������������������������������������������������������������" << endl;
	cout << "���ĵ�һ�����������ֱ��ǣ�" << endl;
	for (; it_py != py.begin() + 3; it_py++)
	{
		cout << "��ţ�" << (*it_py).m_id << "  ��ͣ�" << (*it_py).m_age << "  ������" << (*it_py).m_name << "  �Ա�" << (*it_py).m_sex << "  �ɼ���" << (*it_py).m_grade << endl;
	}
}

void test46()
{
	playerManager pm;
	pm.num_player1 = 12;
	pm.num_pingwei1 = 12;

	int flag;

	while (1)
	{
		pm.showMenu();
		cout << "����������ʹ�õĹ��ܱ�ţ�";
		cin >> flag;
		switch (flag)
		{
		case 0: pm.exitSystem(); break;
		case 1: pm.startSpeech(); break;
		case 2: pm.findInfo(); break;
		case 3: pm.clearRecord(); break;
		default:
			system("cls");
			break;
		}
	}
}

void exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	system("cls");
	exit(0);
}

void showmenu()
{
	cout << "��ӭʹ�û���ԤԼ����ϵͳ!" << endl;
	cout << "-------------------------" << endl;
	cout << "****** 1��ѧ��ϵͳ ******" << endl;
	cout << "****** 2����ʦϵͳ ******" << endl;
	cout << "***** 3������Աϵͳ *****" << endl;
	cout << "****** 4���˳�ϵͳ ******" << endl;

	cout << "��ѡ����������ϵͳ: " << endl;
}

//����ԤԼ����ϵͳ

void test47()
{
	int choice = 0;  //�û�ѡ��
	personManager* psm = new students;
	personManager* ptm = new teachers;
	personManager* padm = new admirManagers;
	while (true)
	{
		showmenu();
		cin >> choice;
		switch (choice)
		{
		case 1:psm->load(); break;
		case 2:ptm->load(); break;
		case 3:padm->load(); break;
		case 4:exitSystem(); break;
		default:
			system("cls");
			break;
		}
	}
	delete psm;
	psm = NULL;
	delete ptm;
	ptm = NULL;
	delete padm;
	padm = NULL;
}



int main() 
{
	test01();  //����
	//test02();    //����ǰ��++�����,���غ���++�����������<<�����
	//test03();    //����ǰ��==�����,���������
	//test05();    //�̳���ͬ�������ĵ���
	//test06();    //��̬������: 1���м̳й�ϵ��2������Ҫ��д������麯��
	//test07();    //��̬����---������
	//test08();    //��̬����������1������̳в���д����ĺ�����2�������ָ���������ָ������Ķ���
	//test09();    //���麯���������
	//test10();    //��̬����---������װ
	//test11();    //�ļ�д�����ȡ
	//test12();    //�����ƶ�д�ļ�
	//test13();    //����ģ��
	//test14();    //ģ�����̳��Լ����⺯������
	//test16();    //ģ��������Ԫ������ʵ��
	//test17();    //��ģ��
	//test18();    //���� --vector
	//test19();    //����ʵ��: ��ί��֣�5��ѡ��ABCDE��10����ί�����֣�ȥ����ͷֺ���߷֣�ȡƽ��
	//test20();    //��list���и�ֵ�ͽ������鿴��С�������ɾ��
	//test21();    //list������ֵ����ȡ�����ʡ���ת������
	//test22();    //������: ��students�Զ����������ͽ�������student����������������͡����,������ͽ������������ͬʱ�������߽��н�������
	//test23();    //set����
	//test24();    //multiset����
	//test25();    //set�����ķ��Զ�������������int,string,double��
	//test26();    //set�������Զ�������������int,string,double��
	//test27();    //����---pair�����ִ�����ʽ
	//test28();    //����pair��map�������и�ֵ
	//test29();    //map�����Ĵ�С�뽻��
	//test30();    //map�����Ĳ�����ɾ��
	//test31();    //map���Һ�ͳ��
	//test32();    //map������,Ĭ��Ϊ���򣬸������������setһ�����ڴ���map����ʱ���趨�Զ������
	//test33();    //����--Ա�����飬��10��Ա��(ABCDEFGHIJ)���䵽3������(�߻����������з�)
	//test34();    //��������---���غ������ò����� () ���࣬����󳣳�Ϊ��������
	//test35();    //ν��--����bool���͵ķº���
	//test36();    //�����º���--ʵ����������,������STL�У������Щ�º���ȫ������ģ�壬���ҵ�����Щ�º�������Ҫ����ͷ�ļ�#include <functional>
	//test37();    //��ϵ�º���--ʵ�ֹ�ϵ�Ա�,������STL��
	//test38();    //�߼��º���--ʵ���߼�����---template<class T> bool logical_and<T> ;bool logical_or<T> ;bool logical_not<T>
	//test39();    //�����㷨--for_each
	//test40();    //�����㷨
	//test41();    //�����㷨--sort��random_shuffle��merge��reverse
	//test42();    //���ÿ������滻�㷨--copy��replace��replace_if��swap
	//test43();    //��Ҫ���������㷨--accumulate,fill��ǰһ���Ǽ�������Ԫ���ۼ��ܺͣ���һ���������������Ԫ��
	//test44();    //��Ҫ���������㷨--set_intersection��set_union��set_difference���������㷨�ֱ��������������Ľ������������


	//����ʵ��---���ڶ�̬��ְ������ϵͳ
	//WorkerManager adminer;
	////���Դ���
	////worker* emp1 = NULL;
	////emp1 = new employee(1, "����", "��", 18);
	////worker* emp1 = new employee(1, "����", "��", 18);
	////worker* man1 = new Manager(2, "����", "��", 20);
	////worker* bos1 = new Boss(3, "�����", "��", 25);
	//int  choice;
	//while (1)
	//{
	//	adminer.ShowmMenu();
	//	cout << "����������ѡ��";
	//	cin >> choice;
	//	switch (choice)
	//	{
	//	case 0: adminer.ExitSystem(); break;  //0.�˳�����ϵͳ
	//  case 1: adminer.AddWorker(); break;   //1.����ְ����Ϣ
	//	case 2: adminer.ShowWorkers(); break; //2.��ʾְ����Ϣ
	//	case 3: adminer.DeleteWorker(); break;//3.ɾ����ְְ��
	//	case 4: adminer.ModifyWorker(); break;//4.�޸�ְ����Ϣ
	//	case 5: adminer.SearchWorker(); break;   //5.����ְ����Ϣ
	//	case 6: adminer.SortWorker(); break;   //6.���ձ������
    //  case 7: adminer.CleanAllWorker(); break;   //7.��������ĵ�
	//	default:
	//		system("cls");
	//		break;
	//	}
	//}


	//����ʵ��--�ݽ�����
	//�����ݽ���������12�˲μӣ����������֣���һ��Ϊ��̭�����ڶ���Ϊ����
	//ÿ��ѡ�ֶ��б�ţ�10001-10012
	//������ʽ�����������ÿ��6��
	//��һ�ַ�Ϊ���飬ѡ���������ǩ����˳���ݽ�
	//10����ί��ѡ�ִ�֣�ȥ���������ͷ֣�ȡƽ����
	//��һ��ȡÿ��ǰ��������������ڶ���ȡǰ����ʤ������ÿ�ֱ���������Ҫ��ʾ����(���ʤ)��ǰ����ѡ����Ϣ
	//test45();   //�Լ����ģ�û�����ݼ�¼����չ��ܣ��������ı������̶�����ʵ��
	//test46();     //������Ƶ����


	//����ԤԼ����ϵͳ
	//�������������ѧ������ʦ������Ա�������Լ�һ���˳�����
	//ѧ����1������ԤԼ--ѡ�����ڡ�ʱ�Ρ�������1��2��3�ţ������ɼ�¼��2���鿴�ҵ�ԤԼ��3���鿴����ԤԼ��4��ȡ��ԤԼ���ɹ��ĺ���������е�ԤԼ����5��ע����¼
	//��ʦ��1���鿴����ԤԼ--���ڡ�ʱ�Ρ�ѧ�š�ѧ�������������š�ԤԼ״̬��2�����ԤԼ--���ͨ����δͨ����3��ע����¼
	//����Ա��1������˺�--���ѧ���˺ţ�ѧ��ѧ�š����������룩--�����ʦ�˺ţ�ְ���š����������룩��2���鿴�˺�--�鿴��ʦ��ѧ������Ϣ��3���鿴����--��ʾ������ź����������4�����ԤԼ--���ԤԼ�ļ���5��ע����¼
	test47();
	
	system("pause");
	return 0;
}
 