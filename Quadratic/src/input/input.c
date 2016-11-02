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
char * read_abc(FILE * file) {
    char *buffer = malloc(ABC_IN_BUFFER_SIZE);
    fgets(buffer, ABC_IN_BUFFER_SIZE, file);

    return buffer;
}
