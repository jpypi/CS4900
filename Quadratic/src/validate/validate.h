#ifndef _QSOLVE_VALIDATE
#define _QSOLVE_VALIDATE

#include <float.h>

#define ALLOWABLE_ZERO_ERROR FLT_EPSILON*2

int daeq(double a, double b, double aerror);

#endif
