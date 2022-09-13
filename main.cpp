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
#include <algorithm>  //标准算法头文件
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


//重载
//+号运算符重载（operator+）
class person
{
	public:
		int p_m;
		int p_n;
		//1、通过成员函数重载+号
		//person operator+ (person& p)
		//{
		//	person temp;
		//	temp.p_m = this->p_m + p.p_m;
		//	temp.p_n = this->p_n + p.p_n;
		//	return temp;
		//}
		//成员函数重载<<号基本不可用，因为不能实现cout在<<左侧
};
//2、通过全局函数重载+号，对+号的重载只能使用函数名operator+
//person operator+ (person &p1, person &p2)
//{
//	person p3;
//	p3.p_m = p1.p_m + p2.p_m;
//	p3.p_n = p1.p_n + p2.p_n;
//	return p3;
//}


//全局函数重载<<号
//如果operator之前没有取址运算符，并且函数类型设定为void，则不需要return，但是在调用<<时，并不能在结尾使用<<endl，
//这是因为<<重载函数类型被设定为了void，所以不能输出endl。
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
	//重载前置++运算符
public:
	Interl& operator++ ()
	{
		Interl int1;
		int1.num = this->num++;
		return *this;
	}
	//重载后置++运算符
	Interl operator++ (int)
	{
		Interl int1;
		//先记录当前值
		int1 = *this;
		//再递增
		num++;
		//再返回记录值
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
		//先判断是否内存空间已经释放
		if (m_age != NULL)
		{
			delete m_age;
			m_age = NULL;
		}
		//深拷贝
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


//继承中同名函数的调用
class father
{
public:
	static int age; //静态变量，类内声明，类外初始化
	static void test04()
	{
		cout << "父亲的年纪为：" << age << endl;
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
		cout << "儿子的年纪为：" << age << endl;
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


//多态
//多态的条件
//1、有继承关系；2、子类要重写父类的虚函数
//重载和重写的不同在于，重写需要返回类型，函数名，函数参数都是一样的，重载是函数名一致，参数不一样
//多态的作用
//通过对父类的指针或引用来完成对子类的操作，例如下面的dospeak的参数就是引用的父类animal，完成对子类cat的操作。
class animal
{
public:
	virtual void speak()  //虚函数,通过虚函数来完成多态操作，在程序运行之前，地址没有提前绑定，
		//virtual会使程序在运行时进行地址绑定，普通的函数会使程序在运行之前就直接绑定了地址，因此，不论dospeak中
		//传入参数是什么，结果都会是执行“动物在说话”；
	{
		cout << "动物在说话：" << endl;
	}
};
//继承关系
class cat:public animal
{
	//重写父类中的虚函数speak函数
	void speak();
};

void cat::speak()
{
	cout << "猫在说话：" << endl;
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


//多态案例---计算器
//普通方法
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

//使用多态
//多态发生条件：1、子类继承并重写父类的函数；2、父类的指针或者引用指向子类的对象
class abstractcalculator
{
public:
	virtual double getresult()
	{
		return 0;
	}
	double num1, num2;
};
//加法
class addcalculator :public abstractcalculator
{
public:
	double getresult()           //1、子类重写了父类中的函数
	{
		return num1 + num2;
	}
};
//减法
class deletecalculator :public abstractcalculator
{
public:
	double getresult()           //1、子类重写了父类中的函数
	{
		return num1 - num2;
	}
};

void test08()
{
	abstractcalculator* abs = new addcalculator;  //2、父类的指针 *abs指向子类的对象addcalculator,就发生了多态
	abs->num1 = 10;
	abs->num2 = 100;
	cout << abs->getresult() << endl;
	delete abs;
}


//纯虚函数与抽象类
class Base    //抽象类
{
public:
	//纯虚函数
	//只要有一个纯虚函数，这个类就是抽象类
	//1、抽象类是无法实例化对象的；
	//2、抽象类的子类必须重写父类中的纯虚函数，否则也是抽象类；
	virtual void func() = 0;
};

class son2 :public Base 
{
public:
	void func()
	{
		cout << "这不是一个抽象类" << endl;
	}
};

void test09()
{
	son2 s;
	s.func();
}


//多态案例---电脑组装
class CPU  //抽象类
{
public:
	virtual void calculator() = 0;
};
class videocard  //抽象类
{
public:
	virtual void display() = 0;
};
class memory  //抽象类
{
public:
	virtual void storagy() = 0;
};
//子类改写父类虚函数
//Intel
class Intelcpu :public CPU
{
public:
	void calculator()
	{
		cout << "Intel CPU开始工作" << endl;
	}
};

class Intelvideocard :public videocard
{
public:
	void display()
	{
		cout << "Intel videocard开始工作" << endl;
	}
};

class Intelmemory :public memory
{
public:
	void storagy()
	{
		cout<< "Intel memory开始工作" << endl;
	}
};

//Lenovo
class Lenovocpu :public CPU
{
public:
	void calculator()
	{
		cout << "Lenovo CPU开始工作" << endl;
	}
};

class Lenovovideocard :public videocard
{
public:
	void display()
	{
		cout << "Lenovo videocard开始工作" << endl;
	}
};

class Lenovomemory :public memory
{
public:
	void storagy()
	{
		cout << "Lenovo memory开始工作" << endl;
	}
};

//多父类继承
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
	//构造函数,提供三个零件的接口
	computer(CPU* cpu, videocard* vcard, memory* mem)
	{
		m_cpu = cpu;
		m_vcard = vcard;
		m_mem = mem;
	}
	//析构函数
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
	//工作函数
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
	//实例化零件
	CPU* intelcpu = new Intelcpu;
	videocard* vcard = new Intelvideocard;
	memory* mem = new Intelmemory;
	//实例化电脑
	computer* c = new computer(intelcpu, vcard, mem);
	//运行电脑
	c->work();
	delete c;
	//Lenovo
	//实例化零件
	CPU* lenovocpu = new Lenovocpu;
	videocard* lenovovcard = new Lenovovideocard;
	memory* lenovomem = new Lenovomemory;
	//实例化电脑
	computer* c1 = new computer(lenovocpu, lenovovcard, lenovomem);
	//运行电脑
	c1->work();
	delete c1;
}

//文件写入与读取
void test11()
{
	//写入
	//创建流对象
	ofstream file1;
	//指定存放路径、文件名以及写入方式
	file1.open("file1.txt",ios::app);
	//写入内容
	file1 << "救赎之道就在其中" << endl;
	//关闭文件流
	file1.close();

	//读取
    //创建流对象
	ifstream file2;
	//指定打开路径、文件名以及打开方式
	file2.open("file1.txt", ios::in);
	//判断是否打开成功
	if(!file2.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	//读取内容
	//第一种
	//char buf[1024] = { 0 };
	//while (file2 >> buf)
	//{
	//	cout << buf << endl;
	//}
	//第二种
	//char buf[1024] = { 0 };
	//while (file2.getline(buf, sizeof(buf)))
	//{
	//	cout << buf << endl;
	//}
	//第三种，推荐
	string buff;
	while (getline(file2, buff))
	{
		cout << buff << endl;
	}
	//第四种,不推荐
	//char buff;
	//while ((buff = file2.get()) != EOF)
	//{
	//	cout << buff;
	//}
	//关闭文件流
	file2.close();
}

//二进制读写文件
class persong
{
public:
	char name[1024];
	int age;
};
void test12()
{
	persong p = { "张三",18 };
	fstream file3;
	file3.open("person.txt", ios::out | ios::binary);
	file3.write((const char*) &p, sizeof(persong));
	file3.close();

	ifstream file4;
	file4.open("person.txt", ios::in | ios::binary);
	if (!file4.is_open())
	{
		cout << "打开文件失败" << endl;
		return ;
	}
	file4.read((char*)&p, sizeof(persong));
	cout << "姓名："<<p.name << endl;
	cout << "年纪："<<p.age << endl;
	file4.close();
}


//模板
//函数模板
template<typename T>   //这里的T表示一种泛类，表示任意一种数据类型
void mySwap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
	//cout << "函数里面a=" << a << endl;
	//cout << "函数里面b=" << b << endl;
}

void test13()
{
	int a = 10;
	int b = 20;
	//模板的调用方式
	//1、自动类型推断
	//mySwap(a, b);
	//2、显式指定类型
	mySwap<int>(a, b);  //这里的<int>表示由编程者指定T=int类型，这个很像
	//opencv中使用到的constraction（范围限制0~255）中的类型指定
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
}

//模板的类继承以及类外函数定义
template <class T>
class dad1
{
public:
	T name;
};

//模板继承
template <class T1,class T2>
class son1:public dad1<T1>
{
public:
	son1(T1 m_name, T2 m_age);

	T2 age;
	void showInfo();
};
//类外函数定义
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
	son1 <string, int>s2("猪八戒",90);
	s2.showInfo();
}

//将类模板分文件编写---分为.cpp和.h两个文件,当源代码.cpp和头文件.h分开写，类模板中的成员函数的创建发生在调试期间
//并且在主函数中只调用.h文件时
//编译器只会去查看.h，并不会去运行.cpp，所以会产生外部无法解析错误
//解决方法
//1、直接引用.cpp文件
//#include "police.cpp"
//2、将.cpp中的内容写到.h中，将.h改为.hpp，并引用
//#include "police.hpp"
//void test15()
//{
//	police<string, int>p1("石原",24);
//	p1.showInfo();
//}


//模板类中友元函数的实现

//2、类外实现
template<class T1, class T2, class T3>
class policeman;

template<class T1, class T2, class T3>
void showInfo2(policeman<T1, T2, T3> &p)
{
	cout << "类外实现--姓名：" << p.m_name << endl;
}

//1、类内实现
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
	//1、类内声明与实现
	friend void showInfo1(policeman<T1,T2,T3> &p)
	{
		cout << "类内实现--姓名：" << p.m_name << endl;
	}
	//2、类内声明，类外实现
	//加入空模板参数列表
	//如果成员函数是 类外实现，则需要在类前进行声明，让编译器知道
	friend void showInfo2<>(policeman<T1, T2, T3> &p);

	T3 m_sexy;
};

void test16()
{
	//1、类内实现
	policeman<int, string, string>p(18, "peter","男");
	showInfo1(p);

	//2、类外实现
	policeman<int, string, string>p1(18, "joy", "男");
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
//容器 --vector
//存放内置数据类型
void test18()
{
	//创建一个vector容器
	vector<int> v;

	//像容器中插入数据
	//尾插法
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);


	//第一种遍历方式
	//通过迭代器访问容器中的数据
	//vector<int>::iterator itBegin = v.begin();  //起始迭代器，v.begin()指向容器v中的第一个元素
	//vector<int>::iterator itEnd = v.end();  //结束迭代器，v.begin()指向容器v中的最后一个元素的下一个位置

	//while (itBegin != itBegin)
	//{
	//	cout << *itBegin << endl;
	//	itBegin++;
	//}

	//第二种遍历方式
	//for(vector<int>::iterator it = v.begin();it!=v.end();it++)
	//{
	//	cout << *it << endl;
	//}

	//第三种遍历方式，利用STL提供的遍历算法
	for_each (v.begin(),v.end(),myPrint);

}


//案例实现
//评委打分，5名选手ABCDE，10个评委对其打分，去除最低分和最高分，取平均
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
		string name1 = "选手";
		name1 += name[i];
		people p1(name1, 0);
		p.push_back(p1);
	}
}

