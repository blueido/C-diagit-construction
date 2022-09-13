#include "main.h"
#include "DynamicArray.h"
#include "linkList.h"
#include "companyList.h"
#include "cyclicList.h"
#include "seqStack.h"
#include "listStack.h"
#include "seqque.h"
#include <Windows.h>
#include <time.h>

using namespace std;

//动态数组
void test01()
{
	//创建容量为1 的动态数组
	dynamicArray da(1);
	//插入数据
	da.push_back(1);
	da.push_back(2);
	da.push_back(3);
	da.push_back(4);
	//分别进行按位置删除和按值删除
	da.era_pos(4);
	da.era_value(3);
	//显示函数
	da.show();
	//回收内存
	da.~dynamicArray();
}

//链表
template <class T>
void myPrint(void* data)  //这个是根据我们插入的数据类型来写，可以利用模板来实现数据类型的包容
{
	T* p = (T*)data;
	cout << *p << " ";
}

void test02()
{
	int i1 = 1;
	int i2 = 2;
	int i3 = 3;

	int pos = -1;
	linkList l;
	//插入
	l.insert(0, &i1);   //在pos==0的位置之前插入数据i，即i1的pos ==0
	l.insert(0, &i2);  //在pos==0的位置之前插入数据i2，即i2的pos ==0 ，i1的pos变为了1
	l.insert(0, &i3);  //在pos==0的位置之前插入数据i3，即i3的pos ==0 ，i2的pos变为了1，i1的pos变为了2

	//查找
	pos = l.findIt(&i1);
	cout << "i的pos: " << pos << endl;
	pos = l.findIt(&i2);
	cout << "i2的pos: " << pos << endl;
	pos = l.findIt(&i3);
	cout << "i3的pos: " << pos << endl;

	//显示
	cout << "l中的元素如下：" << endl;
	l.show(myPrint<int>);
	cout << endl;
	//size大小显示
	cout << "size: " << l.size << endl;
	//删除
	l.era(1);
	cout << "删除后，l中的元素如下：" << endl;
	l.show(myPrint<int>);

	l.~linkList();
}

//企业链表
class person
{
public:
	person(string name, int age)
	{
		this->m_name = name;
		this->m_age = age;
	}

	linknode node;  //这个相当于指针域数据，因此必须写在最上边，也就是第一个，这样才算是企业链表
	string m_name;
	int m_age;
};
void myPrint1(linknode* data)  //这个是根据我们插入的数据类型来写
{
	person* p = (person*)data;
	cout << p->m_name << " " << p->m_age << endl;
}

int myCompare(linknode* current_node, linknode* data)
{
	person* p1 = (person*)current_node;
	person* p2 = (person*)data;

	if (p1->m_age == p2->m_age || p1->m_name == p2->m_name)
	{
		return 0;
	}
	return -1;

}
void test03()
{
	companylist cpl;
	person p1("张一", 11);
	person p2("张二", 12);
	person p3("张三", 13);
	person p4("张四", 14);

	
	cpl.insert(0, (linknode*) &p1);
	cpl.insert(0, (linknode*) &p2);
	cpl.insert(0, (linknode*) &p3);
	cpl.insert(0, (linknode*) &p4);

	int pos = -1;
	pos = cpl.findIt((linknode*)&p1);
	cout << "pos: " << pos << endl;

	cpl.show(myPrint1);
	cpl.~companylist();
}

//循环链表
void test04()
{
	//构造函数
	cyclicList cl;
	int pos = -1;
	int i1 = 1;
	int i2 = 2;
	int i3 = 3;
	//插入
	cl.insert(0, (void*)&i1);
	cl.insert(1, (void*)&i2);
	cl.insert(2, (void*)&i3);
	//查找
	pos = cl.findIt((void*)&i1);
	cout << "i1的pos：" << pos << endl;
	pos = cl.findIt((void*)&i2);
	cout << "i2的pos：" << pos << endl;
	pos = cl.findIt((void*)&i3);
	cout << "i3的pos：" << pos << endl;
	//显示
	cout << "cl中的元素为：";
	cl.show(myPrint<int>);
	cout << endl;
	//按值删除
	cl.era((void*)&i1);  //删除i1
	cout << "删除i1后，cl中的元素为：";
	cl.show(myPrint<int>);
	cout << endl;

	//按位置删除
	cl.era(1);   //删除Pos==1的元素
	cout << "删除pos==1处元素后，cl中的元素为：";
	cl.show(myPrint<int>);

	//析构函数
	cl.~cyclicList();
}

