#include "../minishell.h"

void	ft_unset(t_list *list)
{
	int i;

	i = 0;
	char **ag;
	(void)list;
	while (g_glbl.env[i])
	{
		ag = ft_split(g_glbl.env[i], '=');
		i++;
	}

	i = 1;
	
}
