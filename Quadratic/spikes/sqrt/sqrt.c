#include <stdio.h>
#include <math.h>
#include <unistd.h>

//prints double and its square root using the sqrt function
void psqrt(double d)
{
	printf("Original: %lf   Sqrt: %lf\n", d, sqrt(d));
}

//demos sqrt function on various double numbers (and non-numbers)
void main() 
{
	psqrt(0.0);
	psqrt(-1.0);
	psqrt(100.0);
	psqrt(NAN);
	psqrt(INFINITY);
	psqrt(-INFINITY);
}
