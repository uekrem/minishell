#include "minishell.h"

int	ft_opr_which(char input)
{
	if (input == '|')
		return (1);
	if (input == '<')
		return (2);
	if (input == '>')
		return (3);
	return (0);
}

int	ft_strlen(char *input, int index)
{
	int	i;

	i = 0;
	while (input[index] && input[index] != ' ')
	{
		i++;
		index++;
	}
	return (i);
}

void	ft_couple_core(char	*input, int	*i)
{
	while (input[*i])
	{
		*i += 1;
		if (input[*i] == '"')
			break;
	}
}

int	ft_str_shred(char *input)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;

	while (input[i])
	{
		while (input[i] == ' ' && input[i])
			i++;
		if (input[i] == '"')
			ft_couple_core(input, &i);
		if (input[i])
			flag++;
		while (input[i] != ' ' && input[i])
			i++;
	}
	return (flag);
}