//约瑟夫问题
void test05()
{
	int m = 8;
	int n = 3;
	int index = 1;
	int num[8];
	cyclicList cl;
	//插入1~8
	for (int i = 1; i < 9; i++)
	{
		num[i-1] = i;
		cl.insert(i - 1, (void*)&num[i-1]);
	}
	cl.show(myPrint<int>);
	cout << endl;

	//辅助结点
	cyclicnode* current = cl.headnode;
	while (cl.size > 1)
	{
		current = current->pnext;
		if (current == cl.headnode)
		{
			current = current->pnext;
		}
		if (index % n == 0)
		{
			myPrint<int>(current->data);
			//缓存当前结点所指向的下一个结点
			cyclicnode* next = current->pnext;
			//删除当前结点
			cl.era(current->data);
			//让current指向缓存结点的地址
			current->pnext = next;
		}
		index++;
	}
	if (cl.size == 1)
	{
		cl.show(myPrint<int>);
		cout << endl;
	}

}

//顺序栈
void test06()
{
	seqStack ss;
	int num[10];
	for (int i = 0; i < 10; i++)
	{
		num[i] = i;
		//入栈
		ss.push_stack((void*)&num[i]);
		//显示入栈数据
		myPrint<int>((void*)ss.data[i]);
	}
	cout << endl;

	//显示栈顶元素
	myPrint<int>((void*)ss.front());
	cout << endl;

	//显示并从栈顶弹出元素
	while(ss.size > 0)
	{
		myPrint<int>((void*)ss.front());
		ss.pop_stack();
	}
	//析构函数
	ss.~seqStack();
}

//栈的链式存储
class personls
{
public:
	personls(string name, int age)
	{
		this->m_name = name;
		this->m_age = age;
	}

	listStackNode node;  //这个相当于指针域数据，因此必须写在最上边，也就是第一个，这样才算是企业链表
	string m_name;
	int m_age;
};
template <class T>
void myPrint2(listStackNode* data)  //这个是根据我们插入的数据类型来写
{
	T* p = (T*)data;
	cout << p->m_name << " " << p->m_age << endl;
}
void test07()
{
	listStack ls;
	personls p1("张一", 11);
	personls p2("张二", 12);
	personls p3("张三", 13);
	personls p4("张四", 14);
	personls p5("张五", 15);
	//入栈
	ls.push((listStackNode*)&p1);
	ls.push((listStackNode*)&p2);
	ls.push((listStackNode*)&p3);
	ls.push((listStackNode*)&p4);
	ls.push((listStackNode*)&p5);

	//cout << ls.size << endl;

	while (ls.size != 0)
	{
		//弹出并显示栈顶元素
		//myPrint2<personls>((listStackNode*)ls.front());
		personls* p1 = (personls*)ls.front();
		cout << p1->m_age << " " << p1->m_name << endl;
		//出栈
		ls.pop();
	}
	ls.clear();
	ls.~listStack();
}

//队列的顺序存储
void test08()
{
	seqque sq;

	sq.push((void*)10);
	sq.push((void*)20);
	sq.push((void*)30);
	sq.push((void*)40);

	while (sq.size > 0)
	{
		cout << "队头元素为：";
		int q = (int)sq.front();
		cout << q << endl;
		cout << "队尾元素为：";
		int b = (int)sq.back();
		cout << b << endl;
		//弹出元素
		sq.pop();
	}

	sq.clear();
	int q = (int)sq.front();
	cout << q << endl;

	sq.~seqque();

}

//栈的应用--就近匹配括号
class mychar
{
public:
	listStackNode node;
	const char* pa;
	int index = 0;
};

//显示错误匹配位置函数
void showError(const char* str, int pos)
{
	int i = 0;
	while (str[i] != '\0')
	{
		cout << str[i];
		i++;
	}
	cout << endl;
	for (int i = 0; i < pos; i++)
	{
		cout << " ";
	}
	cout << "A" << endl;
}

