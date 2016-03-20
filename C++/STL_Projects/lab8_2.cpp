/*
lab8-functor
������� �����, 23504/4, 2013 ���

�������:
2.	����������� ���������, �������:
	a.	��������� �������� �������������� ����� ��������� ��:
		i.	����� Shape. 
			1.	�������� ���������� � ��������� ������ ������ (���������� x � y).
			2.	�������� ����� IsMoreLeft, ����������� ���������� ����������� �� ������ ������ 
				����� (������������ �� ��������� ������) ��� ������ ���������� � �������� ���������
			3.	�������� ����� IsUpper, ����������� ���������� ����������� �� ������ ������ ���� 
				(������������ �� ��������� ������) ��� ������ ���������� � �������� ���������
			4.	���������� ����� ����������� ������� ��������� Draw (������ ������ � ���������� 
				���� ������ ������ �������� �� ����������� ����� ���� �������� � ��������� �����)
		ii.	����� Circle ����������� �� ������ Shape
			1.	��������� Draw
		iii.	����� Triangle ����������� �� ������ Shape
			1.	��������� Draw
		iv.	����� Square ����������� �� ������ Shape
			1.	��������� Draw
	b.	�������� ������ list<Shape*>, ���������� ����������� �� ��������� ������
	c.	� ������� ����������� ���������� � ��������� ������� (Draw) ��� ������
	d.	� ������� ����������� ���������� � ��������� ��������� ������ �� ��������� ������ 
		�����-������� (������ � ����, ��� � ������ ������ ������ ���� ������ ����������� �����, 
		���������� x ) � ������� ������ (Draw)
	e.	� ������� ����������� ���������� � ��������� ��������� ������ �� ��������� ������ 
		������-������ � ������� ������
	f.	� ������� ����������� ���������� � ��������� ��������� ������ �� ��������� ������ 
		������-���� � ������� ������
	g.	� ������� ����������� ���������� � ��������� ��������� ������ �� ��������� ������ 
		�����-����� � ������� ������
*/

#include <iostream>
#include <algorithm>
#include <conio.h>
#include <list>
#include <functional>

#define VAL 10
#define SIZE 10

using namespace std;

class Shape
{
protected: 
	int x,y;
public:
	Shape() : x(0),y(0) {}
	~Shape() {}
	bool IsMoreLeft(const Shape* sh) const { return sh->x > x; }
	bool IsUpper(const Shape* sh) const { return sh->y < y; }
	bool IsMoreLeft_rev(const Shape* sh) const { return sh->x < x; }
	bool IsUpper_rev(const Shape* sh) const { return sh->y > y; }
	virtual void Draw() const = 0;
};

class Circle : public Shape
{
public:
	Circle() { x=0; y=0; }
	Circle(int X, int Y) { x=X; y=Y; }
	~Circle() {}
	virtual void Draw() const { cout<<"circle: ( "<<x<<" , "<<y<<" )"<<endl; }
};

class Triangle : public Shape
{
public:
	Triangle() { x=0; y=0; }
	Triangle(int X, int Y) { x=X; y=Y; }
	~Triangle() {}
	virtual void Draw() const { cout<<"triang: ( "<<x<<" , "<<y<<" )"<<endl; }
};

class Square : public Shape
{
public:
	Square() { x=0; y=0; }
	Square(int X, int Y) { x=X; y=Y; }
	~Square() {}
	virtual void Draw() const { cout<<"square: ( "<<x<<" , "<<y<<" )"<<endl; }
};

int main()
{
	list<Shape*> lst;

	for (int i=0; i<SIZE; i++)
	{
		int r = rand()%3;
		if (r == 0)
		{
			Shape *sh = new Circle(rand()%VAL,rand()%VAL);
			lst.push_back(sh);
		}
		else if (r == 1)
		{
			Shape *sh = new Triangle(rand()%VAL,rand()%VAL);
			lst.push_back(sh);
		}
		else if (r == 2)
		{
			Shape *sh = new Square(rand()%VAL,rand()%VAL);
			lst.push_back(sh);
		}
	}

	cout<<"list of figures: "<<endl;
	for_each(lst.begin(),lst.end(),mem_fun(&Shape::Draw));

	lst.sort(mem_fun(&Shape::IsMoreLeft));
	cout<<"\nIsMoreLeft: "<<endl;
	for_each(lst.begin(),lst.end(),mem_fun(&Shape::Draw));

	lst.sort(mem_fun(&Shape::IsMoreLeft_rev));
	cout<<"\nIsMoreLeft (reverse): "<<endl;
	for_each(lst.begin(),lst.end(),mem_fun(&Shape::Draw));

	lst.sort(mem_fun(&Shape::IsUpper));
	cout<<"\nIsUpper: "<<endl;
	for_each(lst.begin(),lst.end(),mem_fun(&Shape::Draw));

	lst.sort(mem_fun(&Shape::IsUpper_rev));
	cout<<"\nIsUpper (reverse): "<<endl;
	for_each(lst.begin(),lst.end(),mem_fun(&Shape::Draw));

	getch();
	return 0;
}