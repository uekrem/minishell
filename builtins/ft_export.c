#include "../minishell.h"

int	arg_count(t_execute *execute)
{
	int			i;

	i = 0;
	while (execute)
	{
		i++;
		execute = execute->next;
	}
	if (i > 2)
		return (1);
	else if (i == 1)
		return (-1);
	return (0);
}

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
int equal(char *env, char *arg)
{
	char **double_env;
	char **double_arg;

	double_env = ft_split(env, '=');
	double_arg = ft_split(arg, '=');

	if (which_commant(double_env[0], double_arg[0]))
	{
		//printf("%s\n", double_env[0]);
		return 1;
	}
	free_char(double_env);
	free_char(double_arg);
	return 0;
}
void	ft_print_export()
{
	int		i;
	char	**ag;

	i = 0;
	while (g_glbl.export[i])
	{
		ag = ft_split(g_glbl.export[i], '=');
		if (ag[1] == NULL && ft_strchr(g_glbl.export[i], '='))
			printf("declare -x %s=\"\"\n", ag[0]);
		else if (ag[1] == NULL)
			printf("declare -x %s\n", ag[0]);
		else
			printf("declare -x %s=\"%s\"\n", ag[0], ag[1]);
		i++;
		free_char(ag);
	}
}

int	check_arg(char *str, char *status)
{
	if (ft_isalpha(str[0]) || str[0] == '_')
		return (0);
	printf("minishell: %s: '%s': not a valid indentifier\n", status, str);
	return (1);
}

void	ft_add_export(char *arg)
{
	int		i;
	int		flag;
	char	**new_export;

	new_export = malloc(sizeof(char *) * (export_size() + 2));
	i = 0;
	flag = 0;
	while (g_glbl.export[i])
	{
		new_export[i] = ft_strdup(g_glbl.export[i]);
		if (equal(new_export[i], arg))
		{
			new_export[i] = ft_strdup(arg);
			flag = 1;
		}
		i++;
	}
	if(flag == 0)
	{
		new_export[i] = ft_strdup(arg);
		new_export[i + 1] = NULL;
	}
	else
		new_export[i] = NULL;
	free_char(g_glbl.export);
	g_glbl.export = new_export;
	//free_char(new_export);
}

void	ft_add_env(char *arg)
{
	int		i;
	int		flag;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (export_size() + 2));
	i = 0;
	flag = 0;
	while (g_glbl.env[i])
	{
		new_env[i] = ft_strdup(g_glbl.env[i]);
		if (equal(new_env[i], arg))
		{
			new_env[i] = ft_strdup(arg);
			flag = 1;
		}
		i++;
	}
	if (flag == 0)
	{
		new_env[i] = ft_strdup(arg);
		new_env[i + 1] = NULL;
	}
	else
		new_env[i] = NULL;
	free_char(g_glbl.env);
	g_glbl.env = new_env;
	//free_char(new_env);
}

void	ft_add_which(t_execute *execute)
{
	if (ft_strchr(execute->value, '=') == NULL)
	{
		ft_add_export(execute->value);
	}
	else
	{
		ft_add_export(execute->value);
		ft_add_env(execute->value);
	}

}

void	ft_export(t_command *cmd)
{
	if (arg_count(cmd->execute) == -1)
		ft_print_export();
	else
	{
		cmd->execute = cmd->execute->next;
		while (cmd->execute)
		{
			if (check_arg(cmd->execute->value, "export"))
			{
				cmd->execute = cmd->execute->next;
				g_glbl.erorno = 1;
				continue;
			}
			else
				ft_add_which(cmd->execute);
			cmd->execute = cmd->execute->next;
		}
	}
}
