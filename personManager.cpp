#include "personManager.h"

using namespace std;
//���溯��
void personManager::save()
{
	ofstream ofile1;
	ofile1.open(APPLY_FILE, ios::out | ios::app);
	for (vector<Apply>::iterator it = va.begin(); it != va.end(); it++)
	{
		ofile1 << (*it).m_time << "," << (*it).m_timePeriod << "," << (*it).m_room << ",";
	}
	ofile1.close(); 
	cout << "������ϣ�" << endl;
}

void personManager::statusUpdate()
{
	
}
