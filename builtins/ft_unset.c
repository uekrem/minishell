#include "../minishell.h"

int	ft_strncmp2(const char *s1, const char *s2, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (s1[i] != s2[i])
			return (0);
	}
	return (1);
}

void del_export(t_list *list, int x)
{
	int i = 0;
	int j;
	x++;
	while (g_glbl.export[i] != NULL && list[x].type == ARG)
	{
		if (ft_strncmp2(g_glbl.export[i], list[x].value, ft_strlen(list[x].value, 0, '=')))
		{
			j = i;
			free(g_glbl.export[j]);
			while (g_glbl.export[j] != NULL)
			{
				g_glbl.export[j] = g_glbl.export[j + 1];
				j++;
			}
			x++;
			i = -1;
		}
		i++;
	}
}

void del_env(t_list *list, int x)
{
	int i = 0;
	int j;
	x++;
	while (g_glbl.env[i] != NULL && list[x].type == ARG)
	{
		if (ft_strncmp2(g_glbl.env[i], list[x].value, ft_strlen(list[x].value, 0, '=')))
		{
			j = i;
			free(g_glbl.env[j]);
			while (g_glbl.env[j] != NULL)
			{
				g_glbl.env[j] = g_glbl.env[j + 1];
				j++;
			}
			x++;
			i = -1;
		}
		i++;
	}
}

void	ft_unset(t_list *list, int *i)
{
	del_export(list, *i);
	//del_env(list, *i);
}
