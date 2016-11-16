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
int	count;	 // number of times the mock object qsolve_sqrt(0 is called.
double	x;	 // arguement passed to qsolve_sqrt()
char	str[100];// messsaage for assert() 
double	d;	 // scratch for discriminate
double	sqrtd;	 // scratch for sqrt(d) 


// initialize the unit testing framework
cunit_init();

// A "good" unit test, need to allow for round off!
// qsolve_roots() passes this one. ;-)
// This allows about one base 10 least significant digit of error
// (x - x1)*(x - x2) = 0

//case 1
//causes catastrophic cancellation
x1 = -0.00856795142385192;
x2 = -3676.49143204858;
a = 2.0;
b = 7353.0;
c = 63.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, FLT_MIN);
assert_feqrerr("x2", r2, x2, FLT_MIN);
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);


//case 2
x1 = -1.0;
x2 = -1.0;
a = 1.0;
b = 2.0;
c = 1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,QSOLVE_SINGLE_ROOT);
assert_feqrerr("x1", r1, x1, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_fmacheps );


//case 3
x1 = -100.0;
x2 = 0.01;
a = 100.0;
b = 9999.0;
c = 100.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x2, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x1, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 4
//good
x1 = -1.0;
x2 = -0.20;
a = 5.0;
b = 6.0;
c = 1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x2, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x1, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 5
//good
x1 = -4.56155281280883;
x2 = -0.438447187191170;
a = 1.0;
b = 5.0;
c = 2.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x2, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x1, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 6
//good
x1 = 4.64575131106459;
x2 = -0.645751311064591;
a = 1.0;
b = -4.0;
c = -3.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 7
//good
x1 = 2.0;
x2 = -2.0;
a = 1.0;
b = 0.0;
c = -4.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 8
//good
//x1 = 4.64575131106459;
//x2 = -0.645751311064591;
a = -1.0;
b = -1.0;
c = -1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,QSOLVE_IMG_ROOTS);
//assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
//assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 9
x1 = 0.000999998000008000;
x2 = -500.000999998000;
a = 2.0;
b = 1000.0;
c = -1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 10
//bad
x1 = -0.229249;
x2 = -1.36073;
a = 5.190;
b = 8.252;
c = 1.619;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 11
//good
x1 = -0.618033988749895;
x2 = 1.61803398874989;
a = -1.0;
b = 1.0;
c = 1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 12
//x1 = 4.64575131106459;
//x2 = -0.645751311064591;
a = 1.0;
b = -1.0;
c = 1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,QSOLVE_IMG_ROOTS);
//assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
//assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 13
//good
x1 = 0.618033988749895;
x2 = -1.61803398874989;
a = 1.0;
b = 1.0;
c = -1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 14
//good
x1 = -1.61803398874989;
x2 = 0.618033988749895;
a = -1.0;
b = -1.0;
c = 1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 15
//good
//x1 = -0.618033988749895;
//x2 = 1.61803398874989;
a = -1.0;
b = 1.0;
c = -1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,QSOLVE_IMG_ROOTS);
//assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
//assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 16
//good
x1 = 1.61803398874989;
x2 = -0.618033988749895;
a = 1.0;
b = -1.0;
c = -1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 17
//good
//x1 = 1.61803398874989;
//x2 = -0.618033988749895;
a = -1.0;
b = -1.0;
c = -1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,QSOLVE_IMG_ROOTS);
//assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
//assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 18
//good
//x1 = ;
//x2 = ;
a = 1000000000.0;
b = 1.0;
c = 1.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,QSOLVE_IMG_ROOTS);
//assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
//assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 19
//bad
x1 = -1.000000000000000001000000e-9;
x2 = -9.99999999999999999000000e8;
a = 1.0;
b = 1000000000.0;
c = 1.0;

d = b*b - 4.0*a*c;
printf("%.12e\n", d);
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,2);
assert_feqrerr("x1", r1, x1, 10.0*cunit_fmacheps );
assert_feqrerr("x2", r2, x2, 10.0*cunit_fmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);



//case 20
//good
//x1 = 1.61803398874989;
//x2 = -0.618033988749895;
a = 1.0;
b = 1.0;
c = 1000000000.0;

d = b*b - 4.0*a*c;
sqrtd = sqrt(d);

//
mock_setup_qsolve_sqrt( d, sqrtd, cunit_dmacheps*2.0*d);
//
ret = qsolve(a,b,c, &r1, &r2);
assert_eq("ret",ret,QSOLVE_IMG_ROOTS);
//assert_feqrerr("x1", r1, x1, 10.0*cunit_dmacheps );
//assert_feqrerr("x2", r2, x2, 10.0*cunit_dmacheps );
//
ret= mock_check_qsolve_sqrt( &count, &x);
snprintf(str, 99, "count ret = %d x =%20.61e", count, x);
assert_eq(str, ret , 1);






exit(0);
}
