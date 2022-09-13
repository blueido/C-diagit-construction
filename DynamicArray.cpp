#include "DynamicArray.h"

//动态增长内存，策略 将存放数据的内存放在堆上
//当需要扩展内存时，1、申请新空间，2、拷贝数据，3、释放旧内存
//上面三步需要考虑 容量capacity、当前数组的数据size

//构造函数
dynamicArray::dynamicArray()
{
	this->m_capacity = 1;
	this->m_pArray = NULL;
	this->m_size = 0;
}

dynamicArray::dynamicArray(int capacity)
{
	this->m_capacity = capacity;
	this->m_size = 0;
	//为类申请空间的时候，先利用malloc，后续再查找关于利用new 来进行类的空间开辟的方法
	//this->m_pArray = (int*)malloc(sizeof(int) * this->m_capacity);   //利用malloc
	this->m_pArray = new int[sizeof(int) * this->m_capacity];          //利用new
}

//插入Push_Back
void dynamicArray::push_back(int value)
{
	if (this->m_pArray == NULL)
	{
		return;
	}

	//判断空间内存是否足够
	if (this->m_size == this->m_capacity)
	{
		//1、申请新空间
		//int* newspace = (int*)malloc(sizeof(int) * this->m_capacity * 2);   //利用malloc
		int* newspace = new int[sizeof(int) * this->m_capacity * 2];          //利用new 
		//2、拷贝数据
		memcpy(newspace, this->m_pArray, sizeof(int) * this->m_capacity);
		//3、释放旧空间
		delete this->m_pArray;

		//更新容量
		this->m_capacity = this->m_capacity * 2;
		this->m_pArray = newspace;
	}

	//插入新元素
	this->m_pArray[this->m_size] = value;
	this->m_size++;

}

//删除erase
void dynamicArray::era_pos(int pos)  //按位置删除，利用前移法删除
{
	//数组已经为空
	if (this->m_pArray == NULL)
	{
		return;
	}

	if (pos > 0 && pos <= this->m_size)
	{
		for (int i = pos; i < this->m_size; i++)
		{
			this->m_pArray[i - 1] = this->m_pArray[i];  //前移法
		}
		this->m_size--;
	}
	else
	{
		return;
	}
}

void dynamicArray::era_value(int value)  //按值删除
{
	//数组已经为空
	if (this->m_pArray == NULL)
	{
		return;
	}

	int pos = -1;
	//通过findIt函数来查找value值的位置
	pos = this->findIt(value);
	if (pos == -1)
	{
		return;
	}
	else
	{
		//利用按位置删除函数来删除value
		this->era_pos(pos);
	}
}

//查找
int dynamicArray::findIt(int value)
{
	//数组已经为空
	if (this->m_pArray == NULL)
	{
		return -1;
	}
	int pos = -1;
	for (int i = 0; i < this->m_size; i++)
	{
		if (this->m_pArray[i] == value)
		{
			//找到后，将value的位置记录
			pos = i + 1;
			break;
		}
	}
	return pos;
}


//清空
void dynamicArray::clearIt()
{
	if (this->m_pArray == NULL)
	{
		return;
	}
	this->m_size = 0;
}

//显示
void dynamicArray::show()
{
	if (this->m_pArray == NULL)
	{
		return;
	}
	for (int i = 0; i < this->m_size; i++)
	{
		cout << this->m_pArray[i] << " ";
	}
	cout << endl;
}

//获取容量
int dynamicArray::get_capacity()
{
	if (this->m_pArray == NULL)
	{
		return 0;
	}
	return this->m_capacity;
}

//获取元素数量
int dynamicArray::get_size()
{
	if (this->m_pArray == NULL)
	{
		return 0;
	}
	return this->m_size;
}

//析构函数
dynamicArray::~dynamicArray()
{
	if (this->m_pArray != NULL)
	{
		delete [] this->m_pArray;
		this->m_pArray = NULL;
	}
	this->m_capacity = 0;
	this->m_size = 0;
}
