#include "minishell.h"

char		ft_quartes_selec(char *str, int	i)
{
	int		num;
	char	c;
	int		check;

	num = -1;
	check = 1;
	while (++num < i)
	{
		if ((str[num] == 39 || str[num] == '"') && check)
		{
			check = 0;
			c = str[num];
		}
		else if (str[num] == c && !check)
		{
			check = 1;
			c = ' ';
		}
	}
	return (c);
}

int			ft_stay_stop(char c)
{
	if (((c >= 32 && c <= 47) 
		|| (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 96)
		|| (c >= 123 && c <= 126) 
		|| c == ' ') 
		&& c )
		return(1);
	return (0);
}

void		ft_str_rebuild(t_list *list, int i)
{
	int		j;
	int		temp;

	j = -1;
	if (list[i].value[j + 1] == '$')
		if (!list[i].value[j + 2])
			return;
	while (list[i].value[++j])
	{
		if (list[i].value[j] == '$' && ft_quartes_selec(list[i].value, j) != 39)
		{
			j++;
			if (ft_stay_stop(list[i].value[j]))
			{
				if (list[i].value[j] == '?')
				{
					temp = ft_strlen(list[i].value, 0, '\0');
					list[i].value = ft_restrlen2(list[i].value, &j);
					j = (j - (temp - ft_strlen(list[i].value, 0, '\0'))) - 1;
				} 
				continue;
			}
			temp = ft_strlen(list[i].value, 0, '\0');
			list[i].value = ft_restrlen(list[i].value, &j);
			j = (j - (temp - ft_strlen(list[i].value, 0, '\0'))) - 1;
		}
	}
}

void		ft_env_check(char *input, t_list *list)	
{
	int	i;

	i = -1;
	while (++i < ft_str_shred(input))
	{
		if (list[i].type == D_OUTPUT_R)
		{
			i++;
			continue;
		}
		ft_str_rebuild(list, i);
	}
}

void	ft_str_base(t_list *list, char *input, int start, int finish, int now)
{
		int	i;

		i = 0;
		list[now].value = malloc(sizeof(char) * ((finish - start) + 1));
		while (input[start] && start != finish)
		{
			list[now].value[i] = input[start];
			start += 1;
			i++;
		}
		list[now].value[i] = '\0';
		list[now].type = 99;
}

void	ft_uname(t_list *list, char *input)
{
	int		i;
	int		now;
	int		temp;			

	i = 0;
	now = 0;
	while (input[i])
	{
		while (input[i] == ' ' && input[i])
			i++;
		temp = i;
		if (input[i])
		{
			ft_couple_core(input, &i, input[i]);
			ft_str_base(list, input, temp, i, now);
			now++;
		}
	}
	list[now].value = NULL;
}

int		ft_check_flag(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[0] != '-')
			break;
		else if (i != 0 && str[i] == '-')
			break;
	}
	if (!str[i])
		return (1);
	return (0);
}

char		ft_issue(char *str, char sea)
{
	int		i;
	char 	c;

	i = -1;
	c = ' ';
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == 39) && c == ' ')
			c = str[i];
		else if (str[i] == c)
			c = ' ';
		else if (str[i] == sea)
			return (c);
	}
	return (0);
}

void	ft_untype(t_list *list)
{
	int	i;

	i = -1;
	while (++i < list->list_len)
	{
		if (list[i].type != 99)
			continue;
		list[i].type = ARG;
		if (list[i].value[0] == '<' && list[i].value[1] == '<')
			list[i].type = D_OUTPUT_R;
		else if (list[i].value[0] == '>' && list[i].value[1] == '>')
			list[i].type = D_INPUT_R;
		else if (list[i].value[0] == '>')
			list[i].type = INPUT_R;
		else if (list[i].value[0] == '<')
			list[i].type = OUTPUT_R;	
		else if (list[i].value[0] == '|')
			list[i].type = PIPE;
	}
	list[i].type = END;
}

char	*ft_appro_proc(char *str, int value)
{
	int		i;
	int		flag;
	int		indepent;
	char	*new_str;

	i = -1;
	flag = 0;
	indepent = -1;
	new_str = malloc(sizeof(char) * (value + 1));
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == 39) && flag == 0)
				flag = str[i];
			else if (flag != 0 && str[i] == flag)
				flag = 0;
			else
				new_str[++indepent] = str[i];
	}
	new_str[++indepent] = '\0';
	free(str);
	return (new_str);
}

void	ft_appro_name(t_list *list)
{
	int		i;
	int		j;
	int		flag;
	int		value;

	i = -1;
	while (++i < list->list_len)
	{
		flag = 0;
		value = 0;
		j = -1;
		while (list[i].value[++j])
		{
			if ((list[i].value[j] == '"' || list[i].value[j] == 39) && flag == 0)
				flag = list[i].value[j];
			else if (flag != 0 && list[i].value[j] == flag)
				flag = 0;
			else
				value++;
		}
		list[i].value = ft_appro_proc(list[i].value, value);
	}
}

void	ft_free(t_list *list)
{
	int	i;

	i = -1;
	while (++i < list->list_len)
		free(list[i].value);
	free(list);
	free(g_glbl.input);
}