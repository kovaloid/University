#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream.h>
#include <string.h>
#include <dos.h>
#include <graphics.h>
#include <fstream.h>

//---FILE-----------------------------------------------------------------------------------------------------

class File
{
    protected:
  FILE *fpnt;
    public:
  File(void){fpnt=NULL;}
  ~File(void){if(fpnt) fclose(fpnt);}
  int Open(char *FileName, char *mode);
  int Close(void);
  void Begin(void){rewind(fpnt);}
  void End(void){fseek(fpnt,0L,SEEK_END);}
  int Eof(void){return feof(fpnt);}
};

int File::Open(char *FileName, char *mode)
{
  int i;
  if(fpnt)
    fclose(fpnt);
  fpnt=fopen(FileName, mode);
  return fpnt!=NULL;
}

int File::Close(void)
{
  int ret=0;
  if(fpnt)
    ret=fclose(fpnt);
  return (ret==0)?1:0;
}

class TxtBD:public File
{
    protected:
  int nF,lenF;
  char *arr;
    public:
  TxtBD(void){arr=NULL;}
  ~TxtBD(void){if(arr) delete[] arr;}
  int OpenBD(char *FileName, char *mode, int nField, int MaxlenField);
  int CloseBD(void);
  int GetNextRecord(void);
  char  AsChar(int n);
  char* AsStr(int n);
  int   AsInt(int n);
  float AsFloat(int n);
};

int TxtBD::OpenBD(char *FileName, char *mode, int nField, int MaxlenField)
{
  File::Open(FileName, mode);
  nF=nField;
  lenF=MaxlenField;
  if(fpnt&&nF>0&&lenF>0)
    arr=new char[nField*(lenF+1)];
  else
    File::Close();
  return fpnt!=NULL;
}

int TxtBD::CloseBD(void)
{
  if(arr)
    delete[] arr;
  File::Close();
  return !fpnt;
}

int TxtBD::GetNextRecord(void)
{
  int i, n=0;
  if(fpnt)
    for(i=0;i<nF;i++)
	{
      n+=fscanf(fpnt,"%s",arr+i*(lenF+1));	
	}
	 	
  return n;
}

char* TxtBD::AsStr(int n)
{
  if(n<0||n>=nF)
  {
    printf("Bad value of index!");
    return "";
  }
  return arr+n*(lenF+1);
}

int TxtBD::AsInt(int n)
{
  if(n<0||n>=nF)
  {
    printf("Bad value of index!");
    return 0;
  }
  return atoi(arr+n*(lenF+1));
}

//------------------------------------------------------------------------------------------------------------

//---SOTRUDNIK_OTPUSK-----------------------------------------------------------------------------------------

