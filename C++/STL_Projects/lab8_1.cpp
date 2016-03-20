/*
lab8-functor
Ковалев Артем, 23504/4, 2013 год

Задание:
1.	Разработать программу, которая, используя только стандартные алгоритмы и функторы, умножает 
	каждый элемент списка чисел с плавающей  точкой на число PI
*/

#include <iostream>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <functional>

#define SIZE 10
const double PI = 3.14159265;

using namespace std;

class FUNC : unary_function<double, double>
{ 
public:
    double operator() (double &i)
    {
		i=i*PI;
		return i;
    }
};	

int main()
{
	vector<double> v;
	FUNC func;

	for (int i=0; i<SIZE; i++)
		v.push_back((double)rand()/(RAND_MAX+1)*(10-(-10))+(-10));

	cout<<"vector: "<<endl;
	copy(v.begin(),v.end(),ostream_iterator<double>(cout, "\n"));

	for_each(v.begin(), v.end(), FUNC());

	cout<<"\nvector * PI: "<<endl;
	copy(v.begin(),v.end(),ostream_iterator<double>(cout, "\n"));

	getch();
	return 0;
}