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
	printf("Missing double or single quotes\n");
	return (1);
}

void	ft_couple_core(char *input, int *i, char c)
{
	c = ' ';
	if (input[*i] == '|')
	{
		*i += 1;
		return;
	}
	else if (ft_opr_which(input[*i]))
	{
		*i += 1;
		if (ft_opr_which(input[*i]) > 1 && input[*i] != input[(*i) - 1])
			return;
		else if (ft_opr_which(input[*i]) > 1)
			*i += 1;
		return;
	}
	if (input[*i] == 39 || input[*i] == '"')
	{
		c = input[*i];
		*i += 1;
		if (input[*i] == c)
			c = ' ';
	}
	while (input[*i] && input[*i] != c)
	{
		*i += 1;						
		if (input[*i] == c && c != ' ')
			c = ' ';
		else if ((input[*i] == '"' || input[*i] == 39) && c == ' ')
		{
			c = input[(*i)++];
			if (input[*i] == c)
				c = ' ';
		}
		else if (ft_opr_which(input[*i]) && c == ' ')
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
		if (input[i])
			flag++;
		if (input[i])
			ft_couple_core(input, &i, input[i]);
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
	while (str[*j])
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
	while (value > 0)
	{
		search[counter] = str[*j - value];
		counter++;
		value--;
	}
	search[counter] = '\0';
	return (search);
}

char	*ft_piece(char *env)
{
	char	*piece;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (env[i] != '=')
		++i;
	++i;
	piece = malloc(sizeof(char) * (ft_strlen(env, i, '\0') + 1));
	while (env[i])
	{
		piece[++j] = env[i];
		i++;
	}
	piece[++j] = '\0';

	return (piece);
}

char    *ft_env_search(char *str)
{
    int i;
    int j;
    i = -1;
    while (g_glbl.env[++i])
    {
        j = -1;
        while (g_glbl.env[i][++j])
        {
            if (str[j] == g_glbl.env[i][j])
                continue;
            break;
        }
        if (g_glbl.env[i][j] == '=' && str[j] == '\0')
            break;
    }
	free(str);
    if (g_glbl.env[i])
        return(ft_piece(g_glbl.env[i]));
    return (NULL);
}

void	ft_strwrite(char *new_str, char *str, int *step, char c)
{
	int	j;

	j = 0;
	while (str[j] != c && str[j])
	{
		new_str[*step] = str[j];
		*step += 1;
		j++;
	}
}

char	*ft_env_null(char *str, int *j, int temp)
{
	char	*new_char;
	int		total;
	int		step;

	total = 0;
	step = 0;
	total += temp;
	total += ft_strlen(str, *j, '\0');
	new_char = malloc(sizeof(char) * (total + 1));
	ft_strwrite2(new_char, str, &step, temp - 1);
	ft_strwrite(new_char, &str[*j], &step, '\0');
	new_char[step] = '\0';
	free(str);
	return (new_char);
}

void	ft_strwrite2(char *new_str, char *str, int *step, int c)
{
	int	j;

	j = 0;
	while (j < c && str[j])
	{
		new_str[*step] = str[j];
		*step += 1;
		j++;
	}
}

int	ft_intlen()
{
	int	tut;
	int	i;

	i = 0;
	tut = g_glbl.erorno;
	if (tut == 0)
		return (i + 1);
	while (1)
	{
		if (tut > 0)
			return (i);
		tut /= 10;
		i++;
	}
}

char	*ft_restrlen2(char *str, int *j)
{
	char	*search = NULL;
	char	*new_char;
	int		total;
	int		step;
	int		temp;

	total = 0;
	step = 0;
	temp = *j;
	*j += 1;
	search = ft_itoa(g_glbl.erorno);
	total += temp;
	total += ft_strlen(search, 0, '\0');
	total += ft_strlen(str, *j, '\0');
	new_char = malloc(sizeof(char) * (total + 1));
	ft_strwrite2(new_char, str, &step, temp - 1);
	ft_strwrite(new_char, search, &step, '\0');
	ft_strwrite(new_char, &str[*j], &step, '\0');
	new_char[step] = '\0';
	free(search);
	free(str);
	return (new_char);
}

char	*ft_restrlen(char *str, int *j)
{
	char	*search = NULL;
	char	*new_char;
	int		total;
	int		step;
	int		temp;

	total = 0;
	step = 0;
	temp = *j;
	search = ft_how_far(str, j);
	search = ft_env_search(search);
	if (search == NULL)
	{
		free(search);
		return (ft_env_null(str, j, temp));
	}
	total += temp;
	total += ft_strlen(search, 0, '\0');
	total += ft_strlen(str, *j, '\0');
	new_char = malloc(sizeof(char) * (total + 1));
	ft_strwrite2(new_char, str, &step, temp - 1);
	ft_strwrite(new_char, search, &step, '\0');
	ft_strwrite(new_char, &str[*j], &step, '\0');
	new_char[step] = '\0';
	free(search);
	free(str);
	return (new_char);
}