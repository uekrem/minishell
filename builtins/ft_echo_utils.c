/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:24:04 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/22 13:27:14 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_execute	*ft_double_n(int *i, int *flag, t_execute *temp)
{
	if (*i > 1)
		*flag = 0;
	while ((*i)--)
		temp = temp->next;
	return (temp);
}

void	ft_check_zero(int flag)
{
	if (flag)
		write(STDOUT_FILENO, "\n", 1);
	g_glbl.erorno = 0;
}

void	ft_echo_defini(int *i, int *flag)
{
	*i = 1;
	*flag = 1;
}
