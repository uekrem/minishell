/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:27:11 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/22 11:32:58 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isnumber_with_sign(char *arg)
{
	while (*arg)
	{
		if ((*arg >= '0' && *arg <= '9') || *arg == '+' || *arg == '-')
			arg++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(t_command *cmd)
{
	if (arg_count(cmd->execute) == -1)
	{
		if (g_glbl.cmd_count == 1)
			printf("exit\n");
		exit(errno);
	}
	else
	{
		if (ft_isnumber_with_sign(cmd->execute->next->value))
		{
			if (arg_count(cmd->execute) == 1)
			{
				write(2, "exit\nminishell: exit: too many arguments\n", 41);
				errno = 1;
				return ;
			}
			printf("exit\n");
			exit(ft_atoi(cmd->execute->next->value) % 256);
		}
		write(2, "exit\nminishell: exit: numeric argument required\n", 48);
		exit(-1 % 256);
	}
}
