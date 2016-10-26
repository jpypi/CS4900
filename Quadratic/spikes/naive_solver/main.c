#include <stdio.h>
#include <math.h>

// -b +- sqrt(pow(b, 2) - 4*a*c) / 2*a
// ax^2 + b*x + c
int solve(double a, double b, double c, double *root1, double *root2) {
    double b_sq = powf(b, 2);
    double four_a = 4 * a;
    double four_a_c = four_a * c;
    double descriminate_pre = b_sq - four_a_c;
    double descriminate = sqrtf(descriminate_pre);
    double two_a = 2 * a;
    double numerator_1 = -b + descriminate;
    double numerator_2 = -b - descriminate;
    *root1 = numerator_1 / two_a;
    *root2 = numerator_2 / two_a;

    return 0;
}

int
main(int argc, char *argv[]) {
    double r1, r2;
    solve(1.0, 2.0, 1.0, &r1, &r2);

    printf("Root 1: %g\n", r1);
    printf("Root 2: %g\n", r2);

    // TODO: Get input
    // TODO: Give output
    return 0;
}
