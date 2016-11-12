#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <float.h>



#define g 1.23456789e5
#define h 1.23456789e-5

#define i 1.5555555559
#define j 1.5555552222
#define k 1.5555549


int main(int argc, char const *argv[])
{

	printf("%#.*e\n", FLT_DIG, g);
	printf("%#.*e\n", FLT_DIG, h);

	printf("%#.*e\n", FLT_DIG, i);
	printf("%#.*e\n", FLT_DIG, j);
	printf("%#.*e\n", FLT_DIG, k);

/*
Conclusion for our specific implementation is that output is rounded (normal)
	rather than being truncated.


Note that many C compilers try to follow IEEE 754 for floating-point matters. 
IEEE 754 recommends rounding according to the current rounding mode for 
	conversions from binary floating-point to decimal. The default rounding
	mode is “round to nearest and ties to even”. Some compilation platforms 
	do not take the rounding mode into account and always round according to 
	the default nearest-even mode in conversions from floating-point to decimal.

*/




	return 0;
}