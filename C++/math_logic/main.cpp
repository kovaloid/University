#pragma comment(lib, "bdd.lib")
#include "bdd.h"
#include <fstream>
#include <string>
using namespace std;

#define N_VAR 72	// число булевых переменных
#define N 8			// число объектов
#define M 3			// число свойств
#define LOG_N 3

ofstream out;

void fun(char* varset, int size); // функция, используемая для вывода решений

void main(void)
{
	// инициализация
	bdd_init(1000000, 100000);
	bdd_setvarnum(N_VAR);
	
	// ->--- вводим функцию p(k, i, j) следующим образом ( pk[i][j] ):
	bdd p1[N][N];
	bdd p2[N][N];
	bdd p3[N][N];

	unsigned I = 0;
	for (unsigned i = 0; i < N; i++)
	{
		for (unsigned j = 0; j < N; j++)
		{
			p1[i][j] = bddtrue;
			for (unsigned k = 0; k < LOG_N; k++) p1[i][j] &= ((j >> k) & 1) ? bdd_ithvar(I + k) : bdd_nithvar(I + k) ;
			p2[i][j] = bddtrue;
			for (unsigned k = 0; k < LOG_N; k++) p2[i][j] &= ((j >> k) & 1) ? bdd_ithvar(I + LOG_N + k) : bdd_nithvar(I + LOG_N + k) ;
			p3[i][j] = bddtrue;
			for (unsigned k = 0; k < LOG_N; k++) p3[i][j] &= ((j >> k) & 1) ? bdd_ithvar(I + LOG_N*2 + k) : bdd_nithvar(I + LOG_N*2 + k) ;
		}
		I += LOG_N*M;
	}
	// -<---

	bdd task = bddtrue; // булева функция, определяющая решение, начальное значение true

	// ->--- ограничение по-умолчанию 6
	for (unsigned i = 0; i < N; i++)
	{
		bdd temp1 = bddfalse;
		bdd temp2 = bddfalse;
		bdd temp3 = bddfalse;
		for (unsigned j = 0; j < N; j++)
		{
			temp1 |= p1[i][j];
			temp2 |= p2[i][j];
			temp3 |= p3[i][j];
		}
		task &= temp1 & temp2 & temp3;
	}
	// -<---
	
	// ограничение типа 1 (4)
	task &= p3[3][3];
	task &= p3[6][6];
	task &= p2[5][5];
	task &= p1[2][2];
    // дополнительное ограничение типа 1
	task &= p2[1][1];
	//task &= p1[8][8];

	// ограничение типа 2 (5)
	for (unsigned i = 0; i < N; i++) task &= !( p1[i][0] ^ p2[i][0] );
	for (unsigned i = 0; i < N; i++) task &= !( p2[i][2] ^ p3[i][2] );
	for (unsigned i = 0; i < N; i++) task &= !( p1[i][4] ^ p3[i][4] );
	for (unsigned i = 0; i < N; i++) task &= !( p1[i][6] ^ p2[i][6] );
	for (unsigned i = 0; i < N; i++) task &= !( p2[i][3] ^ p3[i][3] );
    // дополнительное ограничение типа 2
	//for (unsigned i = 0; i < N; i++) task &= !( p2[i][8] ^ p3[i][8] );
	// !(a ^ b) = (a <=> b)

	int j[4]={1,3,4,6};

	// ->--- ограничение типа 3 (4)
	//task &= !p1[0][1] & !p1[N-1][1] & !p3[0][2] & !p3[N-1][2];
	//task &= !p1[0][2] & !p1[N-1][2] & !p3[0][1] & !p3[N-1][1];
	task &= !p1[0][1] & !p3[0][2];
	task &= !p1[0][2] & !p3[0][1];
	for (unsigned i = 0; i < 4; i++) task &= !( p1[j[i]][1] ^ p3[j[i] + 1][2] );

	//task &= !p1[0][3] & !p1[N-1][3] & !p3[0][4] & !p3[N-1][4];
	//task &= !p1[0][4] & !p1[N-1][4] & !p3[0][3] & !p3[N-1][3];
	task &= !p1[0][3] & !p3[0][4];
	task &= !p1[0][4] & !p3[0][3];
	for (unsigned i = 0; i < 4; i++) task &= !( p1[j[i]][3] ^ p3[j[i] + 1][4] );

	//task &= !p2[0][4] & !p2[N-1][4] & !p3[0][5] & !p3[N-1][5];
	//task &= !p2[0][5] & !p2[N-1][5] & !p3[0][4] & !p3[N-1][4];
	task &= !p2[0][4] & !p3[0][5];
	task &= !p2[0][5] & !p3[0][4];
	for (unsigned i = 0; i < 4; i++) task &= !( p2[j[i]][4] ^ p3[j[i] + 1][5] );

	//task &= !p2[0][6] & !p2[N-1][6] & !p1[0][7] & !p1[N-1][7];
	//task &= !p2[0][7] & !p2[N-1][7] & !p1[0][6] & !p1[N-1][6];
	task &= !p2[0][6] & !p1[0][7];
	task &= !p2[0][7] & !p1[0][6];
	for (unsigned i = 0; i < 4; i++) task &= !( p2[j[i]][6] ^ p1[j[i] + 1][7] );

	// ->--- ограничение типа 4 (2)
	bdd temp1 = bddtrue;
	bdd temp2 = bddtrue;
	//task &= !p3[0][1] & !p3[N-1][1] & !p1[0][2] & !p1[N-1][2];
	//task &= !p3[0][2] & !p3[N-1][2] & !p1[0][1] & !p1[N-1][1];
	task &= !p3[0][1] & !p1[0][2];
	task &= !p3[0][2] & !p1[0][1];
	for (unsigned i = 0; i < 4; i++) temp1 &= !( p3[j[i]][1] ^ p1[j[i] + 1][2] );
	for (unsigned i = 0; i < 4; i++) temp2 &= !( p1[j[i]][2] ^ p3[j[i] + 1][1] );
	task &= temp1 | temp2;

	temp1 = bddtrue;
	temp2 = bddtrue;
	//task &= !p1[0][6] & !p1[N-1][6] & !p3[0][7] & !p3[N-1][7];
	//task &= !p1[0][7] & !p1[N-1][7] & !p3[0][6] & !p3[N-1][6];
	task &= !p1[0][6] & !p3[0][7];
	task &= !p1[0][7] & !p3[0][6];
	for (unsigned i = 0; i < 4; i++) temp1 &= !( p1[j[i]][6] ^ p3[j[i] + 1][7] );
	for (unsigned i = 0; i < 4; i++) temp2 &= !( p3[j[i]][7] ^ p1[j[i] + 1][6] );
	task &= temp1 | temp2;
	// -<---

	// ->--- ограничение по-умолчанию 5
	for (unsigned j = 0; j < N; j++)
		for (unsigned i = 0; i < N - 1; i++)
			for (unsigned k = i + 1; k < N; k++)
			{
				task &= p1[i][j] >> !p1[k][j];
				task &= p2[i][j] >> !p2[k][j];
				task &= p3[i][j] >> !p3[k][j];
			}
	// -<---

	// вывод результатов
	out.open("out.txt");
	unsigned satcount = (unsigned)bdd_satcount(task);
	out<<satcount<<" solutions:\n"<<endl;
	if (satcount) bdd_allsat(task, fun);
	out.close();

	bdd_done(); // завершение работы библиотеки
}

