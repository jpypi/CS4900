#include <stdlib.h>
#include <stdio.h>
#include "input.h"
#include "output.h"
#include "qsolve.h"


int main(int argc, char *argv[]) {
    double a,b,c;

    get_coeficient("Input a: ", &a);
    get_coeficient("Input b: ", &b);
    get_coeficient("Input c: ", &c);

    double root1, root2;
    int res = qsolve(a,b,c, &root1, &root2);

    char *output = NULL;

    if (res == QSOLVE_DOUBLE_ROOT) {
        output = single_root_str(root1, root2);
    } else if (res == QSOLVE_SINGLE_ROOT) {
        output = double_root_str(root1);
    } else {
        output = "Well, y' dun goof'd\n";
        printf(output);
    }

    return 0;
}
