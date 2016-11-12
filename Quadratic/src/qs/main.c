#include <stdio.h>
#include "input.h"
#include "output.h"
#include "qsolve.h"


int main(int argc, char *argv[]) {
    char *buffer = NULL;
    double a,b,c;

    printf("Input a:");
    buffer = read_input(stdin);
    a = parse_double(buffer);
    free(buffer);

    printf("Input b:");
    buffer = read_input(stdin);
    b = parse_double(buffer);
    free(buffer);

    printf("Input c:");
    buffer = read_input(stdin);
    c = parse_double(buffer);
    free(buffer);

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
