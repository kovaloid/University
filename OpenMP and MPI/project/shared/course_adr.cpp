#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <math.h>

using namespace std;

struct Figure {
	int height;
	int width;
	double weight;
};

void Matr(Figure A[][400],int n)
	{
	float w0[400], w[400], summ=0, w0norm[400], e, d, d0;
	int i,j,k;
	for (i = 0; i < n; i++) {
		w0[i] = 0;
	}
	w0[0] = 1;
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
				w[i] = w[i] + A[i][j].width * w0norm[j];
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
	while(e>0.001);
	//printf("%f\n",d);
	for (i = 0; i < n; i++) {
	//printf("%f\n",w0norm[i]);
	}
}

int main() {
    unsigned int start_time =  clock(); 

	int N = 400;
	int A[N][400];
	double result[N][N];
	double result_sum[N][400];
	Figure figures[N][400];
	
	
	/* initialize random seed: */
    srand (time(NULL));
    
    Figure figure;
	
	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) {
		    A[i][j] = rand() % 100 + 1;
		    figure.height = rand() % 1000000 + 1;
		    figure.weight = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/100.00));;
		    figure.width = rand() % 10 + 1;
		    figures[i][j] = figure;
	    }
	}
	
	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) {
	        for (int k = 0; k < N; k++) {
	            result[i][j] = figures[i][k].weight * A[k][j];
	        }
	    }
	}
	
	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) {
			result_sum[i][j] = figures[i][j].width + A[i][j];	
		}
	}
	
	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < 30; j++) {
			Matr(figures,N);
			result_sum[i][j] = figures[i][j].height + A[i][j];
		}
	}
	
	
	//----------------------------------
	 

    unsigned int end_time =  clock(); 
    cout << (end_time - start_time) / 1000 << endl;
    
    for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) {
		  // cout << result[i][j];
	    }
	}
	
	return 0;
}