// Ниже реализация функций, управляющих выводом результатов.
// Рекомендуется самостоятельно с ними ознакомиться.
// В собственных заданиях следует использовать эти функции
// или придумать собственные.

char var[N_VAR];

void print(void)
{
    string st[M][N];

	st[0][0]="Василий";
	st[0][1]="Петр";
	st[0][2]="Николай";
	st[0][3]="Мария";
	st[0][4]="Екатерина";
	st[0][5]="Полина";
	st[0][6]="Виктор";
	st[0][7]="Алексей";
	//st[0][8]="Елена";

	st[1][0]="белой";
	st[1][1]="синей";
	st[1][2]="красной";
	st[1][3]="серой";
	st[1][4]="зеленой";
	st[1][5]="оранжевой";
	st[1][6]="желтой";
	st[1][7]="черной";
	//st[1][8]="фиолетовой";

	st[2][0]="рок";
	st[2][1]="рэп";
	st[2][2]="регги";
	st[2][3]="классику";
	st[2][4]="техно";
	st[2][5]="блюз";
	st[2][6]="джаз";
	st[2][7]="шансон";
	//st[2][8]="хаус";

	for (unsigned i = 0; i < N; i++)
	{
		out<<i<<": ";
		for (unsigned j = 0; j < M; j++)
		{
			unsigned J = i*M*LOG_N + j*LOG_N;
			unsigned num = 0;
			for (unsigned k = 0; k < LOG_N; k++) num += (unsigned)(var[J + k] << k);
			out<<num<<' ';
		}
		out<<endl;
	}
	out<<endl;
	for (unsigned i = 0; i < N; i++)
	{
		for (unsigned j = 0; j < M; j++)
		{
			unsigned J = i*M*LOG_N + j*LOG_N;
			unsigned num = 0;
			for (unsigned k = 0; k < LOG_N; k++) num += (unsigned)(var[J + k] << k);
			if(j==0) out<<st[j][num]<<" в ";
			if(j==1) out<<st[j][num]<<" палатке слушает ";
			if(j==2) out<<st[j][num]<<".";
		}
		out<<endl;
	}
	out<<endl;
}

void build(char* varset, unsigned n, unsigned I)
{
	if (I == n - 1)
	{
		if (varset[I] >= 0)
		{
			var[I] = varset[I];
			print();
			return;
		}
		var[I] = 0;
		print();
		var[I] = 1;
		print();
		return;
	}
	if (varset[I] >= 0) 
	{
		var[I] = varset[I];
		build(varset, n, I + 1);
		return;
	}
	var[I] = 0;
	build(varset, n, I + 1);
	var[I] = 1;
	build(varset, n, I + 1);
}

void fun(char* varset, int size)
{
	build(varset, size, 0);
}