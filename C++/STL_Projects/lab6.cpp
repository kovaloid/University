/*
lab6-algorithms
������� �����, 23504/4, 2013 ���

�������:
1. �������� ���������, ������� ��������� ��������� ��������:
  a. ������ ���������� ���������� �����
  b. �������� �����, ������ ��������� ������������������ �������� ����������� ��������� �/��� 
     ������� ��������� �/��� ��������� ����� ������
  c. ������� ������ ���� �������������� � ������ ��� ���������� (������� � ����, ��� ���� � �� �� 
     ����� ����� �������������� � ������ ������ ���� ���)

2. �������� ���������, ������� ��������� ��������� �������� (��� �������� ������ ����������� � 
   ������� ����������� ����������):
  a. ��������� ������ ��������������� ��������. �������������� ������ ����� ���� �������������, 
     ���������, ��������������� ��� ���� ����������. ��������� ����������� �������������� ������  
	 ���������� ����, 
  b. ������������ ����� ���������� ������ ���� ����� ������������ � ������� (��� ����������� 
     ��������� � ������ ����� 3, ������� 4 � �.�.)
  c. ������������ ���������� �������������, ��������� � ��������������� � �������
  d. ������� ��� ������������� 
  e. �� ��������� ����� ������� ������� vector<Point>, ������� �������� ���������� ����� �� ������ 
     (�����) ������ ������, �.�. ������ ������� ����� ������� �������� ���������� ����� �� ������� 
	 ������ ������, ������ ������� ����� ������� �������� ���������� ����� �� ������� ������ ������ 
	 � �.�.
  f. �������� ������ ���, ����� �� �������� � ������ ��� ������������, ����� ��� ��������, � ����� 
     ��������������.
  g. ������������� ������ ����� ������� ����� ������

�������������� ������ �������� ��������� ����������:
typedef  struct 
{
	int vertex_num;    // ���������� ������, ��� ������������ 3, ��� �������� � 
	                   // �������������� 4, ��� ���� ��������� 5
    vector<Point> vertexes;    // ������ ���������� ���������� ������ ������
	                           // ��� ������������ �������� 3 ��������
	                           // ��� �������� � �������������� �������� 4 ��������
	                           // ��� ������������� 5 ���������
} Shape;

typedef struct
{
	int x,y;
} Point;

���������: ����� ���������� ������������� � ���� ������ ����� ��������� ��� �������� ��������� 
� ���������� �������, ������� ��������� ����������.
*/

#include <iostream>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>

#define SIZE 10

using namespace std;

typedef struct
{
	int x,y;
} Point;

typedef struct 
{
	int vertex_num;
	vector<Point> vertexes;
} Shape;

Shape input(Shape &sh)
{
	Point pnt;
	sh.vertex_num=rand()%3+3;
	if (sh.vertex_num==3)  // �����������
	{
		for (int i=0; i<3; i++)
		{
			pnt.x=rand()%SIZE;
			pnt.y=rand()%SIZE;
			sh.vertexes.push_back(pnt);
		}
	}
	else if (sh.vertex_num==4)
	{
		if (rand()%2==0)  // �������������
		{
				pnt.x=rand()%SIZE;
				pnt.y=rand()%SIZE;
				int width=rand()%SIZE;
				int hight=rand()%SIZE;
				sh.vertexes.push_back(pnt);
				pnt.x=pnt.x+width;
				sh.vertexes.push_back(pnt);
				pnt.y=pnt.y+hight;
				sh.vertexes.push_back(pnt);
				pnt.x=pnt.x-width;
				sh.vertexes.push_back(pnt);
		}
		else   // �������
		{
				pnt.x=rand()%SIZE;
				pnt.y=rand()%SIZE;
				int len=rand()%SIZE;
				sh.vertexes.push_back(pnt);
				pnt.x=pnt.x+len;
				sh.vertexes.push_back(pnt);
				pnt.y=pnt.y+len;
				sh.vertexes.push_back(pnt);
				pnt.x=pnt.x-len;
				sh.vertexes.push_back(pnt);
		}
	
	}
	else if (sh.vertex_num==5)  // ������������
	{
		for (int i=0; i<5; i++)
		{
			pnt.x=rand()%SIZE;
			pnt.y=rand()%SIZE;
			sh.vertexes.push_back(pnt);
		}
	}
	return sh;
}

