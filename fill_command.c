// #include "minishell.h"

// t_command	*setup_cmd(t_list *list)
// {
// 	t_command	*commands;

// 	commands = ft_calloc(sizeof(t_command), 1);
// 	pipe(commands->fd);
// 	commands->pid = -1;
// 	commands->execute = malloc(sizeof(char **) * (count_arguman(list) + 2));
// 	commands->redirects = ft_calloc(sizeof(t_redirection), 1);
// 	commands->execute = 0;
// 	commands->redirects = 0;
// 	commands->prev = NULL;
// 	commands->next = NULL;
// 	return (commands);
// }

// void	add_back_cmd(t_command **commands, t_command *new_cmd)
// {
// 	t_command	*tmp;

// 	tmp = *commands;
// 	if (!(tmp))
// 		*commands = new_cmd;
// 	else
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_cmd;
// 		new_cmd->prev = tmp;
// 	}
// }

// void	add_arguman(t_list **list, t_command *new)
// {
// 	int	i;

// 	i = 0;
// }

// int	count_arguman(t_list *list)
// {
// 	int	i;
// 	int	count_arg;

// 	i = 0;
// 	count_arg = 0;
// 	while (list[i].type != END)
// 	{
// 		if (list[i].type == ARG)
// 			count_arg++;
// 		i++;
// 	}
// 	return (count_arg);
// }

// int count_redirect(t_list *list)
// {
//     int i;

//     i = 0;

//     while(list[i] != END)
//     {


//     }
// }

// void	fill_command(t_list *list, t_command *cmd)
// {
// 	int i;
// 	t_command = *new;

// 	i = 0;
// 	while (list[i].type != END)
// 	{
// 		if (list[i].type == PIPE || i == 0)
// 		{
// 			if (list[i].type == PIPE)
// 				i++;
// 			new = setup_cmd(list);
// 			add_back_cmd(&cmd, new);
// 			// komut sayısını artırma yeri
// 		}
// 		if (!list)
// 			break ;
// 		add_arguman(&list, new);
// 		i++;
// 	}
// }