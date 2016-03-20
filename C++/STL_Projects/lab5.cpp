/*
lab5-algorithm-sort
������� �����, 23504/4, 2013 ���

�������:
�������� ���������, ������� ��������� ��������� ��������:
a. ��������� vector<DataStruct> ����������� DataStruct, ��� ���� key1 � key2, ������������ 
��������� ������� � ��������� �� -5 �� 5, str ����������� �� ������� (������� �������� 10 
������������ �����, ������ ������ ������������ ��������� �������)
b. ������� ���������� ������ �� ������
c. ��������� ������ ��������� �������:
	i. �� ����������� key1
	ii. ���� key1 ����������, �� �� ����������� key2
	iii. ���� key1 � key2 ����������, �� �� ����������� ������ ������ str
d. ������� ���������� ������ �� ������

DataStruct ���������� ��������� �������:
typedef struct
{
	int key1;
	int key2;
	string str;
} DataStruct;
*/

#include <iostream>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>

#define SIZE 16

using namespace std;

typedef struct
{
	int key1;
	int key2;
	string str;
} DataStruct;

struct key1_cmp
{
    bool operator()(const DataStruct& a, const DataStruct& b) const
    {
        return a.key1 < b.key1;
    }
};

struct key2_cmp
{
    bool operator()(const DataStruct& a, const DataStruct& b) const
    {
		if (a.key1 == b.key1) return a.key2 < b.key2;
        return a.key1 < b.key1;
    }
};

struct str_cmp
{
    bool operator()(const DataStruct& a, const DataStruct& b) const
    {
		if ((a.key1 == b.key1) && (a.key2 == b.key2)) return a.str.size() < b.str.size();
        return a.key1 < b.key1;
    }
};

void out_vec(vector<DataStruct> &vec)
{
	cout<<"_key1____key2____str_"<<endl;
	for (int i=0; i<SIZE; i++)
		cout<<"  "<<vec[i].key1<<"      "<< vec[i].key2 <<"      "<<vec[i].str<<endl;
	cout<<endl;
}

int main()
{
	vector<DataStruct> vec(SIZE);
	vector<DataStruct>::iterator iter;
	vector<string> s;

	ifstream f("input5.txt", ios::in);
	if (!f) {cout<<"can't open file"; getch(); return 0;}

	char buf[20];
	while (!f.eof())
	{
		f.getline(buf,20);
		s.push_back(buf);
	}

	for (int i=0; i<SIZE; i++)
	{
		vec[i].key1=(rand()%11-5);
		vec[i].key2=(rand()%11-5);
		vec[i].str=s[rand()%SIZE];
	}
	out_vec(vec);

//i.	�� ����������� key1
	sort(vec.begin(), vec.end(), key1_cmp());
	out_vec(vec);

//ii.	���� key1 ����������, �� �� ����������� key2
	sort(vec.begin(), vec.end(), key2_cmp());
	out_vec(vec);

//iii.	���� key1 � key2 ����������, �� �� ����������� ������ ������ str
	sort(vec.begin(), vec.end(), str_cmp());
	out_vec(vec);

	getch();
	return 0;
}