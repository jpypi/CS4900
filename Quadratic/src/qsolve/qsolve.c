#include "qsolve.h"
#include <math.h>

/*
 * Return values:
 *  QSOLVE_X
 *  See qsolve.h for possible values
 *  -b +- sqrt(pow(b, 2) - 4*a*c) / 2*a
 *  ax^2 + b*x + c
 */
int qsolve(double a, double b, double c, double *root1, double *root2) {
    double b_sq = powf(b, 2);
    double four_a = 4 * a;
    double four_a_c = four_a * c;
    double descriminate_pre = b_sq - four_a_c;
    double descriminate = sqrtf(descriminate_pre);
    double two_a = 2 * a;
    double numerator_1 = -b + descriminate;
    double numerator_2 = -b - descriminate;
    *root1 = numerator_1 / two_a;
    *root2 = numerator_2 / two_a;

    return QSOLVE_DOUBLE_ROOT;
}
