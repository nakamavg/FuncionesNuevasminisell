#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *rl;
	while(1)
	{
    rl = readline("minishell: ");
    printf("%s\n", rl);
	}
    return (0);
}