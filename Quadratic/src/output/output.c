#include <stdio.h>
#include <float.h>


char * double_root_str(double root) {
    printf("Double root.\n");
    printf("Root: %.*le\n", FLT_DIG, root);
    return NULL;
}

char * single_root_str(double root1, double root2) {
    double first = root1, second = root2;
    if (root2 < root1) {
        first = root2;
        second = root1;
    }

    printf("Root 1: %.*le\nRoot 2: %.*le\n", FLT_DIG, first, FLT_DIG, second);
    return NULL;
}
