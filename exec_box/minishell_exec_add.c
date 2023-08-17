/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:13 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:38:17 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prev_type(enum e_token type)
{
	if (type == INPUT_R || type == OUTPUT_R || type == D_INPUT_R
		|| type == D_OUTPUT_R)
		return (1);
	return (0);
}

t_execute	*lst_last_execute(t_execute *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	lst_add_back_execute(t_execute **lst, t_execute *new_node)
{
	t_execute	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last_execute(*lst);
			tmp->next = new_node;
		}
	}
}

t_execute	*lst_new_elem_execute(char *value)
{
	t_execute	*new_elem;

	new_elem = (t_execute *)calloc(sizeof(t_execute), 1);
	if (!new_elem)
		return (0);
	new_elem->value = value;
	new_elem->next = 0;
	return (new_elem);
}

t_execute	*fill_execute(t_link *link, t_execute **execute)
{
	t_execute	*new_execute;

	if (link->type == ARG && link->prev == 0)
	{
		new_execute = lst_new_elem_execute(link->value);
		lst_add_back_execute(execute, new_execute);
	}
	else if (link->type == ARG && prev_type(link->prev->type) == 0)
	{
		new_execute = lst_new_elem_execute(link->value);
		lst_add_back_execute(execute, new_execute);
	}
	return (*execute);
}
