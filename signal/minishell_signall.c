/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:58 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:04:37 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_d(t_glbl *glbl)
{
	if (!glbl->input)
	{
		printf("\nexit\n");
		free_execute(glbl);
		exit(0);
	}
}
