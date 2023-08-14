#include "../minishell.h"

void	ft_env(t_execute *execute)
{
	int		i;
	char	**ag;

	i = 0;
	if (arg_count(execute) == 0 || arg_count(execute) == 1)
	{
		printf("env: %s: No such file or directory\n", execute->next->value);
		g_glbl.erorno = 127;
		return ;
	}
	while (g_glbl.env[i])
	{
		ag = ft_split(g_glbl.env[i], '=');
		if (ag[1] == NULL)
			printf("%s=\"\"\n", ag[0]);
		else
			printf("%s=\"%s\"\n", ag[0], ag[1]);
		i++;
		free_char(ag);
	}
	fill_paths();
	g_glbl.erorno = 0;
}