void test19()
{
	deque<double>PingWei;
	vector<people>xuanshou;

	//创建五个选手，并存入vector容器中
	////第一种方案
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
	//第二种方案
	creatPeople(xuanshou);
	//showvector(xuanshou);

	for (vector<people>::iterator it = xuanshou.begin(); it < xuanshou.end(); it++)
	{
		double fenshu;
		cout << "输入评委分数：";
		for (int de = 0; de < 10; de++)
		{
			cin >> fenshu;
			PingWei.push_front(fenshu);
		}
		cout << "评委打分如下：" << endl;
		showdeque(PingWei);
		//对分数进行排序
		sort(PingWei.begin(), PingWei.end());
		cout << "排序后分数如下：" << endl;
		showdeque(PingWei);
		//去除最高分和最高分，可以用erase，亦可以使用pop_font和pop_back;
		PingWei.erase(PingWei.begin());
		PingWei.erase(PingWei.end()-1);
		cout << "去除最高分与最低分，结果如下：" << endl;
		showdeque(PingWei);
		                         
		for (deque<double>::iterator de1 = PingWei.begin(); de1 < PingWei.end(); de1++)
		{
			(*it).m_score += *de1;
		}
		cout << (*it).m_name << "总分为：" << (*it).m_score << endl;
		(*it).m_score /= PingWei.size();
		cout << (*it).m_name << "的分数为：" << (*it).m_score << endl;
		PingWei.clear();
	}
}

//在c++中stack、queue、priority_queue三种容器都不支持迭代器，不可以遍历

//而list容器是由链表构成的，链表是由节点构成，节点是由两部分构成--数据域与指针域，其中数据域存储的是当前节点的数据，
//而指针域存储了两个指针，分别是指向下一个节点和前一个节点的地址。由于这种特性list容器可以随意插入和删除元素，但是
//由于它所存储数据的地址并不是连续的，且当前节点的读取需要依靠前一个节点中的指针，因此它的读取速度很慢，并且占用空间更大。同时由于它的存储空间不连续，也因此它的迭代器iterator只支持前移与后移，属于双向迭代器，并不能随意读取。
//同时，list比vector好在分配内存时属于按需分配，有多少元素就分配相同的内存空闲，不会分配多余空间。在插入和删除元素时，只会在原有的分配空间中进行，而vector需要重新创立一个新的空间，并且完成数据拷贝和旧空间析构。

