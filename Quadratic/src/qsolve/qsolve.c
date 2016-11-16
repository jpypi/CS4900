#include <math.h>

#include "qsolve.h"
#include "../sqrt/sqrt.h"
#include "../validate/validate.h"

/*
 * Implements the quadradic formula to find the non-imaginary roots (zeros) (if
 * they exist) of a degree 2 polynomial (aka a quadradic equation).
 *     ax^2 + b*x + c = 0
 * Below is the formula that is implemented:
 *     -b +- sqrt(pow(b, 2) - 4*a*c) / 2*a
 *
 * Return values:
 *     QSOLVE_XXXX (where XXXX is a short abbreviated description of the
 *     meaning)
 *     See qsolve.h for full list of defined constant values.
 */
int qsolve(double a, double b, double c, double *root1, double *root2) {
#ifdef LOG_FILE
    fprintf(LOG_FILE, "qsolve: a:%le b:%le c:%le r1:%p r2%p\n", a, b, c, root1, root2);
#endif

    int root_type = QSOLVE_DOUBLE_ROOT;

    double b_sq = powf(b, 2);
    double four_a = 4 * a;
    double four_a_c = four_a * c;
    double descriminate_pre = b_sq - four_a_c;

    // Is this safe/good enough?
    if (daeq(a, 0.0, ALLOWABLE_ZERO_ERROR)) {
        root_type = QSOLVE_SINGLE_ROOT;
    } else if (descriminate_pre < 0) {
        return QSOLVE_IMG_ROOTS;
    }


    double descriminate = qsolve_sqrt(descriminate_pre);
    double two_a = 2 * a;
    double numerator_1 = -b + descriminate;
    double numerator_2 = -b - descriminate;
    *root1 = numerator_1 / two_a;
    *root2 = numerator_2 / two_a;

    return root_type;
}
