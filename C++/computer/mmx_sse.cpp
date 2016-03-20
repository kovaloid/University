#include <stdio.h>
#include <conio.h>
#include <xmmintrin.h>

int main(void) 
{
	char qw1[8] = {1, 1, 1, 1, 1, 1, 1, 1};
	char qw2[8] = {2, 2, 2, 2, 2, 2, 2, 2};
	float c[4] = {1, 6, 3, 4};
	float d[4] = {5, 6, 7, 4};
	double f[2]= {16, 4};
	char a128[16] = {1, 18, 3, 19, 5, 21, 7, 23, 9, 25, 11, 27, 13, 29, 15, 31};
	char b128[16] = {17, 2, 19, 4, 21, 6, 23, 8, 25, 10, 27, 12, 29, 14, 31, 16};
	float a[4] = {17, 18, 3, 4};
	float b[4] = {1, 2, 19, 20};

	_asm { //sse1
		movups xmm0, c
		movups xmm1, d
		cmpps xmm0, xmm1, 0
		movups c, xmm0
	}
	printf("\nComparing elements of vectors c and d :\n");
	for (int i = 0; i < 4; i++)
		printf("%f ", c[i]);

	_asm { //sse2
		movups xmm0, a
		movups xmm1, b
		maxpd xmm0, xmm1
		movups a, xmm0
	}
	printf("\n\nMaximum elements of vectors a and b:\n");
	for (int i = 0; i < 4; i++)
		printf("%f ", a[i]);

	//__m64 delta_pi8 = _mm_or_si64(_mm_subs_pu8(A_pi8,B_pi8),_mm_subs_pu8(B_pi8,A_pi8));

	//float *ptr = (float*)&delta_pi8;
	//printf("\n\n%x   %x  %x", ptr[0],ptr[1],ptr[2]);

	printf("\n\n");
	float x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	float y[8] = {9, 10, 11, 12, 13, 14, 15, 16};
	__m64 x_pi8 = *(const __m64 *)x;
	__m64 y_pi8 = *(const __m64 *)y;
	__m64 res = _mm_add_pi8(x_pi8, y_pi8); //intrinsic - function
	float *z = (float*)&res;
	for (int i = 0; i < 8; i++)
		printf("%f\n",z[i]);

	//----------------------------------------------------------------
	/*__m128 m128_1;
	__m128 m128_2;

	_asm {
		movups xmm0, a128
		movups xmm1, b128
		movaps xmmword ptr m128_1.m128_f32, xmm0
		movaps xmmword ptr m128_2.m128_f32, xmm1
	}
	__m128 _mm_add_pi8 (__m128 m128_1 , __m128 m128_2);

	_asm {
		movaps xmm0, m128_1
		movaps xmm1, m128_2
		movups a128, xmm0
		movups b128, xmm1
	}

	printf("\n\n");
	for (int i = 0; i<16; i++)
		printf("%d ", a128[i]);
	printf("\n\n");
	for (int i = 0; i<16; i++)
		printf("%d ", b128[i]);*/

	//__m64 _mm_add_pi8 (__m64 m1 , __m64 m2);
//----------------------------------------------------------------------
	
	
	/*_asm { //mmx
		movq mm0, qw1
		movq mm1, qw2
		pcmpeqb mm0, mm1
		movq qw1, mm0
	}
	printf("Summing elements of vectors qw1 + qw2 :\n");
	for (int i = 0; i < 8; i++)
		printf("%d ", qw1[i]);

	_asm { //sse1
		movups xmm0, c
		movups xmm1, d
		addps xmm0, xmm1
		movups c, xmm0
	}
	printf("\n\nSumming elements of vectors c + d :\n");
	for (int i = 0; i < 4; i++)
		printf("%f ", c[i]);

	_asm { //sse2
		movups xmm1, f
		sqrtpd xmm0, xmm1
		movups f, xmm0
	}
	printf("\n\nSquare of  %f is %f\n", f[0], f[1]);

	_asm { //sse1
		movups xmm0, a128
		movups xmm1, b128
		pminub xmm0, xmm1
		movups a128, xmm0
	}
	printf("\nComparing elements :\n");
	for (int i = 0; i<16; i++)
		printf("( %d , %d) ; ", a128[i], b128[i]);
	printf("\nMinimum elements :\n");
	for (int i = 0; i<16; i++)
		printf("%d ", a128[i]);*/

	getch();
	return 0;
}