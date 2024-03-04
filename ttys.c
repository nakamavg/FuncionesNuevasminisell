#include <stdio.h>
#include <unistd.h>

int main ()
{
	int prueba = isatty(1);
	printf("isatty(0) = %d\n", prueba);
}