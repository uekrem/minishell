/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_radi_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:21 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 13:28:22 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_radira	*lst_last_redirect(t_radira *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	lst_add_back_redirect(t_radira **lst, t_radira *new_node)
{
	t_radira	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last_redirect(*lst);
			tmp->next = new_node;
		}
	}
}

t_radira	*lst_new_elem_redirect(enum e_token type, char *value)
{
	t_radira	*new_elem;

	new_elem = (t_radira *)ft_calloc(sizeof(t_radira), 1);
	if (!new_elem)
		return (0);
	new_elem->type = type;
	new_elem->value = value;
	new_elem->next = 0;
	return (new_elem);
}

t_radira	*fill_redirect(t_link *link, t_radira **redirects)
{
	t_radira	*new_redirect;

	if (link->type == OUTPUT_R)
	{
		new_redirect = lst_new_elem_redirect(IN_FILE, link->next->value);
		lst_add_back_redirect(redirects, new_redirect);
	}
	else if (link->type == INPUT_R)
	{
		new_redirect = lst_new_elem_redirect(OUT_FILE, link->next->value);
		lst_add_back_redirect(redirects, new_redirect);
	}
	else if (link->type == D_INPUT_R)
	{
		new_redirect = lst_new_elem_redirect(D_INPUT_R, link->next->value);
		lst_add_back_redirect(redirects, new_redirect);
	}
	else if (link->type == D_OUTPUT_R)
	{
		new_redirect = lst_new_elem_redirect(D_OUTPUT_R, link->next->value);
		lst_add_back_redirect(redirects, new_redirect);
	}
	return (*redirects);
}
