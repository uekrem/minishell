#include "minishell.h"

int	is_redirection(t_link *link)
{
	if (link->type == INPUT_R || link->type == OUTPUT_R
		|| link->type == D_INPUT_R || link->type == D_OUTPUT_R)
		return (1);
	return (0);
}

void	add_arguman(t_command *cmd, t_link **link)
{
	t_execute	*new_execute;

	if (is_redirection(*link) && ((*link)->prev == NULL || (*link)->prev->type == PIPE))
	{
		new_execute = lst_new_elem_execute(NULL);
		lst_add_back_execute(&cmd->execute, new_execute);
		cmd->radi = fill_redirect(*link, &cmd->radi);
	}
	else if ((*link)->type == ARG)
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

void	add_back_cmd(t_command *new_cmd)
{
	t_command	*tmp;

	tmp = g_glbl.cmd;
	if (!(tmp))
		g_glbl.cmd = new_cmd;
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
	pipe(new_cmd->fd);
	new_cmd->pid = -1;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_fill_command(t_link *link)
{
	t_command	*new_cmd;
    (void) new_cmd;

    g_glbl.cmd = NULL;
	new_cmd = NULL;
	while (link)
	{
		if (link->type == PIPE || link->prev == NULL)
		{
			if (link->type == PIPE)
				link = link->next;
			if (link->type == PIPE)
				break;
			new_cmd = setup_cmd();
			add_back_cmd(new_cmd);
			g_glbl.cmd_count++;
		}
		if (!link)
			break ;
		add_arguman(new_cmd, &link);
		if (link)
            link = link->next;
	}
}