//list容器
//对list进行赋值和交换，查看大小，插入和删除
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
	//list赋值
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

	//list交换
	L4.swap(L3);
	//listPrint(L4);
	//listPrint(L3);

	//查看L4是否为空，并查看L4的大小
	if (!L4.empty())
	{
		cout << "L4不为空" << endl;
		listPrint(L4);
		cout << "L4的元素个数为：" << L4.size() << endl;
	}
	else
	{
		cout<< "L4为空" << endl;
	}

	////重新指定大小
	////放大
	//L4.resize(5, 1000);
	//listPrint(L4);
	////缩小
	//L4.resize(2);
	//listPrint(L4);

	//插入和删除
	//listPrint(L4);
	cout << "插入元素后：" << endl;
	//尾插
	L4.push_back(50);
	//头插
	L4.push_front(5);
	listPrint(L4);

	cout << "删除元素后：" << endl;
	//尾删
	L4.pop_back();
	//头删
	L4.pop_front();
	listPrint(L4);

	//插入和删除都是需要利用迭代器进行操作的
	//插入
	list<int>::iterator it = L4.begin();
	//在L4.begin()之后插入1000
	L4.insert(++it, 1000);
	listPrint(L4);

	//删除
	it = L4.begin();
	//删除L4的头部之后的第一个元素
	L4.erase(++it);
	listPrint(L4);

	//移除--remove
	L4.push_back(30);
	L4.remove(30);
	listPrint(L4);

	//清空--clear
	L4.clear();
	listPrint(L4);
}

//list数据存取
bool delivery(int v1, int v2)
{
	return v1 > v2;
}

void test21()
{
	//list赋值
	list<int> L;
	L.push_back(10);
	L.push_back(20);
	L.push_back(30);
	L.push_back(40);

	//访问list中的第一个元素
	//不能使用[]和.at来访问数据
	//对于list容器中的元素访问，只能使用front(),back()或者利用迭代器进行双向迭代器操作（++操作和--操作），不能使用随机迭代器操作（+1，+2等操作），这是因为list不能使用随机迭代器
	cout<<"L中的第一个元素："<<L.front()<<endl;

	cout << "L中的最后一个元素：" << L.back() << endl;

	//反转--reverse
	cout << "反转前：" << endl;
	listPrint(L);
	//反转
	L.reverse();
	cout << "反转后：" << endl;
	listPrint(L);

	//排序--sort
	//对于不能使用随机访问迭代器的容器，其内部会有自带的成员函数来进行排序,即list.sort()，而对于vector等可以使用随机访问迭代器的容器而言，它们的排序是通过使用全局函数sort进行实现的，即sort(vector.begin(), vector.end());
	//升序
	L.sort();
	listPrint(L);
	//降序，对于除升序以外的其他排序方案，不能使用随机访问迭代器的容器,需要设定排序规则，即list.sort(sort regular);
	L.sort(delivery);
	listPrint(L);
}
  

//排序案例
//将students自定义数据类型进行排序，student中属性有姓名、年纪、身高
//排序规则：按照年纪进行升序，年纪相同时按照升高进行降序排序
//首先创建类student
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
		string name1 = "学生";
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

bool increas_age(student s1, student s2)  //按照年纪进行升序排列
{
	if (s1.s_age == s2.s_age)    //如果两个对象的年纪相同，则按照升高进行降序排列
	{
		return s1.s_high > s2.s_high;
	}
	return s1.s_age < s2.s_age;
}

bool increas_high(student s1, student s2)  //按照身高进行升序排列
{
	if (s1.s_high == s2.s_high)    //如果两个对象的身高相同，则按照年纪进行降序排列
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
	//对于可以使用随机访问迭代器的容器，当他们使用sort这个全局函数对容器内的对象进行排序时，不能直接进行排序，需要在sort函数中输入第三个参数--比较规则，这个与list使用sort时有些相似，都是使用比较规则进行比较
	//increas_age--按照对象年纪进行升序排列，当年纪相同时，按照身高进行降序排列
	//sort(v1.begin(), v1.end(), increas_age);  //sort(vector.begin(), vector.end(), regular);
	//increas_high--按照对象身高进行升序排列，当身高相同时，按照年纪进行降序排列
	sort(v1.begin(), v1.end(), increas_high);
	showSvector(v1);
	//上面的两个比较规则也可以适用在list容器的排序中
}

//掌握set与multiset的区别
//set不能插入重复的元素，multiset可以插入重复元素
//set插入数据时会返回插入结果，表示插入成功
//multiset不会检测数据，因此可以插入重复数据
void test23()
{
	set<int> s;
	//pair表示一个对组--即其中的数据是成对出现的，其第一个元素是一个set<int>迭代器iterator，第二个元素是一个由 s.insert返回的bool类型的数据
	pair<set<int>::iterator, bool> ret = s.insert(10);
	//在set中，当其插入一个数据的时候，它会返回一个结果，这个结果就是bool类型的，当bool=true，表示插入成功，否则插入失败。
	if (ret.second)
	{
		cout << "第一次元素插入成功！" << endl;
	}
	else
	{
		cout << "第一次元素插入失败！" << endl;
	}
	ret = s.insert(20); //这时的ret.first = ++s.begin()
	if (ret.second)
	{
		cout << "第二次元素插入成功！" << endl;
	}
	else
	{
		cout << "第二次元素插入失败！" << endl;
	}
	s.insert(30);       //这时的ret.first = ++s.begin(),也就是说这时的ret迭代器还是指向s的第二个元素所在位置
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << endl;
	}
	cout << *ret.first << endl;   //这时显示的是s中第二个元素所在位置
	ret.first = ++s.begin();      //这个相当于还是让ret迭代器指向s的第二个元素所在位置，因此两次输出结果一样
	cout << &ret.first << endl;
}

//multiset容器
void test24()
{
	multiset<int> ms;
	ms.insert(10);
	ms.insert(10);
	for (multiset<int>::iterator it = ms.begin(); it != ms.end(); it++)
	{
		cout << *it << " " << endl;
	}
	//输出两个10，这表示multiset允许插入两个重复的值
}

