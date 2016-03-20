/*
lab4-iterators
Ковалев Артем, 23504/4, 2013 год

Задание:
1. Напишите программу – «телефонную книжку». 
Записи (имя и телефон) должны хранится в каком-либо STL-контейнере (vector или list), причем 
крайне желательно, чтобы от типа контейнера не зависело ничего, кроме одной строки в программе – 
объявления этого контейнера (указание: используйте typedef).

Программа должна поддерживать следующие операции:
• Просмотр текущей записи
• Переход к следующей записи
• Переход к предыдущей записи
• Вставка записи перед/после просматриваемой 
• Замена просматриваемой записи 
• Вставка записи в конец базы данных
• Переход вперед/назад через n записей. 

Помните, что после вставки элемента итераторы становятся недействительными, поэтому после вставки 
целесообразно переставлять итератор на начало базы данных.

Постарайтесь реализовать операции вставки и замены с помощью одной и той же функции, которой в 
зависимости от требуемого действия передается либо обычный итератор, либо адаптер – один из 
итераторов вставки: void modifyRecord(iterator pCurrentRecord, CRecord newRecord).
Программа может сразу после запуска сама (без команд пользователя) заполнить  записную книжку 
некоторым количеством записей.
*/

#include <iterator>
#include <list>
#include <string>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cctype> // для функции isdigit

using namespace std;

class pbRecord 
{
	string name, phone;
public:
	pbRecord();
	pbRecord(string &n, string &p)
	{
		setName(n);
		setPhone(p);
	}
	~pbRecord() {}
	pbRecord& operator=(pbRecord &pbR) 
	{
		setName(pbR.getName()); 
		setPhone(pbR.getPhone()); 
		return *this;
	}
	string getName(){return name;}
	void setName(string &n){name=n;}
	string getPhone(){return phone;}
	void setPhone(string &p){phone=p;}
	string printRec(){return "Name: "+getName()+(char) 9+"Phone: "+getPhone();}
};

typedef list<pbRecord> PhoneBook;

string showHelp()
{
	return 
	"--------------------------Command list----------------------------\n"
	"help  - show this screen\n"
	"reset - reset iterator to first record\n"
	"curr  - show current record\n"
	"next  - move to next record\n"
	"prev  - move to previous record\n"
	"nextn <n> - skip several records\n"
	"prevn <n> - skip several records backwards\n"
	"before <name> <phone> - insert a record before the current\n"
	"after <name> <phone>  - insert a record after the current\n"
	"back <name> <phone>   - insert a record at the end of the database\n"
	"change <name> <phone> - change the current record\n"
	"exit - close this window\n"
	"------------------------------------------------------------------\n";
}

void modifyRecord(string v, PhoneBook &pb, PhoneBook::iterator &pbi)
{
	string cmd="", name="", phone="";
	int spaceQ=0, pos1=0, pos2=0;

	for(int i=0; i<v.size(); i++)
		if (v[i]==' ') ++spaceQ;

	if (spaceQ==0)
	{
		if (v=="help") cout << showHelp();
		else if (v=="reset") 
		{
			pbi=pb.begin();
			cout << pbi->printRec() << endl;
		}
		else if (v=="curr") 
		{
			cout << pbi->printRec() << endl;
		}
		else if (v=="next") 
		{
			PhoneBook::iterator xend=pb.end();
			--xend;
			if (pbi==xend) cout<<"no next\nlast note:"<<endl;
			else ++pbi;
			cout << pbi->printRec() << endl;
		}
		else if (v=="prev") 
		{
			if (pbi==pb.begin()) cout<<"no previous\nfirst note:"<<endl;
			else --pbi;
			cout << pbi->printRec() << endl;
		}
	}
	else if (spaceQ==1)
	{
		pos2=v.find(' ', pos1+1);
		for(int i=0; i<pos2; i++)
			cmd.push_back(v[i]);

		if(cmd=="nextn")
		{
			if(isdigit(v[6])) // isdigit() возвращает ненулевое значение, если ее аргумент является цифрой
			{
				cmd.assign(v, 6, v.size()-6);
				char Mass[10];
				strcpy(Mass, cmd.c_str());

				int index=0;
				while (pbi!=pb.end() && index<atoi(Mass)) // atoi() превращает символы в числа
				{
					pbi++;
					index++;
				}

				if (index<atoi(Mass) || pbi==pb.end()) 
				{
					cout<<"out of the range\nlast note:"<<endl;
					pbi=pb.end();
					pbi--;
				}

				cout << pbi->printRec() << endl;
			}
			else cout << "There is no digit after \"nextn\"\n";
		}
		else if(cmd=="prevn")
		{
			if(isdigit(v[6]))
			{
				cmd.assign(v, 6, v.size()-6);
				char Mass[10];
				strcpy(Mass, cmd.c_str());

				int index=0;
				while (pbi!=pb.begin() && index<atoi(Mass))
				{
					pbi--;
					index++;
				}

				if (index<atoi(Mass))
				{
					cout<<"out of the range\nlast note:"<<endl;
					pbi=pb.begin();
				}

				cout << pbi->printRec() << endl;
			}
			else cout << "There is no digit after \"prevn\"\n";
		}
	}
	else if (spaceQ==2)
	{
		pos2=v.find(' ', pos1);
		cmd.assign(v,0,pos2);
		pos1=pos2+1;
		
		pos2=v.find(' ', pos1);
		name.assign(v,pos1,pos2-pos1);
		pos1=pos2+1;
		phone.assign(v,pos1,v.size()-pos1);
		cout << "Name: " << name << (char) 9 << "Phone: "<< phone << endl;
		
		if (cmd=="after") 
			pb.insert(++pbi, pbRecord(name, phone));
		else if (cmd=="before") 
			pb.insert(pbi, pbRecord(name, phone));
		else if (cmd=="back") 
			pb.insert(pb.end(), pbRecord(name,phone));
		else if (cmd=="change") 
		{
			pbi->setName(name);
			pbi->setPhone(phone);
		}

		pbi=pb.begin();
	}
}

void main(void)
{
	PhoneBook pb;
	PhoneBook::iterator pbi;

	string input="", name="", phone="";
	int pos=0;
	ifstream f("database.txt");

	while(!f.eof())
	{
		getline(f, input);
		pos=input.find(' ', 0);
		name.assign(input, 0, pos);
		phone.assign(input, pos+1, input.size()-pos-1);
		pb.insert(pb.end(), pbRecord(name, phone));
		input="";
	}

	for(pbi=pb.begin(); pbi!=pb.end(); pbi++)
		cout<<pbi->printRec()<<endl;

	pbi=pb.begin();
	cout<<endl<<showHelp();

	while (input!="exit")
	{
		getline(cin, input);
		modifyRecord(input, pb, pbi);
	}
}