bool cv3(Shape &sh)
{
	if (sh.vertex_num==3) return true;
	else return false;
}

bool cv4_rectangle(Shape &sh)
{
	if (sh.vertex_num==4)
	{
		int lenx=sh.vertexes[1].x-sh.vertexes[0].x;
		int leny=sh.vertexes[2].y-sh.vertexes[1].y;
		if (lenx!=leny) return true;
		else return false;
	}
	else return false;
}

bool cv4_square(Shape &sh)
{
	if (sh.vertex_num==4)
	{
		int lenx=sh.vertexes[1].x-sh.vertexes[0].x;
		int leny=sh.vertexes[2].y-sh.vertexes[1].y;
		if (lenx==leny) return true;
		else return false;
	}
	else return false;
}

bool cv5(Shape &sh)
{
	if (sh.vertex_num==5) return true;
	else return false;
}

Shape output(Shape &sh)
{
	cout<<"---------------"<<endl;
	if (cv3(sh)==true) cout<<"figure: triangle"<<endl;
	else if (cv4_rectangle(sh)==true) cout<<"figure: rectangle"<<endl;
	else if (cv4_square(sh)==true) cout<<"figure: square"<<endl;
	else if (cv5(sh)==true) cout<<"figure: pentagon"<<endl;
	else cout<<"error"<<endl;
	cout<<"vertex_num: "<<sh.vertex_num<<endl;
	if (sh.vertex_num==3)
		cout<<"x1: "<<sh.vertexes[0].x<<"  "
			<<"y1: "<<sh.vertexes[0].y<<endl
			<<"x2: "<<sh.vertexes[1].x<<"  "
			<<"y2: "<<sh.vertexes[1].y<<endl
			<<"x3: "<<sh.vertexes[2].x<<"  "
			<<"y3: "<<sh.vertexes[2].y<<endl;
	else if (sh.vertex_num==4)
		cout<<"x1: "<<sh.vertexes[0].x<<"  "
			<<"y1: "<<sh.vertexes[0].y<<endl
			<<"x2: "<<sh.vertexes[1].x<<"  "
			<<"y2: "<<sh.vertexes[1].y<<endl
			<<"x3: "<<sh.vertexes[2].x<<"  "
			<<"y3: "<<sh.vertexes[2].y<<endl
			<<"x4: "<<sh.vertexes[3].x<<"  "
			<<"y4: "<<sh.vertexes[3].y<<endl;
	else if (sh.vertex_num==5)
		cout<<"x1: "<<sh.vertexes[0].x<<"  "
			<<"y1: "<<sh.vertexes[0].y<<endl
			<<"x2: "<<sh.vertexes[1].x<<"  "
			<<"y2: "<<sh.vertexes[1].y<<endl
			<<"x3: "<<sh.vertexes[2].x<<"  "
			<<"y3: "<<sh.vertexes[2].y<<endl
			<<"x4: "<<sh.vertexes[3].x<<"  "
			<<"y4: "<<sh.vertexes[3].y<<endl
			<<"x5: "<<sh.vertexes[4].x<<"  "
			<<"y5: "<<sh.vertexes[4].y<<endl;
	cout<<endl;
	return sh;
}

Point new_vec(Shape &sh, Point &pn)
{
	int r;
	if (sh.vertex_num==3) r=rand()%3;
	else if (sh.vertex_num==4) r=rand()%4;
	else if (sh.vertex_num==5) r=rand()%5;
	return sh.vertexes[r];
}

