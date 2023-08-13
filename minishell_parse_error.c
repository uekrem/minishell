#include "minishell.h"

int	check_pars_error_child(t_link *link)
{
	if (link->type == INPUT_R || link->type == OUTPUT_R
		|| link->type == D_INPUT_R)
	{
		if (link->next == NULL || link->next->type != ARG)
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	return (0);
}

int	check_pars_error_child2(t_link *link)
{
	if (link->type == D_OUTPUT_R)
	{
		if (link->next == NULL || link->next->type != ARG)
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	return (0);
}

int	check_pars_error(t_link	*link)
{
	int	tmp;

	tmp = dup(1);
	dup2(2, 1);
	while (link)
	{
		if (check_pars_error_child(link))
			return (1);
		if (check_pars_error_child2(link))
			return (1);
		if (link->type == PIPE)
		{
			if (link->next == NULL)
			{
				printf("syntax error near unexpected link `newline'\n");
				return (1);
			}
		}
		link = link->next;
	}
	dup2(tmp, 1);
	close(tmp);
	return (0);
}

void	free_token(t_link *link)
{
	t_link	*tmp;
	t_link	*token;

	token = link;
	while (token)
	{
		free(token->value);
		token = token->next;
	}
	token = link;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}

int	 ft_parse_eror(t_link *link)
{
	if (check_pars_error(link))
	{
		g_glbl.erorno = 258;
		return (1);
	}
	return (0);
}
