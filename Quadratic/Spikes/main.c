#include <stdio.h>
#include <math.h>

// -b +- sqrt(pow(b, 2) - 4*a*c) / 2*a
void
solve(float a, float b, float c) {
    float b_sq = powf(b, 2);
    float intermediate = 4*a*c;
    float descriminate = sqrtf(b_sq - intermediate);
    float root1 = (-b + descriminate) / 2*a;
    float root2 = (-b - descriminate) / 2*a;

    printf("Root 1: %f\n", root1);
    printf("Root 2: %f\n", root2);
}

int
main(int argc, char *argv[]) {
    solve(1.0, 2.0, 4.0);
    // TODO: Get input
    // TODO: Give output
    return 0;
}
