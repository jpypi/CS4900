#include <math.h>

double qsolve_sqrt(double a) {
    if (a < 0) {
        return -1.0;
    }

    return sqrt(a);
}
