#include <conio.h>
#include <iostream.h>

template<class T> print_arr(T* array,T dim1,T dim2)
{
cout<<"Array:\n";
 for (int i=0;i<dim1;i++)
  {
   for (int j=0;j<dim2;j++)
     cout<<" "<<array[i*dim2+j];
   cout<<"\n";
  }
}

template<class T> T func(T* array,T dim1,T &dim2)
{
 for (int i=0;i<=2;i++)
   dim2*=array[3*dim1+i];
 return dim2;
}

void main(void)
{
 int dim1,dim2=1;
 int array[6][3]={2,8,4,
		  8,5,5,
		  2,4,4,
		  8,5,9,
		  3,6,7,
		  3,7,5};
 clrscr();
 print_arr(*array,6,3);
 metka:
 cout<<"Write number of string [0,5]:\n";
 cin>>dim1;
 if (dim1<0||dim1>5)
  {
   cout<<"Error! Number must be [0,5]\n\n";
   goto metka;
  }
 func(*array,dim1,dim2);
 cout<<"Result:\n"<<dim2;
 getch();
}