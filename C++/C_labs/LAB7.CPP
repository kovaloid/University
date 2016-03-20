#include <conio.h>
#include <stdlib.h>
#include <iostream.h>
#include <string.h>

class Sotrudnik_Otpusk
{
  char *fio;
  char *otdel;
  char *dolzh;
  char *otp;
 public:
  Sotrudnik_Otpusk();
  Sotrudnik_Otpusk(char *fio1,char *otdel,char *dolzh1,char *otp1);
  ~Sotrudnik_Otpusk();
  void menu();
  void edit();
  Sotrudnik_Otpusk operator=(Sotrudnik_Otpusk &tmp);
  int operator==(Sotrudnik_Otpusk &tmp);
  int operator!=(Sotrudnik_Otpusk &tmp);
  friend ostream & operator<<(ostream &s, Sotrudnik_Otpusk &tmp);
};

Sotrudnik_Otpusk Sotrudnik_Otpusk::operator=(Sotrudnik_Otpusk &tmp)
{
  delete[] fio;
  delete[] otdel;
  delete[] dolzh;
  delete[] otp;
  fio=new char[16];
  otdel=new char[10];
  dolzh=new char[13];
  otp=new char[100];
  strcpy(fio,tmp.fio);
  strcpy(otdel,tmp.otdel);
  strcpy(dolzh,tmp.dolzh);
  strcpy(otp,tmp.otp);
  return *this;
}

int Sotrudnik_Otpusk::operator==(Sotrudnik_Otpusk &tmp)
{
  return !(strcmp(fio,tmp.fio)||strcmp(otdel,tmp.otdel)||strcmp(dolzh,tmp.dolzh)||strcmp(otp,tmp.otp));
}

int Sotrudnik_Otpusk::operator!=(Sotrudnik_Otpusk &tmp)
{
  return strcmp(fio,tmp.fio)||strcmp(otdel,tmp.otdel)||strcmp(dolzh,tmp.dolzh)||strcmp(otp,tmp.otp);
}

ostream & operator<<(ostream &s, Sotrudnik_Otpusk &tmp)
{
  s<<"FIO: "<<tmp.fio<<endl
   <<"Otdel: "<<tmp.otdel<<endl
   <<"Dolzhnost': "<<tmp.dolzh<<endl
   <<"Otpuska: "<<tmp.otp<<endl<<endl;
  return s;
}

Sotrudnik_Otpusk::Sotrudnik_Otpusk()
{}

Sotrudnik_Otpusk::Sotrudnik_Otpusk(char *fio1,char *otdel1,char *dolzh1,char *otp1)
{
  fio=new char[16];
  otdel=new char[10];
  dolzh=new char[13];
  otp=new char[100];
  strcpy(fio,fio1);
  strcpy(otdel,otdel1);
  strcpy(dolzh,dolzh1);
  strcpy(otp,otp1);
}

Sotrudnik_Otpusk::~Sotrudnik_Otpusk()
{
  delete[] fio;
  delete[] otdel;
  delete[] dolzh;
  delete[] otp;
}

void Sotrudnik_Otpusk::menu()
{
  clrscr();
  cout<<"Menu:"<<endl
      <<"  1) Show data"<<endl
      <<"  2) Edit data"<<endl
      <<"  3) Exit"<<endl<<endl
      <<"Enter number (1-3) and press key:"<<endl;
}

void Sotrudnik_Otpusk::edit()
{
  clrscr();
  cout<<"FIO: "; cin>>fio;
  cout<<"Otdel: "; cin>>otdel;
  cout<<"Dolzhnost': "; cin>>dolzh;
  cout<<"Otpuska: "; cin>>otp;
  cout<<"\nPress and key:";
}

void main()
{
Sotrudnik_Otpusk SO;
Sotrudnik_Otpusk w1("Nikolaev V.P.","3","manager","01.01.01-02.02.02; 03.03.03-07.07.07");
Sotrudnik_Otpusk w2("Petrov N.S.","4","tester","08.08.08-09.09.09");
Sotrudnik_Otpusk w3("Sidorov N.V.","5","helper","04.04.04-05.05.05; 06.06.06-07.07.07");
Sotrudnik_Otpusk w4("Kovalev A.D.","1","programmer","13.13.13-14.14.14; 15.15.15-16.16.16");
Sotrudnik_Otpusk w5("Lebedev N.S.","2","injener","27.27.27-28.28.28");

  int key;
  Start :
  SO.menu();
  cin>>key;
  switch(key)
  {
    case 1 :
	 cout<<"Enter number of person (1-5):\n";
	 cin>>key;
	 clrscr();
	 switch(key)
	 {
		case 1 : cout<<w1; break;
		case 2 : cout<<w2; break;
		case 3 : cout<<w3; break;
		case 4 : cout<<w4; break;
		case 5 : cout<<w5; break;
		default : break;
	 }
	 cout<<"Press and key:";
	 break;
    case 2 :
	 cout<<"Enter number of person (1-5):\n";
	 cin>>key;
	 switch(key)
	 {
		case 1 : w1.edit(); break;
		case 2 : w2.edit(); break;
		case 3 : w3.edit(); break;
		case 4 : w4.edit(); break;
		case 5 : w5.edit(); break;
		default : break;
	 }
	 break;
    case 3 :
	 w1.~Sotrudnik_Otpusk();
	 w2.~Sotrudnik_Otpusk();
	 w3.~Sotrudnik_Otpusk();
	 w4.~Sotrudnik_Otpusk();
	 w5.~Sotrudnik_Otpusk();
	 exit(0);
    default : break;
  }
  getch();
  goto Start;
}

