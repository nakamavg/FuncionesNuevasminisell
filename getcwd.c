#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	char *pwd;
 	pwd =  getcwd(NULL,0);
    printf("%s\n", pwd);
    return (0);
}