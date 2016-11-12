#include <stdlib.h>
#include <stdio.h>
#include "input.h"
#include "output.h"
#include "qsolve.h"

int get_coeficient(char *prompt, double *ret_value){
    char *buffer = NULL;

    printf(prompt);

    buffer = read_input(stdin);
    *ret_value = parse_double(buffer);
    free(buffer);

    return 0;
}


int main(int argc, char *argv[]) {
    double a,b,c;

    get_coeficient("Input a: ", &a);
    get_coeficient("Input b: ", &b);
    get_coeficient("Input c: ", &c);

    printf("%le %le %le\n", a, b, c);

    double root1, root2;
    int res = qsolve(a,b,c, &root1, &root2);

    char *output = NULL;

    if (res == QSOLVE_DOUBLE_ROOT) {
        printf("Wee");
    } else if (res == QSOLVE_SINGLE_ROOT) {
        printf("Weewooo");
    }

    //printf(output);

    return 0;
}
