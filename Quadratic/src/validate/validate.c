#include <math.h>

/*
 * daeq: Double absolute equals
 */
int daeq(double a, double b, double aerror) {
    return (fabs(a-b) < aerror);
}
