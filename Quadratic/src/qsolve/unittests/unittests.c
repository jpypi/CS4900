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
#include "../qsolve.h"
#include <float.h>


int main() {
int	ret;     // return value from qsolve_roots
// double  a, b, c; // scratch variables
double  a,b,c,x1,x2,r1,r2;  // scratch variables


// initialize the unit testing framework
cunit_init();

// A "good" unit test, need to allow for round off!
// qsolve_roots() passes this one. ;-)
// This allows about one base 10 least significant digit of error
// (x - x1)*(x - x2) = 0


x1 = -0.0085680;
x2 = -3676.5;
a = 2.0;
b = 7353.0;
c = 63.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, FLT_MIN);
assert_feqrerr("x2", r2, x2, FLT_MIN);



x1 = -1.0;
x2 = -1.0;
a = 1.0;
b = 2.0;
c = 1.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,QSOLVE_SINGLE_ROOT);
assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );



x1 = -100.0;
x2 = 0.01;
a = 100.0;
b = 9999.0;
c = 100.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x2, 10.0*cunit_dmacheps );
assert_feqrerr("x2", r2, x1, 10.0*cunit_dmacheps );


//good
x1 = -1.0;
x2 = -0.20;
a = 5.0;
b = 6.0;
c = 1.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x2, 10.0*cunit_dmacheps );
assert_feqrerr("x2", r2, x1, 10.0*cunit_dmacheps );


//good
x1 = -4.56155281280883;
x2 = -0.438447187191170;
a = 1.0;
b = 5.0;
c = 2.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x2, 10.0*cunit_dmacheps );
assert_feqrerr("x2", r2, x1, 10.0*cunit_dmacheps );


//good
x1 = 4.64575131106459;
x2 = -0.645751311064591;
a = 1.0;
b = -4.0;
c = -3.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );


//good
x1 = 2.0;
x2 = -2.0;
a = 1.0;
b = 0.0;
c = -4.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );


//good
//x1 = 4.64575131106459;
//x2 = -0.645751311064591;
a = -1.0;
b = -1.0;
c = -1.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,QSOLVE_IMG_ROOTS);
//assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
//assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );


//
x1 = 0.000999998000008000;
x2 = -500.000999998000;
a = 2.0;
b = 1000.0;
c = -1.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );


//
x1 = 4.64575131106459;
x2 = -0.645751311064591;
a = 1.0;
b = -4.0;
c = -3.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );


//
x1 = 4.64575131106459;
x2 = -0.645751311064591;
a = 1.0;
b = -4.0;
c = -3.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );


//
x1 = 4.64575131106459;
x2 = -0.645751311064591;
a = 1.0;
b = -4.0;
c = -3.0;
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );




exit(0);
}
