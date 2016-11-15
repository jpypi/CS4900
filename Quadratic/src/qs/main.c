#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "input.h"
#include "output.h"
#include "qsolve.h"
#include "validate.h"


int main(int argc, char *argv[]) {
    double a = 0.0, b = 0.0, c = 0.0;

    get_coeficient("Input a: ", &a);

    // TODO: THIS IS TERRIBAD FIX IT
    if (daeq(a, 0.0, FLT_EPSILON*2)) {
        printf("This equation is not processable by this program. Please choose\
 a > 0.\n");
        return 1;
    }

    get_coeficient("Input b: ", &b);
    get_coeficient("Input c: ", &c);

    double root1 = 0.0, root2 = 0.0;
    int res = qsolve(a, b, c, &root1, &root2);

    char *output = NULL;

    if (res == QSOLVE_DOUBLE_ROOT) {
        output = single_root_str(root1, root2);
    } else if (res == QSOLVE_SINGLE_ROOT) {
        output = double_root_str(root1);
    } else {
        output = "Well, y' dun goof'd\n";
        printf("%s", output);
    }

    return 0;
}
