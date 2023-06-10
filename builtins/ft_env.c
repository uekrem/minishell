#include "../minishell.h"


void	ft_env(t_list	*list)
{
	int		i;
	char	**ag;

	i = 0;
	if (arg_count(list) == 0 || arg_count(list) == 1)
	{
		printf("env: %s: No such file or directory", list[1].value);
		exit(0);
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
}
