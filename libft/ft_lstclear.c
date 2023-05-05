/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:01:49 by uguyildi          #+#    #+#             */
/*   Updated: 2022/10/14 23:01:53 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_listt **lst, void (*del)(void *))
{
	t_listt	*root;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		root = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = root;
	}
}
