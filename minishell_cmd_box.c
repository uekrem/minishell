#include "minishell.h"

int	prev_type(enum e_token type)
{
	if (type == INPUT_R || type == OUTPUT_R || type == D_INPUT_R || type == D_OUTPUT_R)
		return (1);
	return (0);
}

t_radira	*lst_last_redirect(t_radira *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	lst_add_back_redirect(t_radira **lst, t_radira *new_node)
{
	t_radira	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last_redirect(*lst);
			tmp->next = new_node;
		}
	}
}

t_radira	*lst_new_elem_redirect(enum e_token type, char *value)
{
	t_radira	*new_elem;

	new_elem = (t_radira *)ft_calloc(sizeof(t_radira), 1);
	if (!new_elem)
		return (0);
	new_elem->type = type;
	new_elem->value = value;
	new_elem->next = 0;
	return (new_elem);
}

t_radira	*fill_redirect(t_link *link, t_radira **redirects)
{
	t_radira	*new_redirect;

	if (link->type == OUTPUT_R)
	{
		new_redirect = lst_new_elem_redirect(OUT_FILE, link->next->value);
		lst_add_back_redirect(redirects, new_redirect);
	}
	else if (link->type == INPUT_R)
	{
		new_redirect = lst_new_elem_redirect(IN_FILE, link->next->value);
		lst_add_back_redirect(redirects, new_redirect);
	}
	else if (link->type == D_INPUT_R)
	{
		new_redirect = lst_new_elem_redirect(D_INPUT_R, link->next->value);
		lst_add_back_redirect(redirects, new_redirect);
	}
	else if (link->type == D_OUTPUT_R)
	{
		new_redirect = lst_new_elem_redirect(D_OUTPUT_R, link->next->value);
		lst_add_back_redirect(redirects, new_redirect);
	}
	return (*redirects);
}

t_execute	*lst_last_execute(t_execute *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	lst_add_back_execute(t_execute **lst, t_execute *new_node)
{
	t_execute	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last_execute(*lst);
			tmp->next = new_node;
		}
	}
}

t_execute	*lst_new_elem_execute(char *value)
{
	t_execute	*new_elem;

	new_elem = (t_execute *)calloc(sizeof(t_execute), 1);
	if (!new_elem)
		return (0);
	new_elem->value = value;
	new_elem->next = 0;
	return (new_elem);
}

t_execute	*fill_execute(t_link *link, t_execute **execute)
{
	t_execute	*new_execute;

	if (link->type == ARG && link->prev == 0)
	{
		new_execute = lst_new_elem_execute(link->value);
		lst_add_back_execute(execute, new_execute);
	}
	else if (link->type == ARG && prev_type(link->prev->type) == 0)
	{
		new_execute = lst_new_elem_execute(link->value);
		lst_add_back_execute(execute, new_execute);
	}
	return (*execute);
}

void	add_arguman(t_command *cmd, t_link **link)
{
	if ((*link)->type == ARG)
	{
		cmd->execute = fill_execute(*link, &cmd->execute);
	}
	else if (/*(*link)->type == IN_FILE || (*link)->type == OUT_FILE
		|| */(*link)->type == D_INPUT_R)
	{
		cmd->radi = fill_redirect(*link, &cmd->radi);
	}
	else if ((*link)->type == D_OUTPUT_R)
	{
		cmd->radi = fill_redirect(*link, &cmd->radi);
	}
	else if ((*link)->type == INPUT_R || (*link)->type == OUTPUT_R)
	{
		cmd->radi = fill_redirect(*link, &cmd->radi);
	}
}

void	add_back_cmd(t_command **cmd, t_command *new_cmd)
{
	t_command	*tmp;

	tmp = *cmd;
	if (!(tmp))
		*cmd = new_cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}

t_command	*setup_cmd(void)
{
	t_command	*new_cmd;
    
	new_cmd = ft_calloc(sizeof(t_command), 1);
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_fill_command(t_command **cmd, t_link *link)
{
	t_command	*new_cmd;
    (void) cmd;
    (void) new_cmd;
    
    *cmd = NULL;
	new_cmd = NULL;
	while (link)
	{
		if (link->type == PIPE || link->prev == NULL)
		{
			if (link->type == PIPE)
				link = link->next;
			new_cmd = setup_cmd();
			add_back_cmd(cmd, new_cmd);
		}
		if (!link)
			break ;
		add_arguman(new_cmd, &link);
		if (link)
            link = link->next;
	}
}