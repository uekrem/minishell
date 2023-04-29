/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:05:22 by uguyildi          #+#    #+#             */
/*   Updated: 2022/10/14 23:06:48 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_listt	*ft_lstnew(void *content)
{
	t_listt	*root;

	root = (t_listt *)malloc(sizeof(t_listt));
	if (!root)
		return (0);
	root->content = content;
	root->next = NULL;
	return (root);
}