void test09()
{
	const char* str = "auisj,.[jeab + 2!{(++---))9(((( ))!";
	const char* str1 = "A";
	const char* p = str;
	listStack ls;
	int i = 0;

	while (*p != '\0')
	{
		//左括号直接插入栈中
		if (*p == '(')
		{
			mychar* mc = new mychar[sizeof(mychar)];  //每次使用完之后，系统会自动释放内存
			mc->pa = p;
			mc->index = i;
			//由于这里我们入栈使用的是指针，因此，我们不能直接释放mc的内存，否则mc指向的内存消失，ls就无法找到存储的指针所指向的地址
			ls.push((listStackNode*) mc);
		}
		if (*p == ')')
		{
			//判断栈中元素是否为0
			if (ls.size == 0)
			{
				cout << "缺少一个 ( " << endl;
				showError(str, i);
				//break;
			}
			else 
			{
				mychar* mc = (mychar*)ls.front();
				if (*mc->pa == '(')
				{
					ls.pop();  //弹出
					delete mc;
				}
			}
		}
 		i++;
		p++;
	}
	while (ls.size > 0)
	{
		int pos = -1;
		mychar* mc = (mychar*)ls.front();
		pos = mc->index;
		cout << "缺少一个 )" << endl;
		showError(str, pos);
		ls.pop();
		delete mc;
	}
}

//栈的应用---中缀表达式转为后缀表达式
int IsNumber(char c)  //判断是否为数字
{
	if(c>='0'&&c<='9')
	{
		return 0;
	}
	return 1;
}

int GetPriority(char c)
{
	if (c == '*' || c == '/')
	{
		return 2;
	}
	else if (c == '+' || c == '-')
	{
		return 1;
	}
	if (c == '(')
	{
		return 0;
	}
	return -1;
}

mychar* PushToStack(const char* c)
{
	mychar* mp = new mychar();
	mp->index = 0;
	mp->pa = c;
	return mp;
}

void test10()
{
	listStack ls;
	const char* str = "8+(3-1)*5";
	const char* c = str;

	while (*c != '\0')
	{
		if (IsNumber(*c)) //c不是数字
		{
			//判断是不是( 或者 判断栈中元素是否为空，如果是，直接入栈，否则判断优先级
			if (*c == '(' || ls.size == 0)
			{
				ls.push((listStackNode*) PushToStack(c));
			}
			else //否则判断栈顶优先级是否小于*c 的优先级
			{
				while (1)
				{
					if (ls.size == 0)
					{
						ls.push((listStackNode*)PushToStack(c));
					}
					//先用一个mychar类型接收栈顶元素
					mychar* mc = (mychar*)ls.front();
					//如果*c优先级高与栈顶元素，或者栈内为空 ，则将c指向的字符直接入栈
					if (GetPriority(*c) > GetPriority(*mc->pa))
					{
						ls.push((listStackNode*)PushToStack(c));
						break;
					}   
					//否则，当栈顶元素优先级高与*c，并且*c不是右括号,弹出元素直到栈顶优先级比*c低
					else if (GetPriority(*c) <= GetPriority(*mc->pa)&& *c != ')')
					{
						cout << *mc->pa << " ";
						ls.pop();
					}
					if (*c == ')')
					{
						delete mc;
						break;
					}
					delete mc;
				}
			}
			if (*c == ')')   //如果*c是右括号，则不断弹出栈内元素，直到弹出左括号或者栈内为空
			{
				while (ls.size > 0)
				{
					mychar* mp = (mychar*)ls.front();
					if (*mp->pa == '(')  // 栈顶元素为 (
					{
						ls.pop();
						delete mp;
						break;
					}
					cout << *mp->pa << " ";
					ls.pop();
					//delete mp; //为什么这里不能释放类指针呢？
				}
			}
		}
		else  //c是数字,则直接显示
		{
			cout << *c << " ";
		}
		c++;
	}

	while (ls.size > 0)
	{
		mychar* mc = (mychar*)ls.front();
		cout << *mc->pa << " ";
		ls.pop();
		delete mc;
	}
	cout << endl;
}

