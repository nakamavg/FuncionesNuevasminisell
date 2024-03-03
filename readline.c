#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
int main(void)
{
    char *rl;
    while(1)
    {
        rl = readline("minishell: ");
        if (rl && *rl) {
            add_history(rl);  
        }
        printf("%s\n", rl);
        free(rl); 
    }
    return (0);
}