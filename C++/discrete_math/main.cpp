#include <stdio.h>
#include <conio.h>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>
#include <locale.h>

using namespace std;

#define MAX_N 100
#define INFINITY 10000	// Условное число, обозначающее бесконечность

int C[MAX_N][MAX_N];	// Матрица "пропускных способностей"
int F[MAX_N][MAX_N];	// Матрица "текущего потока в графе"
int P[MAX_N][MAX_N];	// Матрица "стоимости (расстояний)"
int push[MAX_N];		// Поток в вершину [v] из начальной точки
int mark[MAX_N];		// Отметки на вершинах, в которых побывали
int pred[MAX_N];		// Откуда пришли в вершину [v] (предок)
int dist[MAX_N];		// Расстояние до вершины [v] из начальной точки
int N, M, s ,t;			// Кол-во вершин, ребер, начальная и конечные точки
int max_flow;
int min_cost;

ifstream file_in("data.txt");
ofstream file_out("result.txt");

void file_read()
{
	int u, v, c, p;
	cout << "Читаются данные из файла..." << endl;
	file_in >> N >> M >> s >> t; N++;

	for(int i = 0; i < M; i++)
	{
		file_in >> u >> v >> c >> p;
		C[u][v] = c;
		P[u][v] = p;
		P[v][u] = -p;
	}
	file_in.close();

	cout << "Матрица пропускных способностей:" << endl;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf(" %3d",C[i][j]);
		}
		cout << endl;
	}

	cout << "Матрица стоимости (расстояний):" << endl;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf(" %3d",P[i][j]);
		}
		cout << endl;
	}
}

int edge_cost(int u, int v)
{
	if( C[u][v] - F[u][v] > 0 ) return P[u][v];
	else return INFINITY;
}

int check_cycles()
{
	for(int u = 1; u < N; u++)
		for(int v = 1; v < N; v++)
			if( dist[v] > dist[u] + edge_cost(u, v) )
				return u;
			
	return INFINITY;
}

void init()
{
	for(int i = 1; i < N; i++)
	{
		mark[i] = 0;
		push[i] = 0;
		pred[i] = 0;
		dist[i] = INFINITY;
	}
}

// Алгоритм Беллмана-Форда

int bf(int s)
{
	init();
	queue<int> Q;
	pred[s] = s;
	dist[s] = 0;

	Q.push(s);
	Q.push(MAX_N);

	int u, series = 0;
	while( !Q.empty() )
	{
		while( Q.front() == MAX_N )
		{
			Q.pop();
			if( ++series > N ) return check_cycles();
			else Q.push(MAX_N);
		}

		u = Q.front(); Q.pop();
		for(int v = 1; v < N; v++)
			if( dist[v] > dist[u] + edge_cost(u, v) )
			{
				dist[v] = dist[u] + edge_cost(u, v);
				pred[v] = u;
				Q.push(v);
			}
	}
}

// Алгоритм поиска в ширину

int bfs(int s, int t)
{
	init();
	queue<int> Q;
	mark[s] = 1;
	pred[s] = s;
	push[s] = INFINITY;
    
	Q.push(s);
	while( !mark[t] && !Q.empty() )
	{
		int u = Q.front(); Q.pop();
		for(int v = 1; v < N; v++)
			if( !mark[v] && (C[u][v]-F[u][v] > 0) )
			{
				push[v] = min(push[u], C[u][v]-F[u][v]);
				mark[v] = 1;
				pred[v] = u;
				Q.push(v);
			}
	}

	return mark[t];
}

// Алгоритм Форда-Фалкерсона

void max_flow_ff() 
{
	int u, v, flow = 0;

	while( bfs(s, t) )
	{
		int add = push[t];

		v = t; u = pred[v];
		while( v != s )
		{
			F[u][v] += add;
			F[v][u] -= add;
			v = u; u = pred[v];
		}
		flow += add;
	}

	max_flow = flow;

	cout << "Матрица насыщенности:" << endl;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(F[i][j] < 0)
				printf(" %3d",0);
			else
				printf(" %3d",F[i][j]);
		}
		cout << endl;
	}

	cout << "Насыщенность потоков:" << endl;
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<M; j++)
		{
			if((F[i][j] >= 0) && (C[i][j] != 0))
				printf("   ( %2d , %2d )  =  %d/%d\n", i, j, C[i][j], F[i][j]);
		}
	}
}

// Алгоритм вычисления максимального потока минимальной стоимости

void min_cost_flow()
{
	int u, v, flow = 0;
	int add = INFINITY;
	int neg_cycle;

	neg_cycle = bf(t);
	while( neg_cycle != INFINITY )
	{
		v = neg_cycle; u = pred[v];
		do
		{
			add = min(add, C[u][v]-F[u][v]);
			v = u; u = pred[v];
		}
		while( v != neg_cycle );

		v = neg_cycle; u = pred[v];
		do
		{
			F[u][v] += add;
			F[v][u] -= add;
			v = u; u = pred[v];
		}
		while( v != neg_cycle );

		neg_cycle = bf(t);
	}

	cout << "Стоимость расстояний между узлами:" << endl;
	for(int u = 1; u < N; u++)
		for(int v = 1; v < N; v++)
			if( F[u][v] > 0 )
			{
				min_cost += F[u][v] * P[u][v];
				printf("   ( %2d , %2d )  =  %d\n", u, v, F[u][v] * P[u][v]);
			}
}

void file_write()
{
	cout << "Вывод результата..." << endl;
	cout << "1) Максимальная пропускная способность: " << max_flow << endl;
	cout << "2) Минимальная стоимость максимального потока: " << min_cost << endl;
	file_out << "Максимальная пропускная способность: " << max_flow << endl;
	file_out << "Минимальная стоимость максимального потока: " << min_cost << endl;
	file_out.close();
}

void main()
{
	setlocale(LC_CTYPE, "");

	if(!file_in || !file_out)
	{
		cout << "Ошибка открытия файла!";
		getch();
		exit(0);
	}

	file_read();
	max_flow_ff();
	min_cost_flow();
	file_write();
	
	cout << "Нажмите любую клавишу для выхода...";
	getch();
}