struct cmp
{
    bool operator()(Shape &a, Shape &b) const
    {
		return a.vertex_num < b.vertex_num;
    }
};

int main()
{
	int tn;
start:
	cout<<"task number: "; cin>>tn;
if (tn==1)
{
	ifstream f("input6.txt", ios::in);

	f.seekg (0, std::ios::end);
	int size_of_file=f.tellg();
	f.seekg (0, std::ios::beg);

	if (!f) cout<<"can't open file to read"<<endl<<endl;
	else cout<<"contents of file <input6.txt> with size: "<<size_of_file<<endl<<endl;

	char *buf=new char[size_of_file];
	buf[size_of_file]='\0';
	f.read(buf, size_of_file);

	string str(buf);
	cout<<str;

	vector<string> v;
	int i;
	while((i=str.find_first_of("\t\v\n\r "))!=string::npos) 
	{
		v.push_back(str.substr(0, i)); 
		str=str.substr(i+1);
	}
	v.push_back(str);

	v.erase(remove(v.begin(), v.end(), ""),v.end());

	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());

	copy(str.begin(),str.end(),ostream_iterator<char>(cout));
	cout<<"\n\nedited text: "<<endl<<endl;
	copy(v.begin(),v.end(),ostream_iterator<string>(cout,"  "));
	f.close();
}

//--------------------------------------------------------------
else if (tn==2)
{
	vector<Shape> shv(50);
	cout<<endl<<endl;

	for_each(shv.begin(),shv.end(),input);

	for_each(shv.begin(),shv.end(),output);

	int f3=count_if(shv.begin(),shv.end(),cv3);
	int f4_rec=count_if(shv.begin(),shv.end(),cv4_rectangle);
	int f4_sq=count_if(shv.begin(),shv.end(),cv4_square);
	int f5=count_if(shv.begin(),shv.end(),cv5);

	cout<<"\nall vertexes of figures: "<<f3*3+f4_rec*4+f4_sq+f5*5<<endl<<endl;
	cout<<"\nnumber of triangles: "<<f3<<endl
		<<"number of rectangles: "<<f4_rec<<endl
		<<"number of squares: "<<f4_sq<<endl
		<<"number of pentagons: "<<f5<<endl<<endl;

	shv.erase(remove_if(shv.begin(),shv.end(),cv5),shv.end());
	for_each(shv.begin(),shv.end(),output);

	f3=count_if(shv.begin(),shv.end(),cv3);
	f4_rec=count_if(shv.begin(),shv.end(),cv4_rectangle);
	f4_sq=count_if(shv.begin(),shv.end(),cv4_square);
	f5=count_if(shv.begin(),shv.end(),cv5);
	cout<<"\nnumber of triangles: "<<f3<<endl
		<<"number of rectangles: "<<f4_rec<<endl
		<<"number of squares: "<<f4_sq<<endl
		<<"number of pentagons: "<<f5<<endl<<endl;

	vector<Point> pv(shv.size());
	transform(shv.begin(),shv.end(),pv.begin(),pv.begin(),new_vec);

	cout<<"vector<Point>"<<endl;
	for (int n=0; n<shv.size(); n++)
		cout<<"x: "<<pv[n].x<<"    y: "<<pv[n].y<<endl;

	cout<<endl<<"sort: "<<endl;
	sort(shv.begin(), shv.end(), cmp());  // ���������� �� ��������� ������

 // ���������� ��������� � ���������������

	vector<Shape> tmp_shv;
	for (vector<Shape>::iterator iter=shv.begin(); iter!=shv.end(); iter++)
	{
		if (cv4_rectangle(*iter)==true)
		{
			tmp_shv.push_back(*iter);
		}
	}
	shv.erase(remove_if(shv.begin(),shv.end(),cv4_rectangle),shv.end());
	shv.insert(shv.end(), tmp_shv.begin(), tmp_shv.end());

	for_each(shv.begin(),shv.end(),output);
}
else goto start;

	getch();
	return 0;
}