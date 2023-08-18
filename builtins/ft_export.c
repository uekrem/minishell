/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:27:25 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 13:27:26 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_count(t_execute *execute)
{
	int	i;

	i = 0;
	while (execute)
	{
		i++;
		execute = execute->next;
	}
	if (i >= 2)
		return (1);
	else if (i == 1)
		return (-1);
	return (0);
}

void	ft_print_export(void)
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
	g_glbl.erorno = 0;
}

int	check_arg(char *str, char *status)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 65 && str[i] <= 90) && !(str[i] >= 97 && str[i] <= 122)
			&& str[i] != '_' && str[i] != 92 && str[i] != '=' && str[i]
			&& (i == 1 && !(str[i] >= 48 && str[i] <= 57)))
			flag = 1;
		if (str[i] == '=' && str[i - 1] == '+')
		{
			g_glbl.export_plus_flag = 1;
			flag = 0;
			break ;
		}
		i++;
	}
	if ((ft_isalpha(str[0]) || str[0] == '_') && flag == 0)
		return (0);
	printf("minishell: %s: '%s': not a valid indentifier\n", status, str);
	return (1);
}

void	ft_add_which(t_execute *execute)
{
	g_glbl.export_flag = 0;
	g_glbl.env_flag = 0;
	if (ft_strchr(execute->value, '=') == NULL)
	{
		ft_add_export(execute->value);
	}
	else
	{
		ft_add_export(execute->value);
		ft_add_env(execute->value);
	}
	g_glbl.erorno = 0;
}

void	ft_export(t_command *cmd)
{
	t_execute	*temp;

	temp = cmd->execute;
	g_glbl.export_plus_flag = 0;
	if (arg_count(temp) == -1)
		ft_print_export();
	else
	{
		temp = temp->next;
		while (temp)
		{
			if (check_arg(temp->value, "export"))
			{
				temp = temp->next;
				g_glbl.erorno = 1;
				continue ;
			}
			else
				ft_add_which(temp);
			temp = temp->next;
		}
	}
	fill_paths();
}
