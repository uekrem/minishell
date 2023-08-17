/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actuation2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:39 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:38:52 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_count_ex(t_execute *execute)
{
	int	i;

	i = 0;
	while (execute)
	{
		i++;
		execute = execute->next;
	}
	return (i);
}

char	**get_arg_fill(t_execute *execute)
{
	char	**args;
	int		i;
	int		arg_count;

	i = 1;
	arg_count = arg_count_ex(execute);
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	args[0] = ft_strdup(execute->value);
	execute = execute->next;
	while (i < arg_count && execute)
	{
		args[i] = ft_strdup(execute->value);
		execute = execute->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
