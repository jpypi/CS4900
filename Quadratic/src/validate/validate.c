#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * daeq: Double absolute equals
 */
int daeq(double a, double b, double aerror) {
    return (fabs(a-b) < aerror);
}

/*
 * Validates that the given string is
 * If input provided is anything other than a double (non numerical chars or
 * even an empty string) then abort.
 */
int validate_double_input(char *string) {
    double res = 0;
    int err = sscanf(string, "%le", &res);

    if (err <= 0){
		printf("Input provided is not a numerical value. Aborting\n");
		exit(-1);
    }

    return err;
}
