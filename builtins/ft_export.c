#include "../minishell.h"

int	export_size(t_list *list)
{
	int	i;

	i = 0;
	while (list->export[i])
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

void	ft_print_export(t_list *list)
{
	int		i;
	char	**ag;

	i = 0;
	while (list->export[i])
	{
		ag = ft_split(list->export[i], '=');
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

void	ft_add_export(t_list *list, char *arg)
{
	int		i;
	char	**new_export;

	new_export = malloc(sizeof(char *) * (export_size(list) + 2));
	i = 0;
	while (list->export[i])
	{
		new_export[i] = ft_strdup(list->export[i]);
		i++;
	}
	new_export[i] = ft_strdup(arg);
	new_export[i + 1] = NULL;
	free_char(list->export);
	list->export = new_export;
	int j;

	j = 0;
	while (list->export[j])
	{
		printf("%s\n",list->export[j]);
		j++;
	}
}

void	ft_add_which(t_list *list, int i)
{
	if (ft_strchr(list[i].value, '=') == NULL)
		ft_add_export(list, list[i].value);

}

void	init_env(t_list *list)
{
	int	i;

	i = 0;
	while (list->env[i])
		i++;
	list->export = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (list->env[i])
	{
		list->export[i] = ft_strdup(list->env[i]);
		i++;
	}
	list->export[i] = NULL;
}

void	ft_export(t_list *list)
{
	int	i;

	i = 1;
	if (arg_count(list) == -1)
	{
		printf("Selam");
		ft_print_export(list);
	}
	else
	{
		while (list[i].value)
		{
			printf("nedennn\n");
			if (check_arg(list))
				continue ;
			ft_add_which(list, i);
			i++;
		}
	}
}
