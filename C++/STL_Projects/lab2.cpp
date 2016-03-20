/*
lab2-string
������� �����, 23504/4, 2013 ���

�������:
����������� ���������, ������� ������ ������� ���������:
1.	��������� ���������� ���������� �����. ���� ����� ���������:
	a.	����� � ������� �� ��������� �������� � ��������� ����, � ����� ����, ������ ����� ������ 
		���� �� ����� 20 ��������
	b.	����� ���������� � �.�, �,� �!� �?� �:� �;�
	c.	���������� ������� � ������, ���������, ������ ����� ������.
2.	��������������� ����� ��������� �������:
	a.	�� ������ ����  ���������� �������� �������� �� �������
	b.	�� ������ ���� ������ ����� ������ �������
	c.	����� ������ � ������ ���������� �� ������ ���� �������
	d.	����� ����� ���������� ������ ������ ���� ������
	e.	����� ������ ����� 10 �������� ���������� �� ����� �Vau!!!�
3.	������������� ���������� ����� � ����� ������, ������ �� ������� �������� ����� ���������� ����� 
	(����� ������ ������� ���������� � ������) � �� ������ �� ��������� 40 ��������.

���������:
�	��� �������� ����� �������� ������ ����� ������������ ���� ������
�	����� ������� ������ ���������� ������� ������������� ����� ���� ���������, �������� ����� ����������
�	��� �������� �������������� ����� ����� ������������ vector<string>
*/

#include <conio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

string punct(".,!?:;");
string probel("\b\f\n\r\t\v");

string delete_char_other_than_probel(const string &s,int &flag)
{
    if (s.length()==0) return s;
    int begin = s.find_first_of(probel);
	if (begin==string::npos) 
	{
		flag=1;
		return s;
	}
	return string(s,0,begin)+" "+string(s,begin+1,string::npos);
}

string delete_more_one_probel(string &s,int &flag,int &sp)
{
    if (s.length()==0) return s;
    int begin = s.find(" ",sp);
	sp=begin+1;
	if (begin==string::npos) 
	{
		flag=1;
		return s;
	}
	if (s[sp]==' ')
	{
		int i=0;
		while (s[sp+i]==' ') i++;
			s.erase(sp, i);
	}
	return s;
}

string probel_next_to_punct(string &s,int &flag,int &sp)
{
    if (s.length()==0) return s;
    int begin = s.find_first_of(punct,sp);
	sp=begin+1;
	if (begin==string::npos) 
	{
		flag=1;
		return s;
	}
	if (s[sp-2]==' ') s.erase(sp-2, 1);
	if (s[sp-1]!=' ') s.insert(sp-1, " ");
	return s;
}

string replace_vau(string &s,int &flag,int &sp)
{
	if (s.length()==0) return s;
	int begin = s.find_first_not_of(punct+probel+" ",sp);
	int end = s.find_first_of(punct+probel+" ",sp);

	if (end<begin)
	{
		int i=0;
		while (end<begin)
		{
			end = s.find_first_of(punct+probel+" ",sp+i);
			i++;
			if (end == string::npos)
			{
				flag=1;
				return s;
			}
		}
	}

	if ((begin == string::npos) || (end == string::npos))
	{
		flag=1;
		return s;
	}

	int len=end-begin;

	if (len>10)
	{
		s.replace(sp,len,"VAU!!!");
		sp=end-6+1;
	}
	else sp=end+1;

	return s;
}

void main()
{
	ifstream inpf("input2.txt", ios::in);

	inpf.seekg (0, std::ios::end);
	int size_of_file=inpf.tellg();
	inpf.seekg (0, std::ios::beg);

	if (!inpf) cout<<"can't open file to read"<<endl<<endl;
	else cout<<"contents of file <input2.txt> with size: "<<size_of_file<<endl<<endl;

	char *buf=new char[size_of_file+1L];
	buf[size_of_file]='\0';
	inpf.read(buf, size_of_file);

	string str(buf);
	cout<<str;

//a. �� ������ ����  ���������� �������� �������� �� �������
	int fl=0, strp=0;
	while (fl!=1) str=delete_char_other_than_probel(str,fl);

//b. �� ������ ���� ������ ����� ������ �������
	fl=0; strp=0;
	while (fl!=1) str=delete_more_one_probel(str,fl,strp);

//c. ����� ������ � ������ ���������� �� ������ ���� �������
//d. ����� ����� ���������� ������ ������ ���� ������
	fl=0; strp=0;
	while (fl!=1) str=probel_next_to_punct(str,fl,strp);

//e. ����� ������ ����� 10 �������� ���������� �� ����� �Vau!!!�
	fl=0; strp=0;
	while (fl!=1) str=replace_vau(str,fl,strp);

//3. ������������� ���������� ����� � ����� �����
	vector<string> res;
	string new_str;
	int count=0,begin=0,end=40;

	while (end < str.size())
	{
		if (str[end]==' ')
		{
			new_str=str.substr(begin,end-begin);
			begin=end+1;
		}
		else
		{
			int i=0;
			while (str[end-i]!=' ') i++;
			new_str=str.substr(begin,end-begin-i);
			begin=end-i+1;
		}
		res.push_back(new_str);
		end=begin+40;
		count++;
	}
	new_str=str.substr(begin,string::npos);
	res.push_back(new_str);
	count++;

	cout<<endl<<endl<<"edited text:"<<endl<<endl;
	for (int n=0; n<count; n++) cout<<res[n]<<endl;

	inpf.close();
	getch();
}