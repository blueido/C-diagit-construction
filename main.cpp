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

//��̬����
void test01()
{
	//��������Ϊ1 �Ķ�̬����
	dynamicArray da(1);
	//��������
	da.push_back(1);
	da.push_back(2);
	da.push_back(3);
	da.push_back(4);
	//�ֱ���а�λ��ɾ���Ͱ�ֵɾ��
	da.era_pos(4);
	da.era_value(3);
	//��ʾ����
	da.show();
	//�����ڴ�
	da.~dynamicArray();
}

//����
template <class T>
void myPrint(void* data)  //����Ǹ������ǲ��������������д����������ģ����ʵ���������͵İ���
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
	//����
	l.insert(0, &i1);   //��pos==0��λ��֮ǰ��������i����i1��pos ==0
	l.insert(0, &i2);  //��pos==0��λ��֮ǰ��������i2����i2��pos ==0 ��i1��pos��Ϊ��1
	l.insert(0, &i3);  //��pos==0��λ��֮ǰ��������i3����i3��pos ==0 ��i2��pos��Ϊ��1��i1��pos��Ϊ��2

	//����
	pos = l.findIt(&i1);
	cout << "i��pos: " << pos << endl;
	pos = l.findIt(&i2);
	cout << "i2��pos: " << pos << endl;
	pos = l.findIt(&i3);
	cout << "i3��pos: " << pos << endl;

	//��ʾ
	cout << "l�е�Ԫ�����£�" << endl;
	l.show(myPrint<int>);
	cout << endl;
	//size��С��ʾ
	cout << "size: " << l.size << endl;
	//ɾ��
	l.era(1);
	cout << "ɾ����l�е�Ԫ�����£�" << endl;
	l.show(myPrint<int>);

	l.~linkList();
}

//��ҵ����
class person
{
public:
	person(string name, int age)
	{
		this->m_name = name;
		this->m_age = age;
	}

	linknode node;  //����൱��ָ�������ݣ���˱���д�����ϱߣ�Ҳ���ǵ�һ����������������ҵ����
	string m_name;
	int m_age;
};
void myPrint1(linknode* data)  //����Ǹ������ǲ��������������д
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
	person p1("��һ", 11);
	person p2("�Ŷ�", 12);
	person p3("����", 13);
	person p4("����", 14);

	
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

//ѭ������
void test04()
{
	//���캯��
	cyclicList cl;
	int pos = -1;
	int i1 = 1;
	int i2 = 2;
	int i3 = 3;
	//����
	cl.insert(0, (void*)&i1);
	cl.insert(1, (void*)&i2);
	cl.insert(2, (void*)&i3);
	//����
	pos = cl.findIt((void*)&i1);
	cout << "i1��pos��" << pos << endl;
	pos = cl.findIt((void*)&i2);
	cout << "i2��pos��" << pos << endl;
	pos = cl.findIt((void*)&i3);
	cout << "i3��pos��" << pos << endl;
	//��ʾ
	cout << "cl�е�Ԫ��Ϊ��";
	cl.show(myPrint<int>);
	cout << endl;
	//��ֵɾ��
	cl.era((void*)&i1);  //ɾ��i1
	cout << "ɾ��i1��cl�е�Ԫ��Ϊ��";
	cl.show(myPrint<int>);
	cout << endl;

	//��λ��ɾ��
	cl.era(1);   //ɾ��Pos==1��Ԫ��
	cout << "ɾ��pos==1��Ԫ�غ�cl�е�Ԫ��Ϊ��";
	cl.show(myPrint<int>);

	//��������
	cl.~cyclicList();
}

