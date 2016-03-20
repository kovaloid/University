/*
lab1-vector
Ковалев Артем, 23504/4, 2013 год

Задание:
1)	Напишите алгоритм сортировки (любой простейший) содержимого вектора целых чисел, используя 
	оператор operator[].
2)	Напишите алгоритм сортировки (любой простейший) содержимого вектора целых чисел, используя 
	метод at().
3)	Напишите алгоритм сортировки (любой простейший) содержимого вектора целых чисел, используя 
	для доступа к содержимому вектора только итераторы. Для работы с итераторами допустимо использовать 
	только операторы получения текущего элемента и перехода в следующему (подсказка, можно сохранять 
	копию итератора указывающего на некоторый элемент). 
4)	Прочитайте во встроенный массив С содержимое текстового файлы, скопируйте данные в вектор одной 
	строкой кода (без циклов и алгоритмов STL)
5)	Напишите программу, сохраняющую в векторе числа, полученные из стандартного ввода (окончанием 
	ввода является число 0). Удалите все элементы, которые делятся на 2 (не используете стандартные 
	алгоритмы STL), если последнее число 1. Если последнее число 2, добавьте после каждого числа которое 
	делится на 3 три единицы.
6)	Напишите функцию void fillRandom(double* array, int size) заполняющую массив случайными значениями 
	в интервале от -1.0 до 1.0. Заполните с помощью заданной функции вектора размером 5,10,25,50,100 и 
	отсортируйте его содержимое (с помощью любого разработанного ранее алгоритма модифицированного для 
	сортировки действительных чисел) 
*/

#include <conio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>

#define SIZE 1000

using namespace std;

void fillRandom(double* arr, int size);

