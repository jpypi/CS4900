#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define a 1.0
#define b 0.1
#define c 1e10
#define d 2e-10
#define e 1e100
#define f 1e-100
#define g 1.23456789e5
#define h 1.23456789e-5

//prints doubles using different format specifiers
void p(double *array, int n)
{
	int i = 0;
	for (i=0; i<n; i++)
	{
		printf("1. %lf\n", array[i]);
		printf("2. %#e\n", array[i]);
		printf("3. %#.5e\n", array[i]);
		printf("4. %#.e\n", array[i]);
		//printf("5. %#.*e\n", array[i], 10);
		printf("6. %#.*e\n", 14, array[i]); //<-- best flexibility
		//printf(" %2$#e\n", array[i]);
		//printf(" 

		printf("\n");
	}
}

//demos the printf function's format specifiers for doubles
void main() 
{
	double array[8];
	array[0] = a;
	array[1] = b;
	array[2] = c;
	array[3] = d;
	array[4] = e;
	array[5] = f;
	array[6] = g;
	array[7] = h;

	p(array, 8);
}
