/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:37:36 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:37:28 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_radi(t_radira *radi)
{
	t_radira	*temp;

	if (!radi)
		return ;
	while (radi)
	{
		temp = radi->next;
		free(radi);
		radi = temp;
	}
	free(radi);
}

void	ft_free_exec(t_execute *exec)
{
	t_execute	*temp;

	if (!exec)
		return ;
	while (exec)
	{
		temp = exec->next;
		free(exec);
		exec = temp;
	}
	free(exec);
}
