#include <stdio.h>
#include <math.h>
#include <float.h>


int
main(int argc, char *argv[]) {
    float a = 1.0;
    float b = 1.0;
    printf("1.0 - 1.0 = %f\n", a - b);

    printf("Max binary digits in significand: %d\n", FLT_MANT_DIG);
    // FLT_MIN_EXP - One more than the smallest exponent available in the float type.
    // FLT_MAX_EXP - One more than the largest exponent available in the float type.
    printf("Max decimal digits precision: %d\n", FLT_DIG);
    // FLT_MIN_10_EXP - the smallest n such that 10**n is a non-zero normal number as a float.
    // FLT_MAX_10_EXP - the largest n such that 10**n is finite as a float.
    printf("Smallest positive normal float: %f\n", FLT_MIN);
    printf("Largest positive finite float: %f\n", FLT_MAX);

    // the difference between 1.0 and the smallest float bigger than 1.0.
    printf("Diff between 1.0 and next largest float > 1.0: %f", FLT_EPSILON);

    return 0;
}