//栈的应用--后缀表达式求解
//求解规则
//数字：直接进栈； 符号：先从栈中弹出右操作数，再从栈中弹出左操作数，根据符号进行运算，最后将结果入栈；最终遍历结束后，栈中的唯一数字作为计算结果；
class myint
{
public:
	listStackNode node;
	int value;
};
int GetNumber(listStack ls)
{
	if (ls.size == 0)
	{
		return NULL;
	}
	int right = ((myint*)ls.front())->value;
	ls.pop();
	return right;
}
myint* PushToStack1(const char c)
{
	myint* mp1 = new myint();
	//将char强转为int，得到ASCII值
	int m = (int)c;
	//ASCII值减去41得到实际值
	m = m - 48;
	mp1->value = m;
	return mp1;
}
void test11()
{
	const char str[] = "831-5*+";
	const char* c = str;
	listStack ls;

	while (*c != NULL)
	{
		if (IsNumber(*c))  //符号
		{
			//先从栈中弹出右操作数
			int right = ((myint*)ls.front())->value;
			//cout << "right:" << right << " ";
			ls.pop();
			//先从栈中弹出左操作数
			int left = ((myint*)ls.front())->value;
			//cout << "left:" << left << " ";
			ls.pop();
			//定义一个mychar存放结果
			myint* mc = new myint();
			//根据运算符进行运算
			if (*c == '+')
			{
				(*mc).value = (left + right);
			}
			else if (*c == '-')
			{
				(*mc).value = (left - right);
			}
			else if (*c == '*')
			{
				(*mc).value = (left * right);
			}
			else if (*c == '/')
			{
				(*mc).value = (left / right);
			}
			else
			{
				cout << "error：ls读取一个非运算符的数字！" << endl;
			}
			//将结果压入栈中
			ls.push((listStackNode*)mc);
		}
		else   //数字直接进栈
		{
			/*cout << *c << " ";*/
			ls.push((listStackNode*)PushToStack1(*c));
		}
		c++;
	}
	if (ls.size == 1)
	{
		myint* nc = (myint*)ls.front();
		cout << (*nc).value << endl;
		ls.pop();
	}
}

//二叉树递归遍历
void test12()
{
	binaryTree bt;
	//先序遍历
	//bt.createtree();
	//cout << endl;
	////中序遍历
	//bt.createtree();
	//cout << endl;
	//后序遍历
	bt.createtree();
	cout << endl;
}

//二叉树非递归遍历
void test13()
{
	binaryTree bt;
	bt.createtree();
	cout << endl;
}

//二叉树创建
//通过中序遍历和先序遍历可以确定一个树
//通过中序遍历和后序遍历可以确定一个树
//通过先序遍历和#号法可以创建一个树
//通过一个中序遍历的结果是无法确定一个树的
//通过先序遍历和后序遍历不可以确定一个树
void test14()
{

}


