/*
lab8-functor
Ковалев Артем, 23504/4, 2013 год

Задание:
2.	Разработать программу, которая:
	a.	Реализует иерархию геометрических фигур состоящую из:
		i.	Класс Shape. 
			1.	Содержит информацию о положении центра фигуры (координаты x и y).
			2.	Содердит метод IsMoreLeft, позволяющий определить расположена ли данная фигура 
				левее (определяется по положению центра) чем фигура переданная в качестве аргумента
			3.	Содердит метод IsUpper, позволяющий определить расположена ли данная фигура выше 
				(определяется по положению центра) чем фигура переданная в качестве аргумента
			4.	Определяет чисто виртаульную функцию рисования Draw (каждая фигура в реализации 
				этой функци должна выводить на стандартный вывод свое название и положение цента)
		ii.	Класс Circle производный от класса Shape
			1.	Реализует Draw
		iii.	Класс Triangle производный от класса Shape
			1.	Реализует Draw
		iv.	Класс Square производный от класса Shape
			1.	Реализует Draw
	b.	Содержит список list<Shape*>, заполенный указателями на различные фигуры
	c.	С помощью стандартных алгоритмов и адаптеров выводит (Draw) все фигуры
	d.	С помощью стандартных алгоритмов и адаптеров сортирует список по положению центра 
		слева-направо (имется в виду, что в начале списка должны идти фигуры находящиеся левее, 
		координата x ) и выводит фигуры (Draw)
	e.	С помощью стандартных алгоритмов и адаптеров сортирует список по положению центра 
		справа-налево и выводит фигуры
	f.	С помощью стандартных алгоритмов и адаптеров сортирует список по положению центра 
		сверху-вниз и выводит фигуры
	g.	С помощью стандартных алгоритмов и адаптеров сортирует список по положению центра 
		снизу-вверх и выводит фигуры
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