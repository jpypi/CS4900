/*
 * Author: James Jenkins
 * Date: 2016-10-21
 */
#include <stdio.h>
#include <math.h>
#include <float.h>


int
main(int argc, char *argv[]) {
    float a = 1.0;
    float b = 1.0;
    printf("Some subtraction:\n1.0 - 1.0 = %f\n", a - b);

    printf("FLT_ROUNDS: %d\n", FLT_ROUNDS);

    printf("\nSingles:\n");
    printf("Max binary digits in significand: %d\n", FLT_MANT_DIG);
    printf("Max decimal digits precision: %d\n", FLT_DIG);
    printf("Smallest positive normal float: %#.*e\n", FLT_DIG, FLT_MIN);
    printf("Largest positive finite float: %#.*e\n", FLT_DIG, FLT_MAX);
    // the difference between 1.0 and the smallest float bigger than 1.0.
    printf("Diff between 1.0 and next largest float > 1.0: %#.*g\n", FLT_DIG, FLT_EPSILON);

    // FLT_MIN_EXP - One more than the smallest exponent available in the float type.
    // FLT_MAX_EXP - One more than the largest exponent available in the float type.
    // FLT_MIN_10_EXP - the smallest n such that 10**n is a non-zero normal number as a float.
    // FLT_MAX_10_EXP - the largest n such that 10**n is finite as a float.


    printf("\nDoubles:\n");
    printf("Max binary digits in significand: %d\n", DBL_MANT_DIG);
    printf("Max decimal digits precision: %d\n", DBL_DIG);
    printf("Smallest positive normal double: %#.*e\n", DBL_DIG, DBL_MIN);
    printf("Largest positive finite double: %#.*e\n", DBL_DIG, DBL_MAX);
    // the difference between 1.0 and the smallest double bigger than 1.0.
    printf("Diff between 1.0 and next largest double > 1.0: %#.*e\n", 14, DBL_EPSILON);

    // DBL_MIN_EXP - One more than the smallest exponent available in the double type.
    // DBL_MAX_EXP - One more than the largest exponent available in the double type.
    // DBL_MIN_10_EXP - the smallest n such that 10**n is a non-zero normal number as a double.
    // DBL_MAX_10_EXP - the largest n such that 10**n is finite as a double.


    return 0;
}
