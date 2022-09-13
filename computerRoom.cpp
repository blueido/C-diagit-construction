#include "computerRoom.h"


//默认构造
computerRoom::computerRoom()
{

}

//有参构造
computerRoom::computerRoom(int id, int number, int rest)
{
	this->m_id = id;
	this->m_number = number;
	this->m_rest = rest;
}

//析构函数
computerRoom::~computerRoom()
{

}
