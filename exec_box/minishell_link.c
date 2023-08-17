/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:16 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:38:22 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_link	*ft_lstlast(t_link *lst)
{
	while (lst != NULL && lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_link **lst, t_link *new)
{
	t_link	*position;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		position = ft_lstlast(*lst);
		position->next = new;
	}
}

t_link	*ft_lstnew(t_list *list)
{
	t_link	*root;

	root = (t_link *)malloc(sizeof(t_link));
	if (!root)
		return (0);
	root->value = list->value;
	root->type = list->type;
	root->list_len = list->list_len;
	root->flag = list->flag;
	root->next = NULL;
	return (root);
}

t_link	*ft_copy_list(t_list *list)
{
	int		i;
	t_link	*link_block;
	t_link	*link_ls;

	i = 0;
	link_ls = NULL;
	while (i < list->list_len)
	{
		link_block = ft_lstnew(&list[i]);
		if (i == 0)
			link_block->prev = NULL;
		else
			link_block->prev = ft_lstlast(link_ls);
		ft_lstadd_back(&link_ls, link_block);
		i++;
	}
	if (!link_ls)
		return (0);
	return (link_ls);
}