//set容器排序，set容器在插入数据之后默认是升序排列，因此我们需要掌握利用仿函数来实现其他规则的排序
//set容器的非自定义数据排序，如int,string,double等
class MyCompare
{
public:
	//仿函数--返回值为bool类型，且重载()。而其中的参数类型取决于需要用到仿函数的容器中的数据类型
	bool operator()(const int& v1, const int& v2) const //这个地方后面要加const，现在还不知道为啥
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
	//set容器默认排序
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << endl;
	}

	//设计set中的元素进行降序排列
	//由于set一旦创建就没办法更改它的排序规则，因此必须在创建时更改默认排序规则，更改方法就是在类型中加入一个仿函数类型
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
//set容器的自定义数据排序，如class等
//首先创造一个person类型
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
//仿函数
class comparePersonset
{
public:
	bool operator()(const person_set& p1, const person_set& p2)const
	{
		//按照person_set中的对象年纪来进行降序排列
		return p1.s_age > p2.s_age;
	}
};
void test26()
{
	//对于自定义的数据类型都需要指定排序规则
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

//对组---pair
//两种创建方式
//1、pair<type, type> p (value1, value2);
//2、pair<type, type> p = make_pair(value1, value2);
void test27()
{
	//第一种创建方式
	pair<string, int> p("Tom", 18);
	cout << "姓名：" << p.first << " 年纪：" << p.second << endl;

	//第二种创建方式
	pair<string, int> p1 = make_pair("Jiry", 19);
	cout << "姓名：" << p1.first << " 年纪：" << p1.second << endl;
}

//map/multimap容器--map容器不允许有重复元素，multimap中允许有重复元素
//map中的所有元素都是对组(pair)，pair中的第一个元素为键值(key)，起到索引作用，第二个元素为实值(value)
//并且输入到map中的所有元素都会依据 key 自动排序
void printfMap(const map<int, int>& m)
{
	for (map<int, int>::const_iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key: " << (*it).first << "  value:" << it->second << endl; //注意，key和value的输出方式可以互用，
		//即任一种输出方式都能用在key和value上，这里我们利用两种方法只是为了说明输出的方式有两种。
	}
	cout << endl;
}
void test28()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 10)); //用insert对map容器进行数据插入时，只能使用匿名的pair--没有名称的对组
	m.insert(pair<int, int>(3, 30)); //pair中的key和value的类型必须与map一致
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(5, 50));
	//输出
	printfMap(m);

	//拷贝构造
	map<int, int> m1(m);
	//输出
	cout << "拷贝构造：" << endl;
	printfMap(m1);

	//赋值构造
	map<int, int> m2;
	m2 = m;
	//输出
	cout << "赋值构造：" << endl;
	printfMap(m2);
}

//map容器的大小与交换
void test29()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 10)); 
	m.insert(pair<int, int>(3, 30)); 
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(5, 50));

	if (m.empty())
	{
		cout << "map容器为空！" << endl;
	}
	else
	{
		cout << "map容器不为空！" << endl;
		cout << "map容器的大小为：" << m.size() << endl;
	}

	//交换
	map<int, int> m1(m);
	//为了区别m1与m，在m1中多插入一个元素
	m1.insert(pair<int, int>(7, 80));
	m.swap(m1);
	cout << "交换后的 m：" << endl;
	printfMap(m);
	cout << "交换后的 m1：" << endl;
	printfMap(m1);
}

//map容器的插入与删除
void test30() 
{
	//map容器的四种插入
	map<int, int> m;
	//1、insert(pair<type, type>)
	m.insert(pair<int, int>(1, 10));
	//2、insert(make_pair<type, type>)
	m.insert(make_pair<int, int>(3, 30));
	//3、map<type, type>::value_type
	m.insert(map<int, int>::value_type(2, 20));
	//4、map[key]
	m[4] = 40;

	//显示输出
	printfMap(m);

	//删除
	//1、m.erase(key)
	//传入value无效
	m.erase(3);
	printfMap(m);
	//2、m.erase(pos)
	m.erase(++m.begin());
	printfMap(m);
	
	//清空
	m.erase(m.begin(), m.end());
	m.clear();
}
//map查找和统计
//查找与统计都是通过key值来运行的，传入value值是无效的
void test31()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(3, 30));
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(5, 50));
	//查找，输入key来返回一个迭代器
	map<int, int>::iterator it = m.find(4);
	if (it != m.end())
	{
		cout << "查找到该元素：" << it->second << endl;
	}
	else
	{
		cout << "未查找到该元素：" << endl;
	}
	//统计，输入key返回一个整型值
	int num = m.count(3);
	cout << num << endl;
}

//map的排序,默认为升序
//更改排序规则与set一样，在创建map容器时就设定自定义规则
class compareMap //仿函数，仿函数中重载函数传入的参数类型取决于容器中存储的数据类型
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

//仿函数
class compareMap1
{
public:
	const bool operator()(const person_map& p1, const person_map& p2) const
	{
		//按照person_set中的对象年纪来进行降序排列
		return p1.m_age > p2.m_age;
	}
};


void test32()
{
	//非自定义数据类型排序
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

	//自定义数据类型排序
	//对map容器进行自定义数据类型的自定义排序时，需要注意一点，编译器默认的排序依据时根据key值来排序，所以，当我们自定义排序规则时，我们仿函数中的类型一定是要和map容器中的key值类型一致,所以，我们在创建map容器时,需要将我们自定义的排序规则中传入参数的类型设定为我们的key值类型。比如在下面的案例中，我们在创建自定义的排序规则(仿函数)时，我们传入参数类型为person_map，因此我们在创建map对象时，key值类型也设定为persong_map。
	// const bool operator()(const person_map& p1, const person_map& p2) const
	// map<person_map, int, compareMap1> m1;
	//如果我们将person_map设定为仿函数传入参数类型，key值类型设为整型,value值类型设为person_map--( map<int, person_map, compareMap1> m1; )，那么我们在编译时会出现报错：const person_map & 无法转换为 key值的类型(KTY)(int)。
	map<person_map, int, compareMap1> m1;
	person_map p1(20, "张三", "男");
	person_map p2(24, "李四", "男");
	person_map p3(18, "王五", "男");
	person_map p4(22, "刘八", "男");
	
	m1.insert(pair<person_map, int>(p1, 100));
	m1.insert(pair<person_map, int>(p2, 10));
	m1.insert(pair<person_map, int>(p3, 1000));
	m1.insert(pair<person_map, int>(p4, 10000));

	for (map<person_map, int, compareMap1>::const_iterator it = m1.begin(); it != m1.end(); it++)
	{
		cout << "key: " << "年纪：" << (*it).first.m_age << " 姓名：" << (*it).first.m_name << " 性别：" << (*it).first.m_sex << "  value:" << (*it).second << endl;
	}
	cout << endl;
}

//案例--员工分组
//将10个员工(ABCDEFGHIJ)分配到3个部门(策划、美术、研发)
//员工信息：姓名、工资

#define 研发 0
#define 美术 1
#define 策划 2

//创建一个员工类
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

