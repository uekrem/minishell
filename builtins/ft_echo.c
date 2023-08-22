/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:27:05 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/22 13:27:31 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		write(STDOUT_FILENO, &(input[i]), 1);
		i++;
	}
}

int	check_tire_en(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '-')
			flag++;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if ((str[i] != '-' && str[i] != 'n') || flag != 1)
			return (0);
		i++;
	}
	return (1);
}

int	skip_flag(t_execute *str)
{
	int	i;

	i = 1;
	while (str)
	{
		if (!ft_strncmp(str->value, "-n", ft_strlenn("-n"))
			&& check_tire_en(str->value))
		{
			i++;
			str = str->next;
		}
		else
			break ;
	}
	return (i);
}

void	ft_echo(t_command *cmp)
{
	int			i;
	int			flag;
	t_execute	*temp;

	ft_echo_defini(&i, &flag);
	temp = cmp->execute;
	i = skip_flag(temp->next);
	temp = ft_double_n(&i, &flag, temp);
	while (temp)
	{
		if (!temp->value)
			break ;
		if (ft_strlenn(temp->value) == 0)
		{
			temp = temp->next;
			continue ;
		}
		put_char(temp->value);
		if (temp->next)
			write(STDOUT_FILENO, " ", 1);
		temp = temp->next;
	}
	ft_check_zero(flag);
}
