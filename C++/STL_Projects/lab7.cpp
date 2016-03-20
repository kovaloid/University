/*
lab7-functors
Ковалев Артем, 23504/4, 2013 год

Задание:
Разработать функтор,  позволяющий собирать статистику о последовательности целых чисел 
(послед может содержать числа от -500 до 500). Функтор после обработки последовательности 
алгоритмом for_each должен предоставлять следующую статистику:
a. Максимальное число в последовательности
b. Минимальное число в последовательности
c. Среднее чисел в последовательности
d. Количество положительных чисел
e. Количество отрицательных чисел
f. Сумму нечетных элементов последовательности
g. Сумму четных элементов последовательности
h. Совпадают ли первый и последний элементы последовательности.

Проверить работу программы на случайно сгенерированных последовательностях.
*/

#include <iostream>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <functional>

#define SIZE 30

using namespace std;

vector<int> x(10);

class FUNC : unary_function<int, int>
{ 
	int max,min,middle,counter,kol_pol,kol_otr,sum_nech,sum_chet,first,last;

public:

	FUNC(): max(-500),min(500),
		    middle(0),counter(0),
			kol_pol(0),kol_otr(0),
			sum_nech(0),sum_chet(0),
			first(0),last(0) {}

    int operator() (int &i)
    {
		if (i > max) max=i;
		if (i < min) min=i;
		middle=+i;
		counter++;
		if (i < 0) kol_otr++;
		else kol_pol++;
		if (i%2 == 0) sum_chet=+i;
		else sum_nech=+i;

		if (counter==1) first=i;
		if (counter==SIZE) last=i;

		x[0]=max;
		x[1]=min;
		x[2]=middle;
		x[3]=counter;
		x[4]=kol_pol;
		x[5]=kol_otr;
		x[6]=sum_nech;
		x[7]=sum_chet;
		x[8]=first;
		x[9]=last;

		return 0;
    }

	void results()
	{
		cout<<"\n\nresults: "<<endl
			<<"max: "<<x[0]<<endl
			<<"min: "<<x[1]<<endl
			<<"middle: "<<(double)x[2]/(double)x[3]<<endl
			<<"kol_pol: "<<x[4]<<endl
			<<"kol_otr: "<<x[5]<<endl
			<<"sum_nech: "<<x[6]<<endl
			<<"sum_chet: "<<x[7]<<endl
			<<"first=last: "<<(x[8]==x[9]?"yes":"no")<<endl;
	}

};	


int main()
{
	vector<int> v;
	FUNC func;

	for (int i=0; i<SIZE; i++)
		v.push_back(rand()%1000-500);

	cout<<"vector: "<<endl;
	copy(v.begin(),v.end(),ostream_iterator<int>(cout, "  "));

	for_each(v.begin(), v.end(), FUNC());
	func.results();

	getch();
	return 0;
}