//创建员工对象
void creatEmp(multimap<int, person_emp>&m,int num_emp)
{
	string name = "ABCDEFGHIJ";
	srand((unsigned)time(NULL));
	for (int i = 0; i < num_emp; i++)
	{
		int salary = 0;
		int age = 0;
		int flag = 0;
		//随机创建2000-5000之间的工资和20-25的年纪
		salary = (int)rand() % 3000 + 2000;
		age = (int)rand() % 5 + 20;
		flag = (int)rand() % 3;
		string name1 = "员工：";
		name1 = name1 + name[i];
		person_emp p(name1, salary, age);
		//插入员工对象到multimap容器中，将部门全部设为空，等待后续输入
		m.insert(pair<int, person_emp>(flag, p));
	}
}

//显示各部门员工
void showOccupaEmp(multimap<int, person_emp>& m)
{
	int num_yanfa = 0;
	int num_meishu = 0;
	int num_cehua = 0;
	int index0 = 0;
	int index1 = 0;
	int index2 = 0;

	//统计各部门员工总数
	num_yanfa = m.count(0);
	num_meishu = m.count(1);
	num_cehua = m.count(2);
	//显示各部门员工
	cout << "研发部门：" << endl;
	for (multimap<int, person_emp>::iterator it = m.find(0); index0 < num_yanfa; index0++, it++)
	{
		cout << "姓名：" << (*it).second.p_name << " 年纪：" << (*it).second.p_age << " 工资：" << (*it).second.p_salary << endl;
	}
	cout << "--------------------------------" << endl;
	cout << "美术部门：" << endl;
	for (multimap<int, person_emp>::iterator it = m.find(1); index1 < num_meishu; index1++, it++)
	{
		cout << "姓名：" << (*it).second.p_name << " 年纪：" << (*it).second.p_age << " 工资：" << (*it).second.p_salary << endl;
	}
	cout << "--------------------------------" << endl;
	cout << "策划部门：" << endl;
	for (multimap<int, person_emp>::iterator it = m.find(2); index2 < num_cehua; index2++, it++)
	{
		cout << "姓名：" << (*it).second.p_name << " 年纪：" << (*it).second.p_age << " 工资：" << (*it).second.p_salary << endl;
	}
}
void test33()
{
	//由于我们创建的时候以员工类为key值，所以不需要害怕有重复元素，可以使用map容器，当然，以防万一，亦可以使用multimap
	multimap<int, person_emp> m;
	//创建员工对象，并放入multimap容器中
	creatEmp(m, 10);
	//显示员工信息
	for (multimap<int, person_emp>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "姓名：" << (*it).second.p_name << " 年纪：" << (*it).second.p_age << " 工资：" << (*it).second.p_salary << " 部门：" << (*it).first << endl;
	}
	cout << endl;
	showOccupaEmp(m);
}

//函数对象---重载函数调用操作符 () 的类，其对象常称为函数对象
//函数对象使用重载 () 时，行为类似函数调用，因此也叫仿函数
//函数对象在使用时可以像普通函数那样调用，可以有参数，可以有返回值
//函数对象超出普通函数的概念，函数对象可以有自己的状态
//函数对象可以作为参数传递
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
		cout << "这是一个仿函数！" << endl;
	}
};
void show_fun_Printf2(fun_Printf2& f)
{
	f();
}
void test34()
{
	//函数对象在使用时可以像普通函数那样调用，可以有参数，可以有返回值
	fun_Printf fp;
	cout << fp(10, 20) << endl;
	//函数对象超出普通函数的概念，函数对象可以有自己的状态
	fun_Printf1 fp1;
	fp1("Hello world!");
	cout << fp1.count << endl;
	//函数对象可以作为参数传递
	fun_Printf2 f;
	show_fun_Printf2(f);
}

//谓词--返回bool类型的仿函数
//重载()--operator()()中传入参数只有一个时，称为一元谓词，传入参数为两个时，成为二元谓词
//一元谓词--onePredicate
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
	//bool类型转换为int，分别对应true--1,false--0
	cout << op1(2) << endl;
	cout << op1(-2) << endl;
}
//二元谓词--一般更改list、map等容器的排序规则时会用到，详细案例可参考上面的 map 容器排序


//算数仿函数--实现四则运算,包含在STL中，因此这些仿函数全都是类模板，并且调用这些仿函数还需要引用头文件#include <functional>
//其中negate是一元运算(取反仿函数，取反的实质其实就是 自身减去两倍自身值)，其他都是二元运算
void test36()
{
	//negate是一个类模板
	negate<int> n;
	n(20);
	cout << n(20) << endl;
	//plus--二元运算的类模板
	plus<int> p;
	p(10, 20);
	cout << p(10, 20) << endl;
}

//关系仿函数--实现关系对比,包含在STL中
//仿函数
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
	//大于--greater
	vector<int> v;
	v.push_back(10);
	v.push_back(40);
	v.push_back(30);
	v.push_back(20);
	//显示vector容器内容
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
	//升序排列
	sort(v.begin(), v.end());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
	//自己建立仿函数设计降序排列规则
	//sort(v.begin(), v.end(), vgreater());
	//for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	//{
	//	cout << *it << endl;
	//}
	//cout << endl;
	//利用greater来设计降序排列规则
	sort(v.begin(), v.end(), greater<int>());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
}

//逻辑仿函数--实现逻辑运算---template<class T> bool logical_and<T> ;bool logical_or<T> ;bool logical_not<T>
void test38()
{
	//逻辑非--bool logical_not<T>
	vector<bool> v;
	v.push_back(true);
	v.push_back(false);
	v.push_back(true);
	v.push_back(false);
	//显示
	for (vector<bool>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
	//利用逻辑非进行取反操作，并且将取反后的值放入新的容器v2中
	vector<bool> v2;
	//重新分配空间
	v2.resize(v.size());
	//搬运函数--transform，搬运的容器大小一定要小于等于新的存储空间
	transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());
	for (vector<bool>::iterator it = v2.begin(); it != v2.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
}

//遍历算法--for_each
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
	for_each(v.begin(), v.end(), print02());//print02()是仿函数类创建的实例--函数对象
}

