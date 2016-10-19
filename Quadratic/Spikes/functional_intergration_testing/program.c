

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h> //for testing strings
//======================


int main(int argc, char const *argv[])
{
	FILE *f;
	f = fopen("output.out", "w+");

	int value;


	value = 0;
	fprintf(f, "%d\n", value);


	value = 10;
	fprintf(f, "%d\n", value);


	char* str = "TESTING";
	fprintf(f, "%s", str);


	fclose(f);


	return 0;
}