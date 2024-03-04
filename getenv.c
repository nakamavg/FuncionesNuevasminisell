#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *p;
	char *s;
	char *c;
	p = getenv("HOME");
	s = getenv("PATH");
	c = getenv("SHELL");
	printf("HOME = %s\n", p);
	printf("PATH = %s\n", s);
	printf("SHELL = %s\n", c);
	return 0;
}