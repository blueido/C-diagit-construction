#include "OrderFile.h"

//构造函数
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(APPLY_FILE, ios::in);

	string time;  //日期
	string timePeriod;  //时段
	string id;     //学号
	string name;   //姓名
	string room;   //机房号码
	string rest;      //机房剩余
	string status; //预约状态

	string data;
	int pos = -1;
	int start = 0;
	int count = 0;

	ifs >> data;

	this->m_size = 0;
	while (!data.empty())
	{
		pos = data.find(",", start);
		count++;
		if (pos == -1)
		{
			cout << "文件读取完毕！" << endl;
			break;
		}
		if (count == 1)
		{
			time = data.substr(start, pos - start);
			vs.push_back(time);
		}
		else if (count == 2)
		{
			timePeriod = data.substr(start, pos - start);
			vs.push_back(timePeriod);
		}
		else if (count == 3)
		{
			id = data.substr(start, pos - start);
			vs.push_back(id);
		}
		else if (count == 4)
		{
			name = data.substr(start, pos - start);
			vs.push_back(name);
		}
		else if (count == 5)
		{
			room = data.substr(start, pos - start);
			vs.push_back(room);
		}
		else if (count == 6)
		{
			rest = data.substr(start, pos - start);
			vs.push_back(rest);
		}
		else if (count == 7)
		{
			status = data.substr(start, pos - start);
			//清空计数器
			count = 0;
			vs.push_back(status);
			//更新key值
			this->m_size++;
			//插入vs到map容器中
			this->m_order.insert(make_pair(this->m_size, vs));
			//清空临时容器
			vs.clear();
		}
		start = pos + 1;
	}
	ifs.close();

}

//更新预约记录
void OrderFile::updateOrder()
{
	ofstream ofs;
	ofs.open(APPLY_FILE, ios::trunc);
	ofs.close();

	if (this->m_order.size() == 0)
	{
		cout << "文件为空！" << endl;
		return;
	}

	ofstream ofs1;
	ofs1.open(APPLY_FILE, ios::out);

	for (map<int, vector<string>>::iterator it = this->m_order.begin(); it != this->m_order.end(); it++)
	{
		for (vector<string>::iterator vsi = (it->second).begin(); vsi != (it->second).end();vsi++)
		{
			ofs1 << *vsi << ",";
		}
		cout << endl;
	}
	ofs1.close();
}