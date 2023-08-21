/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:34:10 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:50:26 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glbl	g_glbl;

void	ft_replace_zero(t_list *list)
{
	list->flag = 0;
	g_glbl.flag = 0;
	g_glbl.cmd_count = 0;
	g_glbl.heredoc = 0;
	g_glbl.parent_pid = 1;
	list->list_len = ft_str_shred(g_glbl.input);
}

void	ft_parse_start(t_list *list)
{
	ft_uname(list, g_glbl.input);
	ft_untype(list);
	ft_env_check(g_glbl.input, list);
	ft_appro_name(list);
}

void	ft_begin_assign(char **env)
{
	init_envair(env);
	signal_init();
	fill_paths();
	g_glbl.erorno = 0;
}

int	ft_run_before(t_list **list, t_link **link)
{
	if (ft_pipe_more(*list))
	{
		ft_decomp_free(2, *list, *link);
		return (1);
	}
	*link = ft_copy_list(*list);
	if (ft_parse_eror(*link))
	{
		ft_decomp_free(3, *list, *link);
		return (1);
	}
	if (ft_fill_command(*link))
	{
		ft_decomp_free(4, *list, *link);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_list	*list;
	t_link	*link;

	(void)argv;
	list = NULL;
	link = NULL;
	if (argc == 1)
	{
		ft_begin_assign(env);
		while (1)
		{
			g_glbl.input = readline("minishell: ");
			add_history(g_glbl.input);
			ctrl_d(&g_glbl);
			if (ft_opr_pair(g_glbl.input))
				continue ;
			list = malloc(sizeof(t_list) * (ft_str_shred(g_glbl.input) + 1));
			ft_replace_zero(list);
			ft_parse_start(list);
			if (ft_run_before(&list, &link))
				continue ;
			run_cmd();
			ft_decomp_free(4, list, link);
		}
	}
}
