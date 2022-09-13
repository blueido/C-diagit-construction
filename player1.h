#pragma once
#include <iostream>
#include <string>

using namespace std;

class player1
{
public:
	player1(int id, int age, string name, string sex, double grade);
	int m_id;
	int m_age;
	double m_grade;
	string m_name;
	string m_sex;
};