//查找算法
class vector_predeitor //返回正数的索引
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
	//重载== 使得底层find知道如何对比person_find数据类型
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
	person_find p1("张三", 1000, 20);
	person_find p2("张四", 2000, 30);
	person_find p3("张五", 3000, 40);
	v2.push_back(p1);
	v2.push_back(p2);
	v2.push_back(p3);
	person_find p4("张五", 3000, 40);


	//find--查找元素
	//内置数据类型查找---int\stirng\double...
	it = find(v.begin(), v.end(), 20);
	cout << "find查找内置数据类型: " << *it << endl;
	//自定义数据类型查找---class，需要重载class中的==
	it1 = find(v2.begin(), v2.end(), p4);
	cout << "find查找自定义数据类型: " << (*it1).p_name << " " << (*it1).p_salary << " " << (*it1).p_age << endl;
	//find_if--按条件查找元素 find_if(iterator beg, iterator end, _pred)
	//beg 开始迭代器，end 结束迭代器， _pred 函数或者谓词(返回bool类型的仿函数)
	it = find_if(v.begin(), v.end(), vector_predeitor());
	cout << "find_if查找内置数据类型: " << *it << endl;
	//查找自定义数据类型
	it1 = find_if(v2.begin(), v2.end(), findagegreater20());
	cout << "find_if查找自定义数据类型: " << (*it1).p_name << " " << (*it1).p_salary << " " << (*it1).p_age << endl;
	//adjacent_find--查找相邻重复元素
	it = adjacent_find(v.begin(), v.end());
	cout << "adjacent_find: " << *it << endl;
	//binary_search--二分查找法，查找指定元素，找到返回true，否者返回false，但是这个在无序序列中不可用
	//所以在vector等容器中，想要使用binary_search，需要先对容器进行排序
	sort(v.begin(), v.end());
	bool flag;
	flag = binary_search(v.begin(), v.end(), 20);
	cout << "binary_search: " << flag << endl;
	//count--统计元素个数
	int num = 0;
	num = count(v.begin(), v.end(), -30);
	cout << "统计内置数据类型元素个数: " << num << endl;
	//统计自定义数据类型元素个数，这个和find查找自定义数据类型一样，需要重载其中的==号。
	num = count(v2.begin(), v2.end(), p4);
	cout << "统计自定义数据类型元素个数: " << num << endl;
	//count_if--按条件统计元素个数，count_if(iterator beg, iterator end, _pred)
	int num_if1 = 0, num_if2 = 0;
	//统计内置数据类型
	num_if1 = count_if(v.begin(), v.end(), numberGreater10());
	cout << "统计内置数据类型元素个数: " << num_if1 << endl;
	//统计自定义数据类型
	num_if2 = count_if(v2.begin(), v2.end(), findagegreater20());
	cout << "统计自定义数据类型元素个数: " << num_if2 << endl;
}

//排序算法--sort、random_shuffle、merge、reverse
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

	//random_shuffle--指定范围内的元素顺序随机调整
	srand((unsigned int)time(NULL));
	random_shuffle(v.begin(), v.end());
	cout << "random_shuffle--指定范围内的元素顺序随机调整: " << endl;
	showvector_int(v);

	//sort进行升序
	sort(v.begin(), v.end());
	cout << "sort进行升序: " << endl;
	showvector_int(v);
	//sort进行降序
	//1、利用自定义的排序函数
	//sort(v.begin(), v.end(), delivery);
	//2、利用内置的函数对象(仿函数)
	sort(v.begin(), v.end(), greater<int>());
	cout << "sort--利用内置的函数对象(仿函数)进行降序: " << endl;
	showvector_int(v);

	//merge--将两个容器元素合并，并储存在另一个容器中
	//使用merge的前提是两个容器必须同时都是升序，或者都是降序，注意，降序时需要自定义降序的排序规则或者使用内置的函数对象greater
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(100);
	v1.push_back(50);
	v1.push_back(90);
	sort(v1.begin(), v1.end(), greater<int>());
	cout << "排序(降序)后的v1：" << endl;
	showvector_int(v1);

	vector<int> vTarget;
	vTarget.resize(v1.size() + v.size());
	//降序
	merge(v1.begin(), v1.end(), v.begin(), v.end(), vTarget.begin(), greater<int>());
	//merge(v1.begin(), v1.end(), v.begin(), v.end(), vTarget.begin(), myorder());
	//升序
	//merge(v1.begin(), v1.end(), v.begin(), v.end(), vTarget.begin());

	cout << "merge--拼接两个vector容器: " << endl;
	showvector_int(vTarget);

	//reverse--首尾部元素对调
	reverse(v.begin(), v.end());
	cout << "reverse--首尾部元素对调: " << endl;
	showvector_int(v);
}

//常用拷贝和替换算法--copy、replace、replace_if、swap
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
	//copy之前需要先给目标容器分配空间
	v2.resize(v1.size());
	copy(v1.begin(), v1.end(), v2.begin());
	cout << "copy之后的v2：" << endl;
	showvector_int(v2);

	//replace--replace(iterator beg, iterator end, oldvalue, newvalue); 将容器内指定范围内的元素替换为新的元素
	replace(v2.begin(), v2.end(), 50, 20); //将v2容器从头部到尾部范围内的所有元素50替换为20
	replace(v2.begin() + 2, v2.end(), 10, 30); //将v2容器从头部后面第二个元素位置开始到尾部范围内的所有元素10替换为30
	cout << "replace之后的v2：" << endl;
	showvector_int(v2);

	//replace_if--replace_if(iterator beg, iterator end, _pred, newvalue); 替换指定范围内符合谓词或者函数条件_pred的所有元素为新的元素
	replace_if(v2.begin(), v2.end(), valueGreater20(), 10); //将v2容器从头部到尾部范围内的所有值大于20的元素替换为10
	cout << "replace_if之后的v2：" << endl;
	showvector_int(v2);

	//swap--swap(container c1, container c2); 交换两个容器c1,c2中的元素,交换对象必须是同类型的容器
	v2.push_back(100);
	swap(v1, v2);
	cout << "交换后的v1：" << endl;
	showvector_int(v1);
	cout << "交换后的v2：" << endl;
	showvector_int(v2);
}

//常用算数生成算法--需要包含头文件#include <numeric>
//主要包含两种算法--accumulate,fill，前一种是计算容器元素累计总和，后一种是向容器中添加元素
void test43()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(100);
	v1.push_back(50);
	v1.push_back(90);

	//accumulate(iterator beg, iterator end, value); 其中value是起始值
	int total_num = accumulate(v1.begin(), v1.end(), 1); //这个等同于 total_num = 1 + accumulate(v1.begin(), v1.end(), 0)
	cout << "累加值为: " << total_num << endl;

	//fill(iterator beg, iterator end, value); 向容器内填充指定的元素
	fill(v1.begin(), v1.end(), 0);
	showvector_int(v1);
}