//排序
void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
//冒泡排序，从小到大
void bub(int* arr, int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length -i- 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
//冒泡排序改进版，从小到大
void bub1(int* arr, int length)
{
	int flag = 0;  //falg==0表示序列还没有排序完成
	for (int i = 0; i < length && flag == 0; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			flag = 1;  //在这之前的length-i-1~length-1这段中已经排序完成，我们假设在0~length-i-1这段中已经没有需要继续排序的序列了，如果程序一直没有执行if中的代码，那么我们的假设成立，因此flag保持为1，可以结束循环
			if (arr[j] > arr[j + 1])
			{
				flag = 0;   //当程序运行到这行时，这表示在0~length-i-1这段中还存在需要排序的序列，因此flag设定为0
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
//选择排序，从小到大--假设下标为i（i起始为0）的元素为最小，循环查找后续比第i个元素小的元素，并将该元素的下标赋给min，循环结束后判断min是不是当初的i，如果不是，则表明min位置的元素是在i之后的更小的元素，两者交换位置，否则的话，i位置的元素是后续序列中最小的
void SelectSort(int* arr, int length)
{
	for (int i = 0; i < length; i++)
	{
		int min = i;
		for (int j = i+1; j < length; j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			swap(arr[min], arr[i]);
		}
	}
}
//插入排序，从小到大，这个其实也是一种选择排序，他的特殊之处在于，首先，他先判断在i位置，是否i位置的数比其前一个位置数小，如果小，那么从i-1开始查找比i位置数字小的元素，当在j=i-1~0这区间中，有一个j位置的元素小于i位置元素，那么就把i位置的元素插入到j+1的位置，否则就表示0~i-1这个区间中，i位置元素最小，就将其插入到位置0。
void InserterSort(int* arr, int length)
{
	for (int i = 1; i < length; i++)
	{
		int j;
		if (arr[i] < arr[i - 1])
		{
			int temp = arr[i];
			for (j = i - 1; j >= 0 && arr[j] > temp; j--)
			{
				arr[j + 1] = arr[j];
			}
			//由于上面循环最后有一个j--，因此我们赋值的时候，应当在j+1的位置上赋值
			arr[j+1] = temp;
		}
	}
}
//希尔排序，从小到大--这个主要是利用循环分割的思想，increaser是分割的数量，称为增量，首先将一整段无序序列分割为increaser份无序序列，然后对每一组分别进行插入排序，然后利用增量更新表达式更新increaser，直到increaser=1，注意，到increaser=1时，还需要再来一次插入排序，下面的程序使用的是do while循环，因此他是限制性increaser=1时的插入排序，然后再退出循环的
void ShellSort(int* arr, int length)
{
	int increaser = length;
	int i, j, k;
	do
	{
		//确定分组增量
		increaser = increaser / 3 + 1;   //增量更新表达式
		for (i = 0; i < increaser; i++)  //分组之后，总的组数为increaser
		{
			//对第i组进行插入排序,组中元素间隔为increaser
			for (j = i + increaser; j < length; j += increaser)
			{
				if (arr[j] < arr[j - increaser])
				{
					int temp = arr[j];
					for (k = j - increaser; k >= 0 && arr[k] > temp; k -= increaser)
					{
						arr[k + increaser] = arr[k];
					}
					arr[k + increaser] = temp;
				}
			}
		}
	} while (increaser > 1);
}

//快速排序--分三步：1、设定基准数，设定一个基准数之后，先从左向右寻找小于基准数的元素， 2、挖坑和回填 3、分割递归
void QuickSort(int* arr, int start, int end)
{
	int i = start;
	int j = end;

	//设定基准数，挖初始坑
	int temp = arr[i];

	if (i < j)
	{
		while(i < j)
		{
			//从右向左遍历第一个小于temp的元素
			while (i < j && arr[j] >= temp)
			{
				j--;
			}
			//填坑
			if (i < j)
			{
				arr[i] = arr[j];
				i++;
			}

			//再从左向右遍历第一个大于temp的元素
			while (i < j && arr[i] < temp)
			{
				i++;
			}
			//填坑
			if (i < j)
			{
				arr[j] = arr[i];
				j--;
			}
		}
		//回填基准数,这个时候i==j，因此，回填到i位置还是j位置都一样
		arr[j] = temp;

		//对回填处左侧进行快速排序
		QuickSort(arr, start, i - 1);
		//对回填处右侧进行快速排序
		QuickSort(arr, i + 1, end);
	}
}


//合并算法 从小到大--首先根据输入数据找到两组序列的头尾元素位置，然后利用while循环比较两组序列的头元素大小，将较小的元素存储到临时空间temp中，一直到两组序列全部都存储到temp中为止。然后将temp中的元素覆盖到arr数组原位置处。
void combine(int* arr, int start, int mid, int end, int* temp)
{
	int length = 0;   //length表示temp中存储的元素个数
	//i_start表示第一个序列的头元素位置
	int i_start = start;
	int i_end = mid;
	//j_start表示第二个序列的头元素位置
	int j_start = mid + 1;
	int j_end = end;
	while (i_start <= i_end || j_start <= j_end)
	{
		//开始比较待合并的两个序列中的元素
		if (arr[i_start] < arr[j_start] && i_start <= i_end)   //第一个序列中的元素比第二个序列中的元素小
		{
			temp[length] = arr[i_start];   //将第一个序列中的元素放入temp中存储
			length++;
			i_start++;
		}
		if (arr[i_start] >= arr[j_start] && j_start <= j_end)   //第二个序列中的元素比第一个序列中的元素小
		{
			temp[length] = arr[j_start];   //将第二个序列中的元素放入temp中存储
			length++;
			j_start++;
		}
		if (i_start > i_end)
		{
			temp[length] = arr[j_start];
			j_start++;
			length++;
		}
		if (j_start > j_end)
		{
			temp[length] = arr[i_start];
			i_start++;
			length++;
		}
	}
	//将temp中的元素覆盖到arr中
	for (int i = 0; i < length; i++)
	{
		arr[start + i] = temp[i];
	}
}
//归并排序，从小到大--这是一种分为三步的递归算法，1、对数组中0~mid位置的元素进行归并排序处理 2、对数组中mid+1~end位置的元素进行归并排序处理  3、对处理后的两部分进行合并
void MergeSort(int* arr, int start, int end, int* temp)
{
	if(start >= end)
	{
		return;
	}
	int mid = (start + end) / 2;
	//先对arr中位置为0~mid的元素进行处理
	MergeSort(arr, start, mid, temp);
	//再对arr中位置为mid+1~end的元素进行处理
	MergeSort(arr, mid + 1, end, temp);
	//合并
	combine(arr, start, mid, end, temp);
}

//调整堆算法
/*
* arr是待调整的数组
* index是调整开始的元素下标
* length是当前数组的长度
*/
void AdjustHeap(int* arr, int index, int length)
{
	int root = index;  //root表示当前结点位置
	int lchild = 2 * index + 1;   //lchild是当前结点的左子结点
	int rchild = 2 * index + 2;   //rchild是当前结点的右子结点

	if (lchild<length && arr[lchild]>arr[root]) 
	{
		root = lchild;
	}
	if (rchild<length && arr[rchild]>arr[root])
	{
		root = rchild;
	}
	if (root != index)   //这个表示，root发生了变化，因此要将root位置的数据与原始index位置的数据进行交换
	{
		swap(arr[root], arr[index]);
		AdjustHeap(arr, root, length); //由于交换之后，可能交换之后的root位置元素可能小于当前位置的左子结点和右子结点位置的元素，因此还需要进行递归
	}
}

//堆排序，从小到大
void HeapSort(int* arr, int length)
{
	//初始化堆
	for (int i = length / 2 - 1; i >= 0; i--)
	{
		//调整堆，从下向上调整，应为i是从大到小开始的
		AdjustHeap(arr, i, length);
	}
	//交换树中第一个位置的元素和最后一个位置的元素
	for (int i = length - 1; i >= 0; i--)
	{
		//交换树中第一个位置的元素和最后一个位置的元素
		swap(arr[i], arr[0]);
		//从上向下调整，直接从0开始进行堆调整
		AdjustHeap(arr, 0, i);
	}
}

#define length1  10

//创建数组函数
void CreateArr(int* arr, int len)
{
	srand((unsigned int)time(0));
	for (int i = 0; i < len; i++)
	{
		arr[i] = rand() % len;
	}
}

//显示数组函数
void ArrShow(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void test15()
{
	int arr[length1];
	CreateArr(arr, length1);
	ArrShow(arr, length1);

	//冒泡排序，冒泡排序的特点在于最先有序的是数组的尾部
	//bub(arr, length1);

	//改进版
	bub1(arr, length1);

	//选择排序
	//SelectSort(arr, length1);

	//插入排序--将无序序列插入到有序序列中
	//InserterSort(arr, length1);

	//希尔排序
	//ShellSort(arr, length1);

	//快速排序
	QuickSort(arr, 0, length1 - 1);

	//归并排序
	////开辟临时空间
	//int* temp = new int[length1];
	//MergeSort(arr, 0, length1 - 1, temp);
	////销毁临时空间
	//delete[] temp;

	//堆排序
	HeapSort(arr, length1);

	ArrShow(arr, length1);
}

int main()
{
	//test01();         //动态数组
	//test02();         //链表
	//test03();         //企业链表
	//test04();         //循环链表
	//test05();         //约瑟夫问题
	//test06();         //顺序栈
	//test07();         //栈的链式存储
	//test08();         //队列的顺序存储
	//test09();         //栈的应用--就近匹配括号
	//test10();         //栈的应用--中缀表达式转为后缀表达式
	//test11();         //栈的应用--后缀表达式计算 
	//test12();         //二叉树递归遍历，求树的高度、叶子数、拷贝树、销毁树空间
	//test13();         //二叉树非递归遍历
	//test14();         //二叉树的创建
	//test15();         //排序--冒泡排序、改进版冒泡、选择排序、插入排序、希尔排序、快速排序、归并排序、堆排序


	system("pause");
	return 0;
}