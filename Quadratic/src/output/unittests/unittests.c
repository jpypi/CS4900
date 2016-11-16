/*
* t1.c
* Unit tests for quad_roots() 
* solves a * x^2 + b x + c = 0
*   for the roots
* x1 and x2
* *
* This uses the qsolve_sqrt() which calls the system sqrt()
*/
#include <stdlib.h>
#include "cunit.h"
#include "../output.h"
#include <float.h>


int main() {
int	ret;     // return value from qsolve_roots
// double  a, b, c; // scratch variables
double  a,b,c,a1,b1,c1;  // scratch variables


// initialize the unit testing framework
cunit_init();

// A "good" unit test, need to allow for round off!
// qsolve_roots() passes this one. ;-)
// This allows about one base 10 least significant digit of error
// (x - x1)*(x - x2) = 0
a = 3.1;
b = 3.3;
c = 3.6;
//ret = get_coeficient("a = ", &a1);
//assert_eq("ret",ret,0);
//ret = get_coeficient("b = ", &b1);
//assert_eq("ret",ret,0);
//ret = get_coeficient("c = ", &c1);
//assert_eq("ret",ret,0);
//assert_eq("ret",ret,2);
//assert_feqrerr("a",a, a1, (double)FLT_MIN);
//assert_feqrerr("b",b, b1, (double)FLT_MIN);
//assert_feqrerr("c",c, c1, (double)FLT_MIN);
exit(0);
}
