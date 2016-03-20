#include <conio.h>
#include <iostream.h>

template<class T> class Queue
{   T * a;
    int ind,size;
    void resize(int new_size);
  public:
    typedef T * iterator;
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

void main(void)
{
  Queue<int> a1(10), a2(5);
  Queue<int>::iterator it1;
  clrscr();
  for(int i=0;i<10;i++)
    a1.push_back(i);
  cout<<"Array_1:  ";
  for(i=0;i<a1.tmp_size();i++)
    cout<<a1.at(i);
  a2=a1;
  cout<<endl<<"Array_2:  ";
  for(it1=a2.begin();it1!=a2.end();it1++)
    cout<<a2[*it1];
  cout<<endl<<"Array_1_Size:  "<<a1.tmp_size()<<" of "<<a1.max_size();
  cout<<endl<<"Array_2_Size:  "<<a2.tmp_size()<<" of "<<a2.max_size()<<endl;
  a2.erase(a2.begin()+2);
  a2.erase(a2.begin()+3);
  a2.erase(a2.begin()+4);
  cout<<endl<<"Array_2_Delete_2,4,6:  ";
  for(i=0;i<a2.tmp_size();i++)
    cout<<a2[i];
  cout<<endl<<"Array_2_Size:  "<<a2.tmp_size()<<" of "<<a2.max_size()<<endl<<endl;
  a1.push_back(3); a1.push_back(3);
  a1.pop_front(); a1.pop_front();
  cout<<a1.front()<<"_";
  for(i=0;i<a1.tmp_size();i++)
    cout<<a1[i];
  cout<<endl<<endl;
  a1.swap(a2);
  for(i=0;i<a2.tmp_size();i++)
    cout<<a2[i];
  cout<<endl<<endl;
  for(i=0;i<a1.tmp_size();i++)
    cout<<a1[i];
  getch();
}