//Լɪ������
void test05()
{
	int m = 8;
	int n = 3;
	int index = 1;
	int num[8];
	cyclicList cl;
	//����1~8
	for (int i = 1; i < 9; i++)
	{
		num[i-1] = i;
		cl.insert(i - 1, (void*)&num[i-1]);
	}
	cl.show(myPrint<int>);
	cout << endl;

	//�������
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
			//���浱ǰ�����ָ�����һ�����
			cyclicnode* next = current->pnext;
			//ɾ����ǰ���
			cl.era(current->data);
			//��currentָ�򻺴���ĵ�ַ
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

//˳��ջ
void test06()
{
	seqStack ss;
	int num[10];
	for (int i = 0; i < 10; i++)
	{
		num[i] = i;
		//��ջ
		ss.push_stack((void*)&num[i]);
		//��ʾ��ջ����
		myPrint<int>((void*)ss.data[i]);
	}
	cout << endl;

	//��ʾջ��Ԫ��
	myPrint<int>((void*)ss.front());
	cout << endl;

	//��ʾ����ջ������Ԫ��
	while(ss.size > 0)
	{
		myPrint<int>((void*)ss.front());
		ss.pop_stack();
	}
	//��������
	ss.~seqStack();
}

//ջ����ʽ�洢
class personls
{
public:
	personls(string name, int age)
	{
		this->m_name = name;
		this->m_age = age;
	}

	listStackNode node;  //����൱��ָ�������ݣ���˱���д�����ϱߣ�Ҳ���ǵ�һ����������������ҵ����
	string m_name;
	int m_age;
};
template <class T>
void myPrint2(listStackNode* data)  //����Ǹ������ǲ��������������д
{
	T* p = (T*)data;
	cout << p->m_name << " " << p->m_age << endl;
}
void test07()
{
	listStack ls;
	personls p1("��һ", 11);
	personls p2("�Ŷ�", 12);
	personls p3("����", 13);
	personls p4("����", 14);
	personls p5("����", 15);
	//��ջ
	ls.push((listStackNode*)&p1);
	ls.push((listStackNode*)&p2);
	ls.push((listStackNode*)&p3);
	ls.push((listStackNode*)&p4);
	ls.push((listStackNode*)&p5);

	//cout << ls.size << endl;

	while (ls.size != 0)
	{
		//��������ʾջ��Ԫ��
		//myPrint2<personls>((listStackNode*)ls.front());
		personls* p1 = (personls*)ls.front();
		cout << p1->m_age << " " << p1->m_name << endl;
		//��ջ
		ls.pop();
	}
	ls.clear();
	ls.~listStack();
}

//���е�˳��洢
void test08()
{
	seqque sq;

	sq.push((void*)10);
	sq.push((void*)20);
	sq.push((void*)30);
	sq.push((void*)40);

	while (sq.size > 0)
	{
		cout << "��ͷԪ��Ϊ��";
		int q = (int)sq.front();
		cout << q << endl;
		cout << "��βԪ��Ϊ��";
		int b = (int)sq.back();
		cout << b << endl;
		//����Ԫ��
		sq.pop();
	}

	sq.clear();
	int q = (int)sq.front();
	cout << q << endl;

	sq.~seqque();

}

//ջ��Ӧ��--�ͽ�ƥ������
class mychar
{
public:
	listStackNode node;
	const char* pa;
	int index = 0;
};

//��ʾ����ƥ��λ�ú���
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
		//������ֱ�Ӳ���ջ��
		if (*p == '(')
		{
			mychar* mc = new mychar[sizeof(mychar)];  //ÿ��ʹ����֮��ϵͳ���Զ��ͷ��ڴ�
			mc->pa = p;
			mc->index = i;
			//��������������ջʹ�õ���ָ�룬��ˣ����ǲ���ֱ���ͷ�mc���ڴ棬����mcָ����ڴ���ʧ��ls���޷��ҵ��洢��ָ����ָ��ĵ�ַ
			ls.push((listStackNode*) mc);
		}
		if (*p == ')')
		{
			//�ж�ջ��Ԫ���Ƿ�Ϊ0
			if (ls.size == 0)
			{
				cout << "ȱ��һ�� ( " << endl;
				showError(str, i);
				//break;
			}
			else 
			{
				mychar* mc = (mychar*)ls.front();
				if (*mc->pa == '(')
				{
					ls.pop();  //����
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
		cout << "ȱ��һ�� )" << endl;
		showError(str, pos);
		ls.pop();
		delete mc;
	}
}

//ջ��Ӧ��---��׺���ʽתΪ��׺���ʽ
int IsNumber(char c)  //�ж��Ƿ�Ϊ����
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
		if (IsNumber(*c)) //c��������
		{
			//�ж��ǲ���( ���� �ж�ջ��Ԫ���Ƿ�Ϊ�գ�����ǣ�ֱ����ջ�������ж����ȼ�
			if (*c == '(' || ls.size == 0)
			{
				ls.push((listStackNode*) PushToStack(c));
			}
			else //�����ж�ջ�����ȼ��Ƿ�С��*c �����ȼ�
			{
				while (1)
				{
					if (ls.size == 0)
					{
						ls.push((listStackNode*)PushToStack(c));
					}
					//����һ��mychar���ͽ���ջ��Ԫ��
					mychar* mc = (mychar*)ls.front();
					//���*c���ȼ�����ջ��Ԫ�أ�����ջ��Ϊ�� ����cָ����ַ�ֱ����ջ
					if (GetPriority(*c) > GetPriority(*mc->pa))
					{
						ls.push((listStackNode*)PushToStack(c));
						break;
					}   
					//���򣬵�ջ��Ԫ�����ȼ�����*c������*c����������,����Ԫ��ֱ��ջ�����ȼ���*c��
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
			if (*c == ')')   //���*c�������ţ��򲻶ϵ���ջ��Ԫ�أ�ֱ�����������Ż���ջ��Ϊ��
			{
				while (ls.size > 0)
				{
					mychar* mp = (mychar*)ls.front();
					if (*mp->pa == '(')  // ջ��Ԫ��Ϊ (
					{
						ls.pop();
						delete mp;
						break;
					}
					cout << *mp->pa << " ";
					ls.pop();
					//delete mp; //Ϊʲô���ﲻ���ͷ���ָ���أ�
				}
			}
		}
		else  //c������,��ֱ����ʾ
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

//ջ��Ӧ��--��׺���ʽ���
//������
//���֣�ֱ�ӽ�ջ�� ���ţ��ȴ�ջ�е����Ҳ��������ٴ�ջ�е���������������ݷ��Ž������㣬��󽫽����ջ�����ձ���������ջ�е�Ψһ������Ϊ��������
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
	//��charǿתΪint���õ�ASCIIֵ
	int m = (int)c;
	//ASCIIֵ��ȥ41�õ�ʵ��ֵ
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
		if (IsNumber(*c))  //����
		{
			//�ȴ�ջ�е����Ҳ�����
			int right = ((myint*)ls.front())->value;
			//cout << "right:" << right << " ";
			ls.pop();
			//�ȴ�ջ�е����������
			int left = ((myint*)ls.front())->value;
			//cout << "left:" << left << " ";
			ls.pop();
			//����һ��mychar��Ž��
			myint* mc = new myint();
			//�����������������
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
				cout << "error��ls��ȡһ��������������֣�" << endl;
			}
			//�����ѹ��ջ��
			ls.push((listStackNode*)mc);
		}
		else   //����ֱ�ӽ�ջ
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

//�������ݹ����
void test12()
{
	binaryTree bt;
	//�������
	//bt.createtree();
	//cout << endl;
	////�������
	//bt.createtree();
	//cout << endl;
	//�������
	bt.createtree();
	cout << endl;
}

//�������ǵݹ����
void test13()
{
	binaryTree bt;
	bt.createtree();
	cout << endl;
}

//����������
//ͨ����������������������ȷ��һ����
//ͨ����������ͺ����������ȷ��һ����
//ͨ�����������#�ŷ����Դ���һ����
//ͨ��һ����������Ľ�����޷�ȷ��һ������
//ͨ����������ͺ������������ȷ��һ����
void test14()
{

}


//����
void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
//ð�����򣬴�С����
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
//ð������Ľ��棬��С����
void bub1(int* arr, int length)
{
	int flag = 0;  //falg==0��ʾ���л�û���������
	for (int i = 0; i < length && flag == 0; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			flag = 1;  //����֮ǰ��length-i-1~length-1������Ѿ�������ɣ����Ǽ�����0~length-i-1������Ѿ�û����Ҫ��������������ˣ��������һֱû��ִ��if�еĴ��룬��ô���ǵļ�����������flag����Ϊ1�����Խ���ѭ��
			if (arr[j] > arr[j + 1])
			{
				flag = 0;   //���������е�����ʱ�����ʾ��0~length-i-1����л�������Ҫ��������У����flag�趨Ϊ0
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
//ѡ�����򣬴�С����--�����±�Ϊi��i��ʼΪ0����Ԫ��Ϊ��С��ѭ�����Һ����ȵ�i��Ԫ��С��Ԫ�أ�������Ԫ�ص��±긳��min��ѭ���������ж�min�ǲ��ǵ�����i��������ǣ������minλ�õ�Ԫ������i֮��ĸ�С��Ԫ�أ����߽���λ�ã�����Ļ���iλ�õ�Ԫ���Ǻ�����������С��
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
//�������򣬴�С���������ʵҲ��һ��ѡ��������������֮�����ڣ����ȣ������ж���iλ�ã��Ƿ�iλ�õ�������ǰһ��λ����С�����С����ô��i-1��ʼ���ұ�iλ������С��Ԫ�أ�����j=i-1~0�������У���һ��jλ�õ�Ԫ��С��iλ��Ԫ�أ���ô�Ͱ�iλ�õ�Ԫ�ز��뵽j+1��λ�ã�����ͱ�ʾ0~i-1��������У�iλ��Ԫ����С���ͽ�����뵽λ��0��
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
			//��������ѭ�������һ��j--��������Ǹ�ֵ��ʱ��Ӧ����j+1��λ���ϸ�ֵ
			arr[j+1] = temp;
		}
	}
}
//ϣ�����򣬴�С����--�����Ҫ������ѭ���ָ��˼�룬increaser�Ƿָ����������Ϊ���������Ƚ�һ�����������зָ�Ϊincreaser���������У�Ȼ���ÿһ��ֱ���в�������Ȼ�������������±��ʽ����increaser��ֱ��increaser=1��ע�⣬��increaser=1ʱ������Ҫ����һ�β�����������ĳ���ʹ�õ���do whileѭ�����������������increaser=1ʱ�Ĳ�������Ȼ�����˳�ѭ����
void ShellSort(int* arr, int length)
{
	int increaser = length;
	int i, j, k;
	do
	{
		//ȷ����������
		increaser = increaser / 3 + 1;   //�������±��ʽ
		for (i = 0; i < increaser; i++)  //����֮���ܵ�����Ϊincreaser
		{
			//�Ե�i����в�������,����Ԫ�ؼ��Ϊincreaser
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

//��������--��������1���趨��׼�����趨һ����׼��֮���ȴ�������Ѱ��С�ڻ�׼����Ԫ�أ� 2���ڿӺͻ��� 3���ָ�ݹ�
void QuickSort(int* arr, int start, int end)
{
	int i = start;
	int j = end;

	//�趨��׼�����ڳ�ʼ��
	int temp = arr[i];

	if (i < j)
	{
		while(i < j)
		{
			//�������������һ��С��temp��Ԫ��
			while (i < j && arr[j] >= temp)
			{
				j--;
			}
			//���
			if (i < j)
			{
				arr[i] = arr[j];
				i++;
			}

			//�ٴ������ұ�����һ������temp��Ԫ��
			while (i < j && arr[i] < temp)
			{
				i++;
			}
			//���
			if (i < j)
			{
				arr[j] = arr[i];
				j--;
			}
		}
		//�����׼��,���ʱ��i==j����ˣ����iλ�û���jλ�ö�һ��
		arr[j] = temp;

		//�Ի�������п�������
		QuickSort(arr, start, i - 1);
		//�Ի���Ҳ���п�������
		QuickSort(arr, i + 1, end);
	}
}


//�ϲ��㷨 ��С����--���ȸ������������ҵ��������е�ͷβԪ��λ�ã�Ȼ������whileѭ���Ƚ��������е�ͷԪ�ش�С������С��Ԫ�ش洢����ʱ�ռ�temp�У�һֱ����������ȫ�����洢��temp��Ϊֹ��Ȼ��temp�е�Ԫ�ظ��ǵ�arr����ԭλ�ô���
void combine(int* arr, int start, int mid, int end, int* temp)
{
	int length = 0;   //length��ʾtemp�д洢��Ԫ�ظ���
	//i_start��ʾ��һ�����е�ͷԪ��λ��
	int i_start = start;
	int i_end = mid;
	//j_start��ʾ�ڶ������е�ͷԪ��λ��
	int j_start = mid + 1;
	int j_end = end;
	while (i_start <= i_end || j_start <= j_end)
	{
		//��ʼ�Ƚϴ��ϲ������������е�Ԫ��
		if (arr[i_start] < arr[j_start] && i_start <= i_end)   //��һ�������е�Ԫ�رȵڶ��������е�Ԫ��С
		{
			temp[length] = arr[i_start];   //����һ�������е�Ԫ�ط���temp�д洢
			length++;
			i_start++;
		}
		if (arr[i_start] >= arr[j_start] && j_start <= j_end)   //�ڶ��������е�Ԫ�رȵ�һ�������е�Ԫ��С
		{
			temp[length] = arr[j_start];   //���ڶ��������е�Ԫ�ط���temp�д洢
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
	//��temp�е�Ԫ�ظ��ǵ�arr��
	for (int i = 0; i < length; i++)
	{
		arr[start + i] = temp[i];
	}
}
//�鲢���򣬴�С����--����һ�ַ�Ϊ�����ĵݹ��㷨��1����������0~midλ�õ�Ԫ�ؽ��й鲢������ 2����������mid+1~endλ�õ�Ԫ�ؽ��й鲢������  3���Դ����������ֽ��кϲ�
void MergeSort(int* arr, int start, int end, int* temp)
{
	if(start >= end)
	{
		return;
	}
	int mid = (start + end) / 2;
	//�ȶ�arr��λ��Ϊ0~mid��Ԫ�ؽ��д���
	MergeSort(arr, start, mid, temp);
	//�ٶ�arr��λ��Ϊmid+1~end��Ԫ�ؽ��д���
	MergeSort(arr, mid + 1, end, temp);
	//�ϲ�
	combine(arr, start, mid, end, temp);
}

//�������㷨
/*
* arr�Ǵ�����������
* index�ǵ�����ʼ��Ԫ���±�
* length�ǵ�ǰ����ĳ���
*/
void AdjustHeap(int* arr, int index, int length)
{
	int root = index;  //root��ʾ��ǰ���λ��
	int lchild = 2 * index + 1;   //lchild�ǵ�ǰ�������ӽ��
	int rchild = 2 * index + 2;   //rchild�ǵ�ǰ�������ӽ��

	if (lchild<length && arr[lchild]>arr[root]) 
	{
		root = lchild;
	}
	if (rchild<length && arr[rchild]>arr[root])
	{
		root = rchild;
	}
	if (root != index)   //�����ʾ��root�����˱仯�����Ҫ��rootλ�õ�������ԭʼindexλ�õ����ݽ��н���
	{
		swap(arr[root], arr[index]);
		AdjustHeap(arr, root, length); //���ڽ���֮�󣬿��ܽ���֮���rootλ��Ԫ�ؿ���С�ڵ�ǰλ�õ����ӽ������ӽ��λ�õ�Ԫ�أ���˻���Ҫ���еݹ�
	}
}

//�����򣬴�С����
void HeapSort(int* arr, int length)
{
	//��ʼ����
	for (int i = length / 2 - 1; i >= 0; i--)
	{
		//�����ѣ��������ϵ�����ӦΪi�ǴӴ�С��ʼ��
		AdjustHeap(arr, i, length);
	}
	//�������е�һ��λ�õ�Ԫ�غ����һ��λ�õ�Ԫ��
	for (int i = length - 1; i >= 0; i--)
	{
		//�������е�һ��λ�õ�Ԫ�غ����һ��λ�õ�Ԫ��
		swap(arr[i], arr[0]);
		//�������µ�����ֱ�Ӵ�0��ʼ���жѵ���
		AdjustHeap(arr, 0, i);
	}
}

#define length1  10

//�������麯��
void CreateArr(int* arr, int len)
{
	srand((unsigned int)time(0));
	for (int i = 0; i < len; i++)
	{
		arr[i] = rand() % len;
	}
}

//��ʾ���麯��
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

	//ð������ð��������ص���������������������β��
	//bub(arr, length1);

	//�Ľ���
	bub1(arr, length1);

	//ѡ������
	//SelectSort(arr, length1);

	//��������--���������в��뵽����������
	//InserterSort(arr, length1);

	//ϣ������
	//ShellSort(arr, length1);

	//��������
	QuickSort(arr, 0, length1 - 1);

	//�鲢����
	////������ʱ�ռ�
	//int* temp = new int[length1];
	//MergeSort(arr, 0, length1 - 1, temp);
	////������ʱ�ռ�
	//delete[] temp;

	//������
	HeapSort(arr, length1);

	ArrShow(arr, length1);
}

int main()
{
	//test01();         //��̬����
	//test02();         //����
	//test03();         //��ҵ����
	//test04();         //ѭ������
	//test05();         //Լɪ������
	//test06();         //˳��ջ
	//test07();         //ջ����ʽ�洢
	//test08();         //���е�˳��洢
	//test09();         //ջ��Ӧ��--�ͽ�ƥ������
	//test10();         //ջ��Ӧ��--��׺���ʽתΪ��׺���ʽ
	//test11();         //ջ��Ӧ��--��׺���ʽ���� 
	//test12();         //�������ݹ�����������ĸ߶ȡ�Ҷ���������������������ռ�
	//test13();         //�������ǵݹ����
	//test14();         //�������Ĵ���
	//test15();         //����--ð�����򡢸Ľ���ð�ݡ�ѡ�����򡢲�������ϣ�����򡢿������򡢹鲢���򡢶�����


	system("pause");
	return 0;
}