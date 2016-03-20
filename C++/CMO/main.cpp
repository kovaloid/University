#include <iostream>
#include <conio.h>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <locale>
#include <cmath>

using namespace std;

const int n=8;  // количество источников
const int m=6;  // количество приборов
const int buf_size = 10; // размер буфера
const float lambda = 4.0; // интенсивность приборов
const float tay1 = 0.1;   // интенсивность источников
const float tay2 = 0.5;

float curtime=0; // текущее время 
bool poshag = true; // режим
int p_dev=0; // указатель прибора


class zayvka
{
public:
	int ist_num,zaya_num;
	float cr8_time;
	zayvka(void)
	{
		ist_num=-1;
		zaya_num=-1;
		cr8_time=-1;
	};
};


class isto4
{
private:
	int za_num,is_num;
	float Ntime;
	float r;

public:
	isto4(int i)
	{
		r=(float)rand()/RAND_MAX;
		Ntime=(float)(tay1+(tay2-tay1)*r); // равномерный закон
		is_num=i;
		za_num=0;
	};
	
	float ShowTime(void){
		return Ntime;
	};
	int ShowNum(void){
		return za_num;
	};

	int GetNum(void)
	{
		return is_num;
	};

	zayvka GenerateZayv(float curtime)
	{
		zayvka res;
		r=(float)rand()/RAND_MAX;
		Ntime=(float)(tay1+(tay2-tay1)*r); // равномерный закон
		res.cr8_time =(float)curtime;
		res.zaya_num = za_num;
		res.ist_num=is_num;
		za_num++;
		return res;
	};

};


class pribor
{
private:
	int pr_num;
	float r;
	bool free;
	float Ntime;
public:
	zayvka cur_z;
	float timeinWork;
	pribor(int i)
	{
		timeinWork=0;
		Ntime=0;
		pr_num=i;
		free=true;
	};

	bool Free(void)
	{
		return free;
	};

	void SetFree(void)
	{
		free=true;
		cur_z.ist_num = -1;
		cur_z.zaya_num = -1;
	};

	float ShowTime(void){
		return Ntime;
	};
	float InputZayav(zayvka in_z,vector<float> &vec_timeObs )
	{
		float res;
		cur_z=in_z;
		free=false;
		r=(float)rand()/RAND_MAX;
		res=(float)-log(1-r)/lambda; // экспоненциальный закон
		Ntime=res;
		vec_timeObs[in_z.ist_num]+=res;
		timeinWork+=res;
		return res;
	};

};


class buffer
{
private:
	int size;
public:
	int p_read,p_write;
	vector<zayvka> buf_vec;
	buffer(int SetSize)
	{
		size=SetSize;
		p_read=0;
		p_write=0;
		buf_vec.resize(size);	
		for(int i=0; i<size; i++)
			buf_vec[i].ist_num=-1;
	}
	
	bool Empty(void)
	{
		for(int i=0; i<size; i++)
			if(buf_vec[i].ist_num!=-1) return false;
		return true;
	}
	
	void buf_write(zayvka new_z, vector<int> &vec_otk, vector<float> &vec_timeinsmo)
	{
		int i;
		for( i=p_write; i<size; i++)
		{
			if(buf_vec[i].zaya_num==-1)
			{
				buf_vec[i]=new_z;
				if(i!=(size-1)) p_write=i+1;
				else p_write=0;
				return;
			}
		}

		for( i=0; i<p_write; i++)
		{
			if(buf_vec[i].zaya_num==-1)
			{
				buf_vec[i]=new_z;
				if(i!=(size-1)) p_write=i+1;
				else p_write=0;
				return;
			}
		}

		int min=0;
		for( i=1; i<buf_size; i++)
		{
			if(buf_vec[i].cr8_time < buf_vec[min].cr8_time)
				min = i;
		}
		
		vec_otk[buf_vec[min].ist_num]+=1;
		vec_timeinsmo[buf_vec[min].ist_num]+=(curtime-buf_vec[min].cr8_time);

		if(poshag){
			cout<<"=========================================================\n";
			cout<<" ОТКАЗ:\n";
			cout<<" Позиция буфера:      "<<min<<endl;
			cout<<" Ушедшая заявка:      "<<buf_vec[min].ist_num<<"."<<buf_vec[min].zaya_num<<endl;
		}
		buf_vec[min]=new_z;
		p_write=min;
		if(poshag) cout<<" Появившаяся заявка:  "<<buf_vec[p_write].ist_num<<"."<<buf_vec[p_write].zaya_num<<endl;		
		if(p_write!=(size-1)) p_write++;
				else p_write=0;		
		return;
	};
	int ShowUk()
	{
		return p_write;
	}
	
