#include "../minishell.h"

void	ft_env()
{
	int		i;
	char	**ag;

	i = 0;
	while (g_glbl.env[i])
	{
		ag = ft_split(g_glbl.env[i], '=');
		if (ag[1] == NULL)
			printf("%s=\"\"\n", ag[0]);
		else
			printf("%s=\"%s\"\n", ag[0], ag[1]);
		i++;
	}
}
