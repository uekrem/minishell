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
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	i = skip_flag(cmp->execute->next);
	if (i > 1)
		flag = 0;
	while (i--)
		cmp->execute = cmp->execute->next;
	while (cmp->execute)
	{
		if (!cmp->execute->value)
			break ;
		put_char(cmp->execute->value);
		if (cmp->execute->next)
			write(STDOUT_FILENO, " ", 1);
		cmp->execute = cmp->execute->next;
	}
	if (flag)
		write(STDOUT_FILENO, "\n", 1);
	g_glbl.erorno = 0;
}
