/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:27:08 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/22 11:32:29 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '=')
			return (-1);
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_env(t_execute *execute, int *flag)
{
	if (arg_count(execute) == 0 || arg_count(execute) == 1)
	{
		if (arg_count(execute) == 1 && check_equal(execute->next->value) != 0)
		{
			if (check_equal(execute->next->value) == 1)
				*flag = 1;
			else if (check_equal(execute->next->value) == -1)
			{
				g_glbl.erorno = 1;
				printf("env: setenv %s: Invalid argument\n",
					execute->next->value);
				return (1);
			}
		}
		else
		{
			printf("env: %s: No such file or directory\n",
				execute->next->value);
			g_glbl.erorno = 127;
			return (1);
		}
	}
	return (0);
}

void	ft_env(t_execute *execute)
{
	int		i;
	char	**ag;
	int		flag;

	i = 0;
	flag = 0;
	if (check_env(execute, &flag))
		return ;
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
	if (flag == 1)
		printf("%s\n", execute->next->value);
	fill_paths();
	g_glbl.erorno = 0;
}
