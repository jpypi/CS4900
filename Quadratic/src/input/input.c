#include <stdio.h>
#include <stdlib.h>


#define ABC_IN_BUFFER_SIZE 80


/*
 * Parses a character array (string) for three floating point (single precision)
 * values.
 * Always returns 0
 */
int parse_abc(char *string, float *a, float *b, float *c) {
#ifdef LOG_FILE
    fprintf(LOG_FILE, "parse_abc: string: %s a:%le b:%le c:%le\n", string, a, b, c);
#endif
    sscanf(string, "%f %f %f", a, b, c);
    return 0;
}


/*
 * Parses a double from a character array (i.e. string)
 */
double parse_double(char *string) {
#ifdef LOG_FILE
    fprintf(LOG_FILE, "parse_double: string:%s\n", string);
#endif
    double res = 0;
    sscanf(string, "%le", &res);
    return res;
}


/*
 * Reads from a FILE into a buffer of ABC_IN_BUFFER_SIZE that gets mallocd.
 * The programmer should free this buffer when they are done with it.
 */
char * read_input(FILE * file) {
    char *buffer = malloc(ABC_IN_BUFFER_SIZE);
    fgets(buffer, ABC_IN_BUFFER_SIZE, file);

    return buffer;
}


/*
 * Wrapper function to helpfully output a prompt, read a double in from stdin
 * as ascii and write the double at the pointer: ret_value.
 */
int get_coeficient(char *prompt, double *ret_value){
#ifdef LOG_FILE
    fprintf(LOG_FILE, "get_coeficient: prompt:%s ret_value:%p\n", prompt, ret_value);
#endif
    char *buffer = NULL;

    printf(prompt);

    buffer = read_input(stdin);
    *ret_value = parse_double(buffer);
    free(buffer);

    return 0;
}
