#include <stdio.h>
#include <stdlib.h>


#define ABC_IN_BUFFER_SIZE 80


/*
 */
int parse_abc(char *string, float *a, float *b, float *c) {
    sscanf(string, "%f %f %f", a, b, c);
    return 0;
}

/*
 */
double parse_double(char *string) {
    double res = 0;
    sscanf(string, "%le", &res);
    return res;
}

/*
 */
char * read_input(FILE * file) {
    char *buffer = malloc(ABC_IN_BUFFER_SIZE);
    fgets(buffer, ABC_IN_BUFFER_SIZE, file);

    return buffer;
}

/*
 */
int get_coeficient(char *prompt, double *ret_value){
    char *buffer = NULL;

    printf(prompt);

    buffer = read_input(stdin);
    *ret_value = parse_double(buffer);
    free(buffer);

    return 0;
}
