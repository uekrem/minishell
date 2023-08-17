/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_adding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:27:14 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 13:27:15 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_plus_not_same(char **new_export, char *arg, int *i)
{
	int		j;
	int		x;
	char	*new;

	new = malloc(sizeof(char) * ft_strlenn(arg) + 1);
	j = 0;
	x = 0;
	while (arg[j])
	{
		if (arg[j] == '+')
			j++;
		new[x++] = arg[j];
		j++;
	}
	new[x] = '\0';
	new_export[*i] = ft_strdup(new);
	free(new);
}

void	add_plus(char **env, char **arg, char **new_env, int *i)
{
	if (g_glbl.export_plus_flag == 1 && (ft_strncmp(env[0], arg[0],
				ft_strlen(arg[0], 0, '+')) == 0))
	{
		if (arg[1] == NULL)
		{
			if (env[1] == NULL)
				new_env[*i] = ft_export_join(new_env[*i], "=");
			g_glbl.export_flag = 1;
			g_glbl.env_flag = 1;
			return ;
		}
		if (env[1] == NULL)
			new_env[*i] = ft_export_join(new_env[*i], "=");
		new_env[*i] = ft_export_join(new_env[*i], arg[1]);
		g_glbl.export_flag = 1;
		g_glbl.env_flag = 1;
	}
}

void	equal(char **new_export, int *i, char *arg, char *name)
{
	char	**double_env;
	char	**double_arg;

	double_env = ft_split(new_export[*i], '=');
	double_arg = ft_split(arg, '=');
	add_plus(double_env, double_arg, new_export, i);
	if (which_commant(double_env[0], double_arg[0]))
	{
		free(new_export[*i]);
		new_export[*i] = ft_strdup(arg);
		if (which_commant(name, "export"))
			g_glbl.export_flag = 1;
		else if (which_commant(name, "env"))
			g_glbl.env_flag = 1;
	}
	free_char(double_env);
	free_char(double_arg);
}

void	ft_adding_env(char **new_env, char *arg)
{
	int	i;

	i = -1;
	while (g_glbl.env[++i])
	{
		new_env[i] = ft_strdup(g_glbl.env[i]);
		equal(new_env, &i, arg, "env");
	}
	if (g_glbl.env_flag == 0)
	{
		if (g_glbl.export_plus_flag == 1)
			add_plus_not_same(new_env, arg, &i);
		else
			new_env[i] = ft_strdup(arg);
		new_env[i + 1] = NULL;
	}
	else
		new_env[i] = NULL;
	free_char(g_glbl.env);
	g_glbl.env = new_env;
}

void	ft_adding_export(char **new_export, char *arg)
{
	int	i;

	i = -1;
	while (g_glbl.export[++i])
	{
		new_export[i] = ft_strdup(g_glbl.export[i]);
		equal(new_export, &i, arg, "export");
	}
	if (g_glbl.export_flag == 0)
	{
		if (g_glbl.export_plus_flag == 1)
			add_plus_not_same(new_export, arg, &i);
		else
			new_export[i] = ft_strdup(arg);
		new_export[i + 1] = NULL;
	}
	else
		new_export[i] = NULL;
	free_char(g_glbl.export);
	g_glbl.export = new_export;
}