	zayvka buf_read(vector<float> &vec_timeinbuf)
	{
		zayvka res;
		bool iwork = false;

		for(int i=0; i<size; i++)
		{
			if(buf_vec[i].ist_num!=-1) iwork = true;
		}
		if (iwork){
			p_read=0;
			float last_time = buf_vec[p_read].cr8_time;
			for(int i=0; i<size; i++)
			{
				if(buf_vec[i].cr8_time > last_time)
				{
					last_time = buf_vec[i].cr8_time;
					p_read = i;
				}
			}
			res=buf_vec[p_read];
			vec_timeinbuf[buf_vec[p_read].ist_num]+=curtime - buf_vec[p_read].cr8_time;
			buf_vec[p_read].ist_num=-1;
			buf_vec[p_read].zaya_num=-1;
			buf_vec[p_read].cr8_time=-1;
			return res;
		}

	};
};


void main()
{
	setlocale( LC_ALL,"Russian" );

	int av;
	printf(" Пошаговый режим      - 0\n");
	printf(" Автоматический режим - 1\n ");
	scanf(" %d",&av);
	getchar();
	if (av==0) poshag=true;
	else poshag=false;

	srand( (unsigned)time( NULL ) );
	vector<isto4> ist_vec;
	vector<pribor> pri_vec;
	vector<float> ist_time;
	vector<float> pri_time;
	vector<int> ist_otk;
	int Ncycl;
	Ncycl = 100;
	
	int i;

	vector<float> ist_zayaVsmo;
	vector<float> ist_zayaObs;
	vector<float> ist_zayaW8;

	vector<int> ist_vsego;
	float nexttime=0,min=0;
	zayvka z_buf;
	buffer buf(buf_size);
	bool t;
	int SumZayv;

	ist_vec.empty();
	pri_vec.empty();
	ist_time.empty();
	pri_time.empty();
	for( i=0; i<n; i++)
	{
		ist_otk.push_back(0);
		ist_zayaVsmo.push_back(0);
		ist_zayaObs.push_back(0);
		ist_zayaW8.push_back(0);
		isto4 ist_buf(i);
		ist_vec.push_back(ist_buf);
		ist_time.push_back(ist_vec[i].ShowTime());
	
	}	
	for( i=0; i<m; i++)
	{
		pribor pri_buf(i);
		pri_vec.push_back(pri_buf);
		pri_time.push_back(pri_vec[i].ShowTime());
	}
	SumZayv=0;
	while(SumZayv<=Ncycl)
	{
		//poisk min
		min=ist_time[0];
		for( i=1; i<n; i++)
			if(ist_time[i] < min ) min=ist_time[i];
		for( i=0; i<m; i++)
			if((pri_time[i] < min)&& (! pri_vec[i].Free())  ) min=pri_time[i];

		curtime=min;
//Pribors 
//-------------------------------------------------------------
		for( i=0; i<m; i++)
		{
			if(curtime == pri_time[i])
			{
				pri_vec[i].SetFree(); // освобождаем прибор
				if(!buf.Empty())
				{	
					pri_time[i]=curtime+(float)pri_vec[i].InputZayav(buf.buf_read(ist_zayaW8),ist_zayaObs);
					if(i!=m-1) p_dev=i+1;
					else p_dev=0;				
				}			
			}		
	    }

//Isto4nik
//-------------------------------------------------------------
		for( i=0; i<n; i++)
		{			
			if(curtime == ist_time[i])
			{
				int j;
				t=true; // = незаписана
				z_buf=ist_vec[i].GenerateZayv(curtime);
				ist_time[i]+=ist_vec[i].ShowTime();
			// заполнение прибора по кольцу
				for( j=p_dev; j<m; j++)
				{
					if(pri_vec[j].Free())
					{	
						pri_time[j]=curtime+pri_vec[j].InputZayav(z_buf,ist_zayaObs);
						if(j!=m-1) p_dev=j+1;
						else p_dev=0;
						t=false;					
						break;
					}
				}
				if(t)
					for(j=0; j<p_dev; j++)
					{
						if(pri_vec[j].Free())
						{	
							pri_time[j]=curtime+pri_vec[j].InputZayav(z_buf,ist_zayaObs);
							if(j!=m-1) p_dev=j+1;
							else p_dev=0;
							t=false;
							break;
						}
					}

				if(t) 
				{					
					buf.buf_write(z_buf, ist_otk,ist_zayaW8 );
				}
			}	
		}

		if(poshag)
		{
			cout<<"=========================================================";
			cout<<"\n Текущее время = "<<(float)curtime<<"\n";
			cout<<"            *** ИСТОЧНИКИ ***\n";
			cout<<" Источник    Время    Заявок    Отказов\n";
			for( i=0; i <n; i++)
			{ 
				printf("%5d  %12.6f  %5d  %8d\n",i,(float)ist_time[i],ist_vec[i].ShowNum(),ist_otk[i]);
			}
			cout<<"            *** ПРИБОРЫ ***\n";
			cout<<"  Прибор     Время   Содержимое  Свободен  Указатель\n";
			for( i=0; i <m; i++)
			{
				if(pri_vec[i].Free()) pri_time[i]=-1;
				printf("%5d  %12.6f  %4d.%2d  %7d",i,(float)pri_time[i],pri_vec[i].cur_z.ist_num,pri_vec[i].cur_z.zaya_num,pri_vec[i].Free());
				if (p_dev == i) cout<<"         <-*\n";
				else cout << "\n";
			}
			cout<<"            *** БУФЕР ***\n";
			cout<<" Позиция     Время   Содержимое   Заполнение   Выборка\n";
			for( i=0; i<buf_size; i++)
			{	
				printf("%5d  %12.6f  %4d.%2d",i,(float)buf.buf_vec[i].cr8_time,buf.buf_vec[i].ist_num,buf.buf_vec[i].zaya_num);

				if(buf.ShowUk()==i) cout <<"         <-*";
				else cout<<"            ";

				int j=0;
				float last_time = buf.buf_vec[j].cr8_time;
				for(int i=0; i<buf_size; i++)
				{
					if(buf.buf_vec[i].cr8_time > last_time)
					{
						last_time = buf.buf_vec[i].cr8_time;
						j = i;
					}
				}
				if (j == i) cout<<"         <-*\n";
				else cout << "\n";
			}
			cout<<"=========================================================\n";
			getchar();
		}
		SumZayv=0;
		for(i=0; i<n; i++)
		{
			SumZayv+=ist_vec[i].ShowNum();
		}

// подборка N
	if(SumZayv==Ncycl)
	{
		float Pmin;
		float Nnew;
		Pmin=1;
		for( i=0; i < n; i++)
		{
			if(Pmin > (float)ist_otk[i]/ist_vec[i].ShowNum())
			{
				if((float)ist_otk[i]/ist_vec[i].ShowNum()!=0) Pmin=(float)ist_otk[i]/ist_vec[i].ShowNum();
			}
		}
		cout<<" Pmin = "<<(float)Pmin;
		Nnew = (1.643*1.643 )*( 1 -Pmin)/ ( Pmin*0.01);
		cout <<" \n"<< " Nnew = "<<Nnew;
		getchar();
		if(abs(Nnew-Ncycl)> (Ncycl/10)) Ncycl = Nnew;
		else break;
	}	
}

// закончить моделирование
	t=false;
	for( i=0; i<m;i++) 
		if(!pri_vec[i].Free())
		{
			t=true;
			break;
		}
	while(t)
	{
		for( i=0; i<m; i++)
		{
			if(! pri_vec[i].Free() )
			{
				min=pri_time[i];
				break;
			}
		}
		for( i=0; i<m; i++)
			if((pri_time[i] < min)&& (! pri_vec[i].Free())  ) min=pri_time[i];
		curtime=min;
		for( i=0; i<m; i++)
		{
			if(curtime == pri_time[i])
			{				
				pri_vec[i].SetFree();
				if(!buf.Empty())
				{					
					pri_time[i]=curtime+(float)pri_vec[i].InputZayav(buf.buf_read(ist_zayaW8),ist_zayaObs);					
				}			
			}		
	    }
		t=false;
		for(i=0; i<m;i++) 
		if(!pri_vec[i].Free())
		{
			t=true;
			break;
		}
		if(!buf.Empty()) t=true;
	}

// автоматический режим
	cout << "\n Время моделирования : "<< curtime <<"\n\n";
	cout << " Источник    Заявок      Ротк         Тпреб         Тбп         Тобсл"<<endl;

	float z;
	float Tpreb=0.0, Potk=0.0, Tbp=0.0, Tobs=0.0;
	for( i=0; i <n; i++)
	{
		z=(float)ist_otk[i]/ist_vec[i].ShowNum();
		(float)ist_zayaVsmo[i]=ist_zayaObs[i]+ist_zayaW8[i];
		printf("  %4d  %9d  %12.6f  %11.6f  %11.6f  %11.6f\n",i,ist_vec[i].ShowNum(),z,
			(float)ist_zayaVsmo[i]/ist_vec[i].ShowNum(),(float)ist_zayaW8[i]/ist_vec[i].ShowNum(),(float)ist_zayaObs[i]/ist_vec[i].ShowNum());
		Potk=Potk+z;
		Tpreb=Tpreb+(float)ist_zayaVsmo[i]/ist_vec[i].ShowNum();
		Tbp=Tbp+(float)ist_zayaW8[i]/ist_vec[i].ShowNum();
		Tobs=Tobs+(float)ist_zayaObs[i]/ist_vec[i].ShowNum();
	}
	cout<<"\n Среднее значение :    "<<(float)Potk/n<<"     "<<(float)Tpreb/n<<"     "<<(float)Tbp/n<<"     "<<(float)Tobs/n<<endl;
	cout << "\n  Прибор     Время работы     Занятость"<<endl;
	for( i=0; i <m; i++)
	{
		printf("  %4d  %16.6f  %12.6f \%%\n",i,(float)pri_vec[i].timeinWork,(float) pri_vec[i].timeinWork*100/curtime);
	}

	getch();

}