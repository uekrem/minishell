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
				continue;
			temp = ft_strlen(list[i].value, 0, '\0');
			list[i].value = ft_restrlen(list[i].value, &j);
			j = j - (temp - ft_strlen(list[i].value, 0, '\0'));
		}
	}
}

void		ft_env_check(char *input, t_list *list)	
{
	int	i;

	i = -1;
	while (++i < ft_str_shred(input))
		ft_str_rebuild(list, i);
}

void	ft_str_base(t_list *list, char *input, int start, int finish, int *now)
{
		int	i;

		i = 0;
		list[*now].value = malloc(sizeof(char) * ((finish - start) + 1));
		while (input[start] && start != finish)
		{
			list[*now].value[i] = input[start];
			start += 1;
			i++;
		}
		list[*now].value[i] = '\0';
		*now += 1;
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
			ft_couple_core(input, &i, input[i]);
		ft_str_base(list, input, temp, i, &now);
	}
	list[now].value = NULL;
}

int	ft_what_should(t_list *list, int i)
{
	while (list[i].type != PIPE && i != 0)
		i--;
	if (!ft_opr_which(list[i].value[0]) && i == 0)
		i--;
	if (list[++i].type == COMMAND)
		return (0);
	return (1);
}

void	ft_untype(t_list *list)
{
	int	i;
	int	which;

	i = -1;
	while (++i < list->list_len)
	{
		which = ft_opr_which(list[i].value[0]);
		if (i == 0 && !which)
			list[i].type = COMMAND;
		else if (which == 1)
		{
			list[i].type = PIPE;
			if (list[i + 1].value)
				list[++i].type = COMMAND;
		}
		else if (which == 2)
		{
			list[i].type = D_INPUT_R;
			if (!list[i].value[1])
				list[i].type = INPUT_R;
			list[++i].type = FILE_NAME;
			if(ft_what_should(list, i))
				list[++i].type = COMMAND; 
		}
		else if (which == 3)
		{
			list[i].type = D_OUTPUT_R;
			if (!list[i].value[1])
				list[i].type = OUTPUT_R;
			list[++i].type = FILE_NAME;
			if(ft_what_should(list, i))
				list[++i].type = COMMAND; 
		}
		else
			list[i].type = ARG;
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