//常用集合算法
//主要包含三种算法--set_intersection、set_union、set_difference，这三种算法分别是求两个容器的交集、并集、差集
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
	//为目标容器提前开辟空间，空间大小为两个容器中空间最小的那一方的空间大小
	vTarget_inter.resize(min(v.size(), v1.size()));
	//set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);  其中，dest是目标容器的开始迭代器
	//注意，这两个容器必须是有序的序列，和merge是一样的
	sort(v.begin(), v.end());
	sort(v1.begin(), v1.end());
	cout << "v：" << endl;
	showvector_int(v);
	cout << "v1：" << endl;
	showvector_int(v1);
	//set_intersection会返回交集结果容器 vTarget_inter 中最后一个元素的迭代器地址vTarget_inter.end()
	cout << "容器v与v1的交集结果" << endl;
	vector<int>::iterator itEnd_inter = set_intersection(v.begin(), v.end(), v1.begin(), v1.end(), vTarget_inter.begin());
	for_each(vTarget_inter.begin(), itEnd_inter, myPrint<int>);
	cout << endl;

	//set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
	//注意，这两个容器必须是有序的序列，和merge是一样的
	vector<int> vTarget_union;
	vTarget_union.resize(v.size() + v1.size()); 
	//set_union会返回并集结果容器 vTarget_union 中最后一个元素的迭代器地址vTarget_union.end()
	cout << "容器v与v1的并集结果" << endl;
	vector<int>::iterator itEnd_union = set_union(v.begin(), v.end(), v1.begin(), v1.end(), vTarget_union.begin());
	for_each(vTarget_union.begin(), itEnd_union, myPrint<int>);
	cout << endl;

	//set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
    //注意，这两个容器必须是有序的序列，和merge是一样的
	vector<int> vTarget_difference1;
	vector<int> vTarget_difference2;
	vTarget_difference1.resize(max(v.size(), v1.size()));
	vTarget_difference2.resize(max(v.size(), v1.size()));
	//先删除两个容器中存在的重复元素
	vector<int>::iterator it;
	it = unique(v.begin(), v.end());
	v.erase(it);

	cout << "v与v1的差集: " << endl;
	vector<int>::iterator itEnd_difference1 = set_difference(v.begin(), v.end(), v1.begin(), v1.end(), vTarget_difference1.begin());
	for_each(vTarget_difference1.begin(), itEnd_difference1, myPrint<int>);
	cout << endl;

	cout << "v1与v的差集: " << endl;
	vector<int>::iterator itEnd_difference2 = set_difference(v1.begin(), v1.end(), v.begin(), v.end(), vTarget_difference2.begin());
	for_each(vTarget_difference2.begin(), itEnd_difference2, myPrint<int>);
	cout << endl;

}

//案例实现--演讲比赛
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
	string name1[] = { "赵一","钱二","孙三","李四","周五","吴六","郑七","王八","冯九", "陈十", "褚十一", "卫十二" };
	string sex1[] = { "男","男","女","女","女","女","男","男","女", "男", "女", "男" };
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
		cout << "编号：" << (*it).m_id << "  年纪：" << (*it).m_age << "  姓名：" << (*it).m_name << "  性别：" << (*it).m_sex << "  成绩：" << (*it).m_grade << endl;
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
		cout << "rang必须为一个大于1的正整数！" << endl;
	}
}

