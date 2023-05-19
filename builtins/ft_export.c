#include "../minishell.h"

int	export_size()
{
	int	i;

	i = 0;
	while (g_glbl.export[i])
		i++;
	return (i);
}

void	free_char(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void	ft_print_export()
{
	int		i;
	char	**ag;

	i = 0;
	while (g_glbl.export[i])
	{
		ag = ft_split(g_glbl.export[i], '=');
		if (ag[1] == NULL)
			printf("declare -x %s=\"\"\n", ag[0]);
		else
			printf("declare -x %s=\"%s\"\n", ag[0], ag[1]);
		i++;
	}
}

int	check_arg(t_list *list)
{
	if (ft_isalpha(list[1].value[0]) || list[1].value[0] == '_')
		return (0);
	printf("minishell: export: '%s': not a valid indentifier", list[1].value);
	return (1);
}

void	ft_add_export(char *arg)
{
	int		i;
	char	**new_export;

	new_export = malloc(sizeof(char *) * (export_size() + 2));
	i = 0;
	while (g_glbl.export[i])
	{
		new_export[i] = ft_strdup(g_glbl.export[i]);
		i++;
	}
	new_export[i] = ft_strdup(arg);
	new_export[i + 1] = NULL;
	free_char(g_glbl.export);
	g_glbl.export = new_export;
}

void	ft_add_env(char *arg)
{
	int		i;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (export_size() + 2));
	i = 0;
	while (g_glbl.env[i])
	{
		new_env[i] = ft_strdup(g_glbl.env[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	free_char(g_glbl.env);
	g_glbl.env = new_env;
}

void	ft_add_which(t_list *list, int i)
{
	if (ft_strchr(list[i].value, '=') == NULL)
	{
		ft_add_export(list[i].value);
	}
	else
	{
		ft_add_export(list[i].value);
		ft_add_env(list[i].value);
	}

}

void	ft_export(t_list *list)
{
	int	i;

	i = 1;
	if (arg_count(list) == -1)
		ft_print_export();
	else
	{
		while (list[i].type != END)
		{
			if (list[i].type == PIPE)
				exit (0);
			if (check_arg(list))
				continue ;
			ft_add_which(list, i);
			i++;
		}
	}
}
