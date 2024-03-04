# include <readline/readline.h>
# include <readline/history.h>

int main()
{
	char *rl;
	while(1)
	{
		rl = readline("minishell: ");
		rl_replace_line("", 0);
	}
	return (0);
}