//选手抽签
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
	//随机生成num_pingwei位评委的打分
	for (int i = 0; i < num_pingwei; i++)
	{
		grade = (rand() % 301 + 700.0) / 10.f;
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

//重写vector容器排序规则

bool player_sort( player& p1, player& p2)
{
	if (p1.m_grade == p2.m_grade)
	{
		return p1.m_grade > p2.m_grade;
	}
	return p1.m_grade > p2.m_grade;
}

//对选手进行评分
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
	//第一轮
	vector<player> py;
	vector<player> py1;
	vector<player> py2;

	multimap<int, player> m1;   //第一轮第一组的选手容器
	multimap<int, player> m2;   //第一轮第二组的选手容器
	multimap<int, player> m3;   //第二轮的选手容器

	
	//生成12个选手
	createPlayer(py, 12);
	//show_player(py);
	py1 = py;
	py2 = py;
	//py1只取py后6位选手，py2只取py前6位选手
	py1.erase(py1.begin() + 6, py1.end());
	py2.erase(py2.begin(), py2.begin() + 6);

	//第一组抽签
	getOrder(py1, m1, 6);
	//第二组抽签
	getOrder(py2, m2, 6);

	//评委给成绩
	giveGrade(m1, 12);
	giveGrade(m2, 12);
	//清空py1、py2，准备接受数据
	py1.clear();
	py2.clear();

	for (multimap<int, player>::iterator it = m1.begin(); it != m1.end(); it++)
	{
		py1.push_back(it->second);
		cout << "编号：" << (*it).second.m_id << "  年纪：" << (*it).second.m_age << "  姓名：" << (*it).second.m_name << "  性别：" << (*it).second.m_sex << "  成绩：" << (*it).second.m_grade << endl;
	}
	for (multimap<int, player>::iterator it = m2.begin(); it != m2.end(); it++)
	{
		py2.push_back(it->second);
		cout << "编号：" << (*it).second.m_id << "  年纪：" << (*it).second.m_age << "  姓名：" << (*it).second.m_name << "  性别：" << (*it).second.m_sex << "  成绩：" << (*it).second.m_grade << endl;
	}

	//对两组选手按成绩排序
	sort(py1.begin(), py1.end(), player_sort);
	sort(py2.begin(), py2.end(), player_sort);

	vector<player>::iterator it_py1 = py1.begin();
	vector<player>::iterator it_py2 = py2.begin();

	cout << "第一组中的前三名分别是：" << endl;
	for (; it_py1 != py1.begin() + 3; it_py1++)
	{
		cout << "编号：" << (*it_py1).m_id << "  年纪：" << (*it_py1).m_age << "  姓名：" << (*it_py1).m_name << "  性别：" << (*it_py1).m_sex << "  成绩：" << (*it_py1).m_grade << endl;
	}

	cout << "————————————————————————————————" << endl;
	cout << "第二组中的前三名分别是：" << endl;
	for (; it_py2 != py2.begin() + 3; it_py2++)
	{
		cout << "编号：" << (*it_py2).m_id << "  年纪：" << (*it_py2).m_age << "  姓名：" << (*it_py2).m_name << "  性别：" << (*it_py2).m_sex << "  成绩：" << (*it_py2).m_grade << endl;
	}

	//取py1、py2中各自的前三名放入py
	py.clear();

	for (int i = 0; i < 3; i++)
	{
		py.push_back(*(py1.begin() + i));
		py.push_back(*(py2.begin() + i));
	}
	cout << "————————————————————————————————" << endl;
	cout<< "进入第二轮的6名选手如下: " << endl;
	show_player(py);

	//第二轮
	//第二轮抽签
	getOrder(py, m3, 6);
	//评委给成绩
	giveGrade(m3, 12);
	//清空py，准备接受数据
	py.clear();

	cout << "————————————————————————————————" << endl;
	cout << "6名选手的第二轮成绩如下: " << endl;
	for (multimap<int, player>::iterator it = m3.begin(); it != m3.end(); it++)
	{
		py.push_back(it->second);
		cout << "编号：" << (*it).second.m_id << "  年纪：" << (*it).second.m_age << "  姓名：" << (*it).second.m_name << "  性别：" << (*it).second.m_sex << "  成绩：" << (*it).second.m_grade << endl;
	}
	//对两组选手按成绩排序
	sort(py.begin(), py.end(), player_sort);
	cout << "————————————————————————————————" << endl;
	cout << "6名选手的第二轮成绩排序后：" << endl;
	show_player(py);

	vector<player>::iterator it_py = py.begin();
	cout << "————————————————————————————————" << endl;
	cout << "最后的第一、二、三名分别是：" << endl;
	for (; it_py != py.begin() + 3; it_py++)
	{
		cout << "编号：" << (*it_py).m_id << "  年纪：" << (*it_py).m_age << "  姓名：" << (*it_py).m_name << "  性别：" << (*it_py).m_sex << "  成绩：" << (*it_py).m_grade << endl;
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
		cout << "请输入你想使用的功能编号：";
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
	cout << "欢迎下次使用！" << endl;
	system("pause");
	system("cls");
	exit(0);
}

void showmenu()
{
	cout << "欢迎使用机房预约管理系统!" << endl;
	cout << "-------------------------" << endl;
	cout << "****** 1、学生系统 ******" << endl;
	cout << "****** 2、教师系统 ******" << endl;
	cout << "***** 3、管理员系统 *****" << endl;
	cout << "****** 4、退出系统 ******" << endl;

	cout << "请选择你想进入的系统: " << endl;
}

//机房预约管理系统

void test47()
{
	int choice = 0;  //用户选择
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
	test01();  //重载
	//test02();    //重载前置++运算符,重载后置++运算符，重载<<运算符
	//test03();    //重载前置==运算符,并进行深拷贝
	//test05();    //继承中同名函数的调用
	//test06();    //多态的条件: 1、有继承关系；2、子类要重写父类的虚函数
	//test07();    //多态案例---计算器
	//test08();    //多态发生条件：1、子类继承并重写父类的函数；2、父类的指针或者引用指向子类的对象
	//test09();    //纯虚函数与抽象类
	//test10();    //多态案例---电脑组装
	//test11();    //文件写入与读取
	//test12();    //二进制读写文件
	//test13();    //函数模板
	//test14();    //模板的类继承以及类外函数定义
	//test16();    //模板类中友元函数的实现
	//test17();    //类模板
	//test18();    //容器 --vector
	//test19();    //案例实现: 评委打分，5名选手ABCDE，10个评委对其打分，去除最低分和最高分，取平均
	//test20();    //对list进行赋值和交换，查看大小，插入和删除
	//test21();    //list容器赋值、存取、访问、反转、排序
	//test22();    //排序案例: 将students自定义数据类型进行排序，student中属性有姓名、年纪、身高,按照年纪进行升序，年纪相同时按照升高进行降序排序。
	//test23();    //set容器
	//test24();    //multiset容器
	//test25();    //set容器的非自定义数据排序，如int,string,double等
	//test26();    //set容器的自定义数据排序，如int,string,double等
	//test27();    //对组---pair的两种创建方式
	//test28();    //利用pair对map容器进行赋值
	//test29();    //map容器的大小与交换
	//test30();    //map容器的插入与删除
	//test31();    //map查找和统计
	//test32();    //map的排序,默认为升序，更改排序规则与set一样，在创建map容器时就设定自定义规则
	//test33();    //案例--员工分组，将10个员工(ABCDEFGHIJ)分配到3个部门(策划、美术、研发)
	//test34();    //函数对象---重载函数调用操作符 () 的类，其对象常称为函数对象
	//test35();    //谓词--返回bool类型的仿函数
	//test36();    //算数仿函数--实现四则运算,包含在STL中，因此这些仿函数全都是类模板，并且调用这些仿函数还需要引用头文件#include <functional>
	//test37();    //关系仿函数--实现关系对比,包含在STL中
	//test38();    //逻辑仿函数--实现逻辑运算---template<class T> bool logical_and<T> ;bool logical_or<T> ;bool logical_not<T>
	//test39();    //遍历算法--for_each
	//test40();    //查找算法
	//test41();    //排序算法--sort、random_shuffle、merge、reverse
	//test42();    //常用拷贝和替换算法--copy、replace、replace_if、swap
	//test43();    //主要包含两种算法--accumulate,fill，前一种是计算容器元素累计总和，后一种是向容器中添加元素
	//test44();    //主要包含三种算法--set_intersection、set_union、set_difference，这三种算法分别是求两个容器的交集、并集、差集


	//案例实现---基于多态的职工管理系统
	//WorkerManager adminer;
	////测试代码
	////worker* emp1 = NULL;
	////emp1 = new employee(1, "张三", "男", 18);
	////worker* emp1 = new employee(1, "张三", "男", 18);
	////worker* man1 = new Manager(2, "李四", "男", 20);
	////worker* bos1 = new Boss(3, "夏洛克", "男", 25);
	//int  choice;
	//while (1)
	//{
	//	adminer.ShowmMenu();
	//	cout << "请输入您的选择：";
	//	cin >> choice;
	//	switch (choice)
	//	{
	//	case 0: adminer.ExitSystem(); break;  //0.退出管理系统
	//  case 1: adminer.AddWorker(); break;   //1.增加职工信息
	//	case 2: adminer.ShowWorkers(); break; //2.显示职工信息
	//	case 3: adminer.DeleteWorker(); break;//3.删除离职职工
	//	case 4: adminer.ModifyWorker(); break;//4.修改职工信息
	//	case 5: adminer.SearchWorker(); break;   //5.查找职工信息
	//	case 6: adminer.SortWorker(); break;   //6.按照编号排序
    //  case 7: adminer.CleanAllWorker(); break;   //7.清空所有文档
	//	default:
	//		system("cls");
	//		break;
	//	}
	//}


	//案例实现--演讲比赛
	//需求：演讲比赛，有12人参加，比赛分两轮，第一轮为淘汰赛，第二轮为决赛
	//每名选手都有编号：10001-10012
	//比赛方式：分组比赛，每组6人
	//第一轮分为两组，选手先随机抽签，再顺序演讲
	//10个评委给选手打分，去除最高与最低分，取平均分
	//第一轮取每组前三名进入决赛，第二轮取前三名胜出，且每轮比赛过后需要显示晋级(或获胜)的前三名选手信息
	//test45();   //自己做的，没有数据记录和清空功能，但基本的比赛流程都可以实现
	//test46();     //跟着视频做的


	//机房预约管理系统
	//需求：主界面设计学生、教师、管理员三个类以及一个退出功能
	//学生：1、申请预约--选择日期、时段、机房（1、2、3号）、生成记录；2、查看我的预约；3、查看所有预约；4、取消预约（成功的和正在审核中的预约）；5、注销登录
	//老师：1、查看所有预约--日期、时段、学号、学生姓名、机房号、预约状态；2、审核预约--审核通过、未通过；3、注销登录
	//管理员：1、添加账号--添加学生账号（学生学号、姓名、密码）--添加老师账号（职工号、姓名、密码）；2、查看账号--查看老师和学生的信息；3、查看机房--显示机房编号和最大容量；4、清空预约--清空预约文件；5、注销登录
	test47();
	
	system("pause");
	return 0;
}
 