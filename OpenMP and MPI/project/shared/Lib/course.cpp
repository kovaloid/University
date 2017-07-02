#include <cstdlib>
#include <string>
#include <math.h>
#include <omp.h>
//#include "course.h"

using namespace std;

struct Figure {
	int height;
	int width;
	double weight;	
};

void Matr(int A[][400],int n)
	{
	
	float w0[400],w[400],summ=0,w0norm[400],e,d,d0;
	int i,j,k;
	#pragma omp parallel for
	for (i = 0; i < n; i++) {
		w0[i] = 0;
	}
	w0[0] = 1;
	#pragma omp parallel
	do {
		for (i = 0; i < n; i++) {
			summ = summ + w0[i] * w0[i];
		}
		d0 = sqrt(summ);
		for (i = 0; i < n; i++) {
			w0norm[i] = w0[i] / d0;
		}
		for (i = 0; i < n; i++) {
			w[i] = 0;
			for (j = 0; j < n; j++)
				w[i] = w[i] + A[i][j] * w0norm[j];
		}
		summ = 0;
		for (i = 0; i < n; i++) {
			summ = summ + w[i] * w[i];
		}
		d = sqrt(summ);
		e= fabs(d - d0);
		for (i = 0; i < n; i++)
			w0[i] = w[i];
		summ = 0;
	}
	while(e > 0.001);
	//printf("%f\n",d);
	for (i = 0; i < n; i++) {
	//printf("%f\n",w0norm[i]);
	}
}

int startx() {
	omp_set_num_threads(3);	
	int N = 400;
	int A[N][400];
	double result[N][N];
	double result_sum[N][N];
	Figure figures[N][N];
	
	
    
    Figure figure;
	#pragma omp parallel for
	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) {
		    figures[i][j] = figure;
	    }
	}
	
	#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		#pragma omp parallel for
	    for (int j = 0; j < N; j++) {
			#pragma omp parallel for
	        for (int k = 0; k < N; k++) {
	            result[i][j] = figures[i][k].weight * A[k][j];
	        }
	    }
	}
	
	#pragma omp parallel for
	for (int i = 0; i < N; i++) {	
		#pragma omp parallel for
	    for (int j = 0; j < N; j++) {
			result_sum[i][j] = figures[i][j].width + A[i][j];	
		}
	}
	
	#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		#pragma omp parallel for
	    for (int j = 0; j < 30; j++) {
			Matr(A,N);
			result_sum[i][j] = figures[i][j].height + A[i][j];
		}
	}
	
	
	//----------------------------------
	 

   return -10; 

}

int main() {
    startx();
  return 69;
}