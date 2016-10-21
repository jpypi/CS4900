#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

//prints initial string and what it is parsed as
void p(const char *s)
{
	printf("input: %12s Parsed: %lf\n", s, strtod(s, NULL));
}

//demos strtod on different inputs (valid and invalid)
void main() 
{
	p("0.2");
	p("1.2e4");
	p("12e4");
	p("12.0e4");
	p("0.120e4");
	p("1E6");
	p("ha!");
	p("nan");
	p("inf");
	p("-inf");
	p("-nan");
	p("a120");
	p("0x");
	p("0x10");
	p("010");
}