class Sotrudnik_Otpusk
{
  char *fio;
  char *otdel;
  char *dolzh;
  char *otp;
 public:
  Sotrudnik_Otpusk(){}
  Sotrudnik_Otpusk(char *fio1,char *otdel,char *dolzh1,char *otp1);
  ~Sotrudnik_Otpusk();
 // void menu();
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

void Sotrudnik_Otpusk::edit()
{
  clrscr();
  cout<<"FIO: "; cin>>fio;
  cout<<"Otdel: "; cin>>otdel;
  cout<<"Dolzhnost': "; cin>>dolzh;
  cout<<"Otpuska: "; cin>>otp;
  cout<<"\nPress and key:";
}

//------------------------------------------------------------------------------------------------------------

//---QUEUE----------------------------------------------------------------------------------------------------

template<class T> class Queue
{   T * a;
    int ind,size;
    void resize(int new_size);
  public:
    typedef T * iterator;
	Queue(){}
    Queue(int Size);
    Queue(const Queue &xQue);
    ~Queue(void){delete[] a;}
    iterator begin(void){return a;}
    iterator end(void){return a+ind;}
    iterator insert(int position,const T &value){a[position]=value; return a+position;}
    void clear(void){ind=0;}
    int empty(void){if(ind==0) return 1; else return 0;}
    int max_size(void){return size;}
    int tmp_size(void){return ind;}
    void push_back(T &value);
    void pop_front(void);
    T & front(void){return a[0];}
    void erase(iterator it)
    {
	 int n=it-begin();
	 for(int i=n;i<ind-1;i++)
		a[i]=a[i+1];
	 ind--;
    }
    T & at(int i){return a[i];}
    void swap(Queue<T> &xQue);
    Queue & operator=(Queue<T> &xQue);
    int operator==(iterator tmp){if(a==tmp) return 1; else return 0;}
    int operator!=(iterator tmp){if(a==tmp) return 0; else return 1;}
    iterator operator=(iterator tmp){return tmp;}
    iterator operator*(void){return a;}
    iterator operator++(int){return a++;}
    T & operator[](int Index);
};

template<class T> Queue<T>::Queue(int Size=10)
{
  size=Size;
  ind=0;
  if(Size==0)
    a=NULL;
  else
    a=new T[size];
}

template<class T> Queue<T>::Queue(const Queue<T> & xQue)
{
  ind=xQue.ind;
  a=new T[size=xQue.size];
  for(int i=0;i<ind;i++)
    a[i]=xQue.a[i];
}

template<class T> void Queue<T>::resize(int new_size)
{
  T * tmp;
  tmp=new T[new_size];
  for(int i=0;i<new_size&&i<ind;i++)
    tmp[i]=a[i];
  delete[] a;
  a=tmp;
  size=new_size;
  if(ind>=new_size)
    ind=new_size;
}

template<class T> void Queue<T>::push_back(T &value)
{
  if(ind>=size)
    resize(size+1);
  a[ind++]=value;
}

template<class T> void Queue<T>::pop_front(void)
{
  for(int i=0;i<ind;i++)
    a[i]=a[i+1];
  ind--;
}

template<class T> void Queue<T>::swap(Queue<T> &xQue)
{
  Queue<T> tmp(10);
  tmp=xQue;
  xQue=*this;
  *this=tmp;
}

template<class T> Queue<T> & Queue<T>::operator=(Queue<T> &xQue)
{
  delete[] a;
  a=new T[size=xQue.size];
  ind=xQue.ind;
  for(int i=0;i<ind;i++)
    a[i]=xQue.a[i];
  return *this;
}

template<class T> T & Queue<T>::operator[](int Index)
{
  if(Index>=ind||Index<0)
  {
    cout<<"Bad value of index! ("<<Index<<") "<<endl;
    getch();
  }
  return a[Index];
}

//------------------------------------------------------------------------------------------------------------

//---MOUSE----------------------------------------------------------------------------------------------------

void InitMouse(void)
{
  REGPACK regs;
  regs.r_ax=0;  
  intr(0x33, &regs);
}

void ShowMouse(void)
{
  REGPACK regs;
  regs.r_ax=1;
  intr(0x33, &regs);
}

void HideMouse(void)
{
  REGPACK regs;
  regs.r_ax=2;
  intr(0x33, &regs);
}

void ReadMouse(int &x, int &y, int &buttons)
{
  REGPACK regs;
  regs.r_ax=3;
  intr(0x33, &regs);
  buttons=regs.r_bx;
  x=regs.r_cx;
  y=regs.r_dx;
}

void Click(int &x, int &y)
{
  int buttons;
  do
    ReadMouse(x,y,buttons);
  while(!(buttons&1));
  do
    ReadMouse(x,y,buttons);
  while(buttons&1);
}

int ClickMouse(int &x, int &y)
{
  int buttons;
  do
  {
    ReadMouse(x,y,buttons);
    if(buttons&2)
      return 0;
  }
  while(!(buttons&1));
  do
    ReadMouse(x,y,buttons);
  while(buttons&1);
  return 1;
}

void Press(void)
{
  int buttons, x, y;
  do
    ReadMouse(x,y,buttons);
  while(!(buttons&3));
}

//------------------------------------------------------------------------------------------------------------

//---MENU-----------------------------------------------------------------------------------------------------

class Menu   
{
  int x,y,Width,High;
  COLORS ColorGr,Color;
  int NumberItems;
  char **Items;
  void *Image;
  int show;
    public:
  Menu(int x, int y, COLORS ColorGr, COLORS Color,
       int NumberItems, char **Items);
  ~Menu(void);
  void Show(void);
  void Hide(void);
  int  Choice(int x, int y);
};

Menu::Menu(int X, int Y, COLORS ClrGr, COLORS Clr,
       int NmbItems, char **items)
{
  int i,len;
  x=X; y=Y; ColorGr=ClrGr; Color=Clr;
  NumberItems=NmbItems;
  Width=0;
  Items= new char*[NmbItems];
  for(i=0;i<NmbItems;i++)
  {
    len=strlen(items[i]);
    if(len>Width) Width=len;
    Items[i]=new char[len+1];
    strcpy(Items[i],items[i]);
  }
  Width=Width+2;
  High =NmbItems+2;
  Image=NULL;
  show =0;
}

Menu::~Menu(void)
{
  Hide();
  for(int i=0;i<NumberItems;i++)
    delete[] Items[i];
  delete[] Items;
}

void Menu::Show(void)
{
  text_info ti;
  int i,j;
  if(!show)
  {
    gettextinfo(&ti);
    Image=new char[Width*High*2];
    if(Image)
      gettext(x,y,x+Width-1,y+High-1,Image);
    textbackground(ColorGr);
    textcolor(Color);
    gotoxy(x,y);
    for(i=0;i<High;i++)
    {
      gotoxy(x,y+i);
    //  bar(x, y, x+Width,y+10);

      for(j=0;j<Width;j++)
	cprintf("%c",' ');

    }
    for(int i=0;i<NumberItems;i++)
    {
      gotoxy(x+1,y+i+1);
      cprintf("%s",Items[i]);
    }
    show=1;
    textattr(ti.attribute);
  }
}

void Menu::Hide(void)
{
  if(show&&Image)
  {
    puttext(x,y,x+Width-1,y+High-1,Image);
    delete[] Image;
    show=0;
  }
}

int Menu::Choice(int X, int Y)
{
  if(X<x||X>x+Width-1) return -1;
  for(int i=0;i<NumberItems;i++)
    if(Y==y+i+1)
      return i;
  return -1;
}

//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------

/*template <class Type> void OpenBd(TxtBD &f, Type &Arr);
template <class Type> void PrintAll(Type &Arr);
template <class Type> void QueryGet(Type &Arr);
template<class Type>  int  BookAdd(Type &Arr);
template<class Type>  int  DeleteBook(Type &Arr);
template<class Type>  int  CorrectBook(Type &Arr);
template<class Type>  void Exit(Type &Arr, int lChange);
*/


void main(void)
{
 Queue<char*> fio_note(15), dolzh_note(10), otp_note(20);
 Queue<int> otdel_note(2);
 TxtBD f;
 clrscr();
 
 //fio_note.push_back(" qwe ");
 //otdel_note.push_back(228);
 //dolzh_note.push_back(" rty ");
 //otp_note.push_back(" uio ");
 
//cout<<fio_note.front()<<endl<<otdel_note.front()<<endl<<dolzh_note.front()<<endl<<otp_note.front()<<endl;
 //getch();
 
 int i=0;

  printf("NAME            OTDEL           DOLZH           OTP\n");
  printf("-------------------------------------------------------\n");
  f.OpenBD("D:\\BC\\lab9\\bd.txt","r",4, 20);
  f.GetNextRecord();
  while(!f.Eof())
  {
   // printf("%-20s%-10d%-20s%-20s\n",f.AsStr(0),f.AsInt(1),f.AsStr(2),f.AsStr(3));
	//cout<<f.AsStr(0)<<"   "<<f.AsInt(1)<<"   "<<f.AsStr(2)<<"   "<<f.AsStr(3)<<'\n';
	fio_note.push_back(f.AsStr(0));
    otdel_note.push_back(f.AsInt(1));
    dolzh_note.push_back(f.AsStr(2));
    otp_note.push_back(f.AsStr(3));
	printf("%-20s%-10d%-20s%-20s\n",fio_note.at(i),otdel_note.at(i),dolzh_note.at(i),otp_note.at(i));
	i++;
    f.GetNextRecord();
  }
  getch();
  
  //for(int n=0;n<15;n++)
  //cout<<fio_note.at(n)<<endl;
  
  getch();
  f.Close();   
  
  
 /* int n,x,y,t=1,lChange=0, pr=0;
  char *Items[]={"OPEN BD",
		 "PRINT DATA OF ALL BOOK",
		 "FIND BOOK",
		 "VVOD NEW NOTE",
		 "CORRECTION NOTE",
		 "DELETE NOTE",
		 "EXIT"};
  TxtBD f;
  Queue<int> ArrVh;
  clrscr();
  Menu mn(30,17,GREEN,BLACK,7,Items);
  mn.Show();
  InitMouse();
  while(t)
  {
    ShowMouse();
    Click(x,y);
    HideMouse();
    x=x/8+1; y=y/8+1;
    n=mn.Choice(x,y);
    switch(n)
    {
      case 0:
	   mn.Hide();
	   if(pr==0)
	   {
	     OpenBd(f,ArrVh);
	     pr=1;
	   }
	   else
	   {
	     gotoxy(35,10);
	     cout<<"BD already open"<<endl;
	     getch();
	     clrscr();
	   }
	   mn.Show();
	   break;
      case 1:
	   mn.Hide();
	   if(pr==1)
	      PrintAll(ArrVh);
	   else
	   {
	     gotoxy(35,10);
	     cout<<"BD not found"<<endl;
	     getch();
	     clrscr();
	   }
	   mn.Show();
	   break;
      case 2:
	   mn.Hide();
     //	QueryGet(ArrVh);
	   mn.Show();
	   break;
      case 3:
	   mn.Hide();
	   if(pr==1)
	   {
	      if(BookAdd(ArrVh))
		lChange=1;
	   }
	   else
	   {
	     gotoxy(35,10);
	     cout<<"BD not found"<<endl;
	     getch();
	     clrscr();
	   }
	   mn.Show();
	   break;
      case 4:
	   mn.Hide();
	   if(pr==1)
	   {
	     if(CorrectBook(ArrVh))
		lChange=1;
	   }
	   else
	   {
	     gotoxy(35,10);
	     cout<<"BD not found"<<endl;
	     getch();
	     clrscr();
	   }
	   mn.Show();
	   break;
      case 5:
	   mn.Hide();
	   if(pr==1)
	   {
	     if(DeleteBook(ArrVh))
	       lChange=1;
	   }
	   else
	   {
	     gotoxy(35,10);
	     cout<<"BD not found"<<endl;
	     getch();
	     clrscr();
	   }
	   mn.Show();
	   break;
      case 6:
       	Exit(ArrVh, lChange);
	t=0;
   }
  }*/
  
}







//------------------------------------------------------------------------------------------------------------

/*

template <class Type> void OpenBd(TxtBD &f, Type &Arr)
{
  Arr.Clear();
  if (f.OpenBD("data.txt","r",5, 20)==NULL)
   {
       gotoxy(35,10);
       cout<<"File not found"<<endl;
       getch();
       return;
   }
  f.GetNextRecord();
  while(!f.Eof())
  {
    Arr.push_front(Book(f.AsStr(0),f.AsStr(1),f.AsStr(2),f.AsStr(3),
		     f.AsStr(4), ""));
    f.GetNextRecord();
  }
  f.Close();
  gotoxy(35,10);
  cout<<"Open BD!"<<endl;
  getch();
  clrscr();
}

template<class Type> void PrintAll(Type &Arr)
{
  int n=0;
 list<Book>::iterator it2;
  clrscr();
  for (it2=Arr.begin(); it2!=Arr.end();it2++)
  {
      cout<<*it2;

    if(++n==8)
    {
      n=0;
      cout<<"     *****For continue press any key!*****";
      getch();
      clrscr();
    }
  }
  getch();
  clrscr();
}


template<class Type> void QueryGet(Type &Arr)
{
  int n=0;
  char  *ArrS[3]={"", "", ""};
  int   ArrI[2]={0,0};
  float Price=0.0;
  int input;
  void *v[]={ArrS[0],ArrS[1],ArrS[2],ArrI,ArrI+1,&Price};
  textbackground(BLACK);
  textcolor(WHITE);
  clrscr();
  ScrFrm sf("QueryGet.scr",v);
  sf.Show();
  if(input=sf.InPut())
  {
    sf.Hide();
    gotoxy(1,1);
    for(int i=0;i<Arr.Size();i++)
    {
      if(!Arr[i].ThatRegVil(sf.GetString(0),sf.GetString(1)))
	continue;
      if(!Arr[i].ThatSize(sf.GetInt(3),sf.GetInt(4)))
	continue;
      if(Arr[i]<sf.GetFloat(5) || !sf.GetFloat(5))
      {
	cout<<"  ["<<i<<"]  "<<Arr[i]<<endl;
        if(++n==8)
        {
          n=0;
          cout<<"     *****For continue press any key!*****";
          getch();
          clrscr();
        }
      }
    }
  }
  if(input)
    getch();
  clrscr();
}

template<class Type> int BookAdd(Type &Arr)
{
  int ret=0;
  char  *ArrS[4]={"", "", "", ""};
  int   ArrI[2]={0,0};
  float Price=0.0;
  list<Book>::iterator it2;
  char* str1,*str2, *str3,*str4,*str5;

   void *v[]={ArrS[0],ArrS[1],ArrS[2],ArrS[3],ArrI,ArrI+1,&Price};
  textbackground(BLACK);
  textcolor(WHITE);
  clrscr();
  cout<<"Enter avtor of book: ";
  cin>>str1;
  cout<<"Enter name of book: ";
  cin>>str2;
  cout<<"Enter tematika: ";
  cin>>str3;
  cout<<"Enter year: ";
  cin>>str4;
  cout<<"Enter number of page: ";
  cin>>str5;

  it2=Arr.end();
  Arr.push_back(Book(str1,str2,str3,str4,str5,""));

  clrscr();
  return ret;
}

template<class Type> int DeleteBook(Type &Arr)
{
  int ind,ret=0;
  list<Book>::iterator it2;

  clrscr();
  gotoxy(20,10);
  cout<<"Enter number of book: ";
  cin>>ind;
  if(cin.good())//&&Arr.ValidInd(ind))
  {
     it2=Arr.begin();
     for(int i=0;i<ind-1;i++)
       it2++;
     Arr.erase(it2);
    ret=1;
  }
  else
  {
    cin.clear();
    cin.ignore(10,'\n');
    gotoxy(20,12);
    cout<<"Bad value of index!";
    getch();
  }
  clrscr();
  return ret;
}

template<class Type> int CorrectBook(Type &Arr)
{
  int s,a,i,ret,ind=0;
  list<Book>::iterator it2;

  clrscr();
  gotoxy(20,10);
  cout<<"Enter index of book: ";
  cin>>ind;
  if(!cin.good())// || !Arr.ValidInd(i))
  {
    cin.clear();
    cin.ignore(10,'\n');
    gotoxy(20,12);
    cout<<"Bad value of index!";
    getch(); clrscr(); return ret;
  }

 it2=Arr.begin();
 for( i=0;i<ind-1;i++)
   it2++;
 // Arr.erase(it2);
 // Arr.insert(it2,

  Book vh1;
// vh1.Correct  (it2,"-");


  return ret;
}

template<class Type>  void Exit(Type &Arr, int lChange)
{
  char sym;
  if(!lChange)
    return;
 
}*/
