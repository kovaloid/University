/*
lab3-list-deque
Ковалев Артем, 23504/4, 2013 год

Задание:
Необходимо выполнить ВСЕ задания.
1. Ниже приведен интерфейс класса очереди с приоритетами, который функционирует следующим образом.
В очередь могут быть добавлены элементы, каждому элементу при добавлении присваивается один из трех 
уровней приоритета (low, normal, high)
Элементы из очереди извлекаются в соответствии с их приоритетами (сначала извлекаются элементы с 
приоритетом high, потом normal, потом low), элементы с одинаковыми приоритетами извлекаются из 
очереди в порядки их поступления. 
В очереди также может происходить операция акселерации – все элементы с приоритетом low находящиеся 
в момент акселерации в очереди увеличивают свой приоритет до high и «обгоняют» элементы с 
приоритетом normal.

Ниже приведен интерфейс этого класса:
typedef enum 
{
    LOW, 
    NORMAL,
    HIGH 
} ElementPriority;

typedef struct
{
    string name;
} QueueElement;

class QueueWithPriority
{
    // Конструктор, создает пустую очередь
   QueueWithPriority();

    // Деструктор
   ~QueueWithPriority();

    // Добавить в очередь элемент element с приоритетом priority
    void PutElementToQueue(const QueueElement& element, ElementPriority priority);

    // Получить элемент из очереди
    // метод должен возвращать элемент с наибольшим приоритетом, который был
    // добавлен в очередь раньше других
    QueueElement GetElementFromQueue();

    // Выполнить акселерацию
    void Accelerate();
};

Реализовать этот класс, используя list или deque. Объяснить свой выбор.
Протестируете программу, добавьте отладочный вывод, показывающий, что  класс работает правильно.

2. Разработайте программу, которая
a. Заполняет list<int> 15 случайными значениями от 1 до 20, список может содержать от 0 до 20 
значений (обязательно проверить на длине списка 0, 1. 2, 3, 4, 5, 7, 14)
b. Выводит содержимое списка в следующем порядке: первый элемент, последний элемент, второй 
элемент, предпоследний элемент, тритий элемент и т.д.

Например если список содержит:
1 2 3 4 5 6 7 8
то вывод будет иметь вид 
1 8 2 7 3 6 4 5

Подсказка: можно использовать рекурсию и двунаправленные итераторы
*/

#include <conio.h>
#include <string>
#include <deque>
#include <list>
#include <iostream>
#include <fstream>

using namespace std;

typedef enum 
{
    LOW, 
    NORMAL,
    HIGH 
} ElementPriority;

typedef struct
{
    string name;
} QueueElement;

class QueueWithPriority
{
	deque<QueueElement> low_deq;
	deque<QueueElement> normal_deq;
	deque<QueueElement> high_deq;
public:
// Конструктор, создает пустую очередь
	QueueWithPriority(){}
// Деструктор
	~QueueWithPriority(){low_deq.clear(); normal_deq.clear(); high_deq.clear();}
// Добавить в очередь элемент element с приоритетом priority
	void PutElementToQueue(const QueueElement& element, ElementPriority priority);
// Получить элемент из очереди
// Метод должен возвращать элемент с наибольшим приоритетом, который был
// добавлен в очередь раньше других
	QueueElement GetElementFromQueue();
// Выполнить акселерацию
    void Accelerate();
	void Output();
};

void QueueWithPriority::PutElementToQueue(const QueueElement& element, ElementPriority priority)
{
	if (priority==LOW) low_deq.push_back(element);
	else if (priority==NORMAL) normal_deq.push_back(element);
	else if (priority==HIGH) high_deq.push_back(element);
}

QueueElement QueueWithPriority::GetElementFromQueue()
{
	QueueElement elem;

	if (high_deq.size()!=0) 
	{
		elem=high_deq.front();
		high_deq.pop_front();
	}
	else if (normal_deq.size()!=0)
	{	
		elem=normal_deq.front();
		normal_deq.pop_front();
	}
	else if (low_deq.size()!=0) 
	{
		elem=low_deq.front();
		low_deq.pop_front();
	}

	return elem;
}

void QueueWithPriority::Accelerate()
{
	for (int i=0; i<low_deq.size(); i++)
		high_deq.push_back(low_deq[i]);
	low_deq.clear();
}

void QueueWithPriority::Output()
{
	int i;

	cout<<"\n//OUTPUT://\nHIGH: "<<endl;
	if (high_deq.size()!=0)
		for (i=0; i!=high_deq.size();i++)
			cout<<high_deq[i].name<<endl;
	else cout<<"zero"<<endl;

	cout<<"\nNORMAL: "<<endl;
	if (normal_deq.size()!=0)
		for (i=0; i!=normal_deq.size();i++)
			cout<<normal_deq[i].name<<endl;
	else cout<<"zero"<<endl;

	cout<<"\nLOW: "<<endl;
	if (low_deq.size()!=0)
		for (i=0; i!=low_deq.size()-1;i++)
			cout<<low_deq[i].name<<endl;
	else cout<<"zero"<<endl;
}

//---------------------------------------

int recurs(list<int>::iterator iter1, list<int>::iterator iter2)
{
	if (iter1==iter2) 
	{
		if (iter1==iter2--) cout<<*iter1;
		return 0;
	}
	cout<<*iter1<<"  "<<*iter2<<"  ";
	recurs(++iter1,--iter2);
}

int main()
{	
	QueueWithPriority xQue;
	ElementPriority xPrior;
	QueueElement xElem;

	ifstream f("input3.txt", ios::in);
	if (!f) {cout<<"can't open file"; getch(); return 0;}

	char buf[20];
	cout<<"content of file: "<<endl<<endl;
	while (!f.eof())
	{
		f.getline(buf,20);
		xElem.name=buf;
		int tmp=rand()%30;
		if (tmp>0&&tmp<=10) xPrior=LOW;
		else if (tmp>10&&tmp<=20) xPrior=NORMAL;
		else if (tmp>20&&tmp<30) xPrior=HIGH;
		xQue.PutElementToQueue(xElem,xPrior);
		cout<<buf<<endl;
	}
	xQue.Output();

	cout<<"\n\ndelete 4 elements of deque"<<endl;
	for (int i=0; i<4; i++)
		xElem=xQue.GetElementFromQueue();
	xQue.Output();

	cout<<"\n\naccelerate"<<endl;
	xQue.Accelerate();
	xQue.Output();

	getch();
	xQue.~QueueWithPriority();
	cout<<"\n--------------------------------------------"<<endl<<endl;

	list<int> ListOfInt;

	cout<<"source list: "<<endl;
	for (int i=0; i<15; i++)
	{
		ListOfInt.push_back(rand()%20);
		cout<<ListOfInt.back()<<"  ";
	}
	cout<<endl<<endl;

	list<int>::iterator it1 = ListOfInt.begin();
	list<int>::iterator it2 = --ListOfInt.end();

	cout<<"sorted list: "<<endl;
	recurs(it1, it2);

	getch();
	return 0;
}