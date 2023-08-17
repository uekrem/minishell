/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:27:17 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:41:54 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_fonk(char *a, size_t i, char const *s2)
{
	size_t	j;
	size_t	len;

	len = ft_strlenn(s2);
	j = 0;
	while (j < len)
	{
		a[i] = s2[j];
		i++;
		j++;
	}
	a[i] = '\0';
	return (a);
}

char	*ft_export_join(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*a;

	len1 = ft_strlenn(s1);
	len2 = ft_strlenn(s2);
	i = 0;
	a = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!a)
		return (NULL);
	while (i < len1)
	{
		a[i] = s1[i];
		i++;
	}
	a = ft_fonk(a, i, s2);
	free(s1);
	return (a);
}
