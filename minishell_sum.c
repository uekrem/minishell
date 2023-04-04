#include "minishell.h"

int	ft_opr_pair(char *input)
{
	int			i;
	int			arg;
	int			arg2;
	static int	flag;
	static int	flag2;

	i = -1;
	arg = 1;
	arg2 = 1;
	while (input[++i])
	{
		if (input[i] == '"' && arg2 == 1)
		{
			if (arg == 0)
				arg = 1;
			else
				arg = 0;
			flag++;
		}
		else if (input[i] == 39 && arg == 1)
		{
			if (arg2 == 0)
				arg2 = 1;
			else
				arg2 = 0;
			flag2++;
		}
	}
	if (flag % 2 == 0 && flag2 % 2 == 0)
		return (0);
	printf("Missing double or single quotes");
	return (1);
}

void	ft_couple_core(char *input, int *i, char c)
{
	while (input[*i])
	{
		*i += 1;
		if (input[*i] == c)
			break ;
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
		if (input[i] == '"' || input[i] == 39)
			ft_couple_core(input, &i, input[i]);
		if (input[i])
			flag++;
		while (input[i] != ' ' && input[i])
			i++;
	}
	return (flag);
}

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

int	ft_strlen(char *input, int index, char c)
{
	int i;

	i = 0;
	while (input[index] && input[index] != c)
	{
		i++;
		index++;
	}
	return (i);
}

char	*ft_how_far(char *str, int *j)
{
	int		counter;
	int		value;
	char	*search;

	value = 0;
	counter = 0;
	while (1)
	{
		if (((str[*j] >= 32 && str[*j] <= 47) 
			|| (str[*j] >= 58 && str[*j] <= 64)
			|| (str[*j] >= 91 && str[*j] <= 96)
			|| (str[*j] >= 123 && str[*j] <= 126)) 
			&& str[*j])
			break;
		value++;
		*j += 1;
	}
	search = malloc(sizeof(char) * (value + 1));
	search[value - 1] = '\0';
	while (value > 0)
	{
		search[counter] = str[*j - value];
		counter++;
		value--;
	}
	return (search);
}

int	ft_restrlen(t_list *list, char *str, int *j)
{
	(void)list;
	char	*search;
	
	search = ft_how_far(str, j);
	printf("%s\n", search);
	return (0);
}