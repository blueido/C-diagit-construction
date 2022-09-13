#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T1,class T2>
class police
{
public:
	T1 m_name;
	T2 m_age;
	police(T1 name, T2 age);
	void showInfo();
	
};

template <class T1, class T2>
police<T1, T2>::police(T1 name, T2 age)
{
	this->m_age = age;
	this->m_name = name;
}
template <class T1, class T2>
void police<T1, T2>::showInfo()
{
	cout << "Ãû×Ö£º" << this->m_name << " " << "Äê¼Í£º" << this->m_age << endl;
}