void main()
{
	int i, j, x, tmp;
	vector<int> VectorOfInt;

	cout<<"enter "<<SIZE<<" numbers"<<endl<<endl;
	for (i=0; i<SIZE; i++)
	{
		x=rand()%1000;
		VectorOfInt.push_back(x);
		cout<<x<<"  ";
	}
	cout<<"\nend of input, press <enter>"<<endl<<endl;
	getch();
	cout<<"with operator[]"<<endl<<endl;

//------------part_1------------

	int time1=clock();
	for (i=SIZE-1; i>0; i--)
		for (j=0; j<i; j++)
			if (VectorOfInt[j] > VectorOfInt[j + 1])
			{
				tmp=VectorOfInt[j];
				VectorOfInt[j]=VectorOfInt[j+1];
				VectorOfInt[j+1]=tmp;
			}
	int time2=clock(), itog=time2-time1;

	for (i=0; i<SIZE; i++)
		cout<<VectorOfInt[i]<<"  ";
	cout<<"\ntime of sort (microseconds): "<<itog<<endl<<endl;
	getch();

//------------part_2------------

try
{
	cout<<"with at()"<<endl<<endl;
	time1=clock();
	for (i=SIZE-1; i>0; i--)
		for (j=0; j<i; j++)
			if (VectorOfInt.at(j)>VectorOfInt.at(j+1))
			{
				tmp=VectorOfInt.at(j);
				VectorOfInt.at(j)=VectorOfInt.at(j+1);
				VectorOfInt.at(j+1)=tmp;
			}
	time2=clock();
	itog=time2-time1;

	for (i=0; i<SIZE+100; i++)
		cout<<VectorOfInt.at(i)<<"  ";
	cout<<"\ntime of sort (microseconds): "<<itog<<endl<<endl;
}
catch(out_of_range)
{
	cout<<"\nout of range"<<endl<<endl;
	getch();
}

//------------part_3------------

	vector<int>::iterator it;
	vector<int>::iterator it2;
	it=VectorOfInt.begin();
	it2=VectorOfInt.begin();
	cout<<"\nwith iterators"<<endl<<endl;

	time1=clock();
	for (it=VectorOfInt.end()-1; it!=VectorOfInt.begin(); it--)
		for (it2=VectorOfInt.begin(); it2<it; it2++)
			if (*it2>*(it2+1))
			{
				tmp=*it2;
				*it2=*(it2+1);
				*(it2+1)=tmp;
			}
	time2=clock();
	itog=time2-time1;

	it=VectorOfInt.begin();
	while(it!=VectorOfInt.end())
	{
		cout<<*it<<"  ";
		it++;
	}
	cout<<"\ntime of sort (microseconds): "<<itog<<endl<<endl;
	getch();

//------------part_Qsort------------

	cout<<"\nwith quick sort"<<endl<<endl;
	time1=clock();
	sort(VectorOfInt.begin(),VectorOfInt.end());
	time2=clock();
	itog=time2-time1;
	for (i=0; i<SIZE; i++)
		cout<<VectorOfInt[i]<<"  ";
	cout<<"\ntime of sort (microseconds): "<<itog<<endl<<endl;
	getch();

//------------part_4------------

	ifstream inpf("input.txt", ios::in);

	inpf.seekg (0, std::ios::end);
	int size_of_file=inpf.tellg();
	inpf.seekg (0, std::ios::beg);

	if (!inpf) cout<<"\ncan't open file to read"<<endl<<endl;
	else cout<<"\ncontents of file <input.txt> with size: "<<size_of_file<<endl<<endl;

	char *buf=new char[size_of_file+1L];
	buf[size_of_file]='\0';
	inpf.read(buf, size_of_file);
    cout<<buf<<endl;

	cout<<"\nvector of char"<<endl<<endl;

	vector<char> VectorOfChar(size_of_file);
	VectorOfChar.assign(&buf[0], &buf[size_of_file-1]);
    for (i=0; i<VectorOfChar.size(); i++)
		cout<<VectorOfChar[i];

	inpf.close();
	getch();

//------------part_5------------

	vector<int> vec;
	tmp=1;

	cout<<"\n\nenter numbers, to end press '0'"<<endl<<endl;
	while(tmp!=0)
	{
		cin>>tmp;
		if (tmp!=0) vec.push_back(tmp);
	}

	cout<<"\nsource array"<<endl<<endl;
	for (i=0; i<vec.size(); i++)
		cout<<vec[i]<<"  ";

	vector<int>::iterator iter=vec.begin();
	int const q=1;
	if (vec.back()==1)
		while (iter!=vec.end())
		{
			if (*iter%2==0) iter=vec.erase(iter);
			iter++;
		}
	else if (vec.back()==2)
		while (iter!=vec.end())
		{
			if (*iter%3==0) iter=vec.insert(iter+1,q)+1;
			iter++;
		}

	cout<<"\n\ncorrected array"<<endl<<endl;
	for (i=0; i<vec.size(); i++)
		cout<<vec[i]<<"  ";
	getch();

//------------part_5------------

	vector<double> vec1(5); double tmp_arr1[5];
	vector<double> vec2(10); double tmp_arr2[10];
	vector<double> vec3(25); double tmp_arr3[25];
	vector<double> vec4(50); double tmp_arr4[50];
	vector<double> vec5(100); double tmp_arr5[100];

	cout<<"\n\nvector with size of 5"<<endl<<endl;
	fillRandom(tmp_arr1,5);
	vec1.assign(&tmp_arr1[0],&tmp_arr1[sizeof(tmp_arr1)/sizeof(tmp_arr1[0])]);
	sort(vec1.begin(),vec1.end());
	for (i=0; i<vec1.size(); i++)
		cout<<vec1[i]<<"  ";

	cout<<"\n\nvector with size of 10"<<endl<<endl;
	fillRandom(tmp_arr2,10);
	vec2.assign(&tmp_arr2[0],&tmp_arr2[sizeof(tmp_arr2)/sizeof(tmp_arr2[0])]);
	sort(vec2.begin(),vec2.end());
	for (i=0; i<vec2.size(); i++)
		cout<<vec2[i]<<"  ";

	cout<<"\n\nvector with size of 25"<<endl<<endl;
	fillRandom(tmp_arr3,25);
	vec3.assign(&tmp_arr3[0],&tmp_arr3[sizeof(tmp_arr3)/sizeof(tmp_arr3[0])]);
	sort(vec3.begin(),vec3.end());
	for (i=0; i<vec3.size(); i++)
		cout<<vec3[i]<<"  ";

	cout<<"\n\nvector with size of 50"<<endl<<endl;
	fillRandom(tmp_arr4,50);
	vec4.assign(&tmp_arr4[0],&tmp_arr4[sizeof(tmp_arr4)/sizeof(tmp_arr4[0])]);
	sort(vec4.begin(),vec4.end());
	for (i=0; i<vec4.size(); i++)
		cout<<vec4[i]<<"  ";

	cout<<"\n\nvector with size of 100"<<endl<<endl;
	fillRandom(tmp_arr5,100);
	vec5.assign(&tmp_arr5[0],&tmp_arr5[sizeof(tmp_arr5)/sizeof(tmp_arr5[0])]);
	sort(vec5.begin(),vec5.end());
	for (i=0; i<vec5.size(); i++)
		cout<<vec5[i]<<"  ";

	getch();
}

void fillRandom(double* arr, int size)
{
	for(int i=0; i<size; i++)
	{
		arr[i]=(double)rand()/(RAND_MAX+1)*2 - 1;
		//temp = (double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min; 
	}
}