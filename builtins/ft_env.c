#include "../minishell.h"


void	ft_env(t_command *cmd)
{
	int		i;
	char	**ag;

	i = 0;
	if (arg_count(cmd->execute) == 0 || arg_count(cmd->execute) == 1)
	{
		printf("env: %s: No such file or directory", cmd->execute->value);
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
