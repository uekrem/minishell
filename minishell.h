/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:29:16 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/22 13:27:23 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

enum					e_token
{
	PIPE,
	OUTPUT_R,
	INPUT_R,
	D_OUTPUT_R,
	D_INPUT_R,
	ARG,
	COMMAND,
	FILE_NAME,
	FLAG,
	OUT_FILE,
	IN_FILE,
	END
};

typedef struct s_radira
{
	char				*value;
	enum e_token		type;
	struct s_radira		*prev;
	struct s_radira		*next;
}						t_radira;

typedef struct s_execute
{
	char				*value;
	struct s_execute	*prev;
	struct s_execute	*next;
}						t_execute;

typedef struct s_command
{
	pid_t				pid;
	int					fd[2];
	int					heredoc_fd[2];
	t_execute			*execute;
	t_radira			*radi;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct s_glbl
{
	char				**env;
	char				**export;
	char				**path;
	char				*input;
	int					flag;
	int					heredoc;
	int					cmd_count;
	int					parent_pid;
	int					erorno;
	int					export_plus_flag;
	int					export_flag;
	int					env_flag;
	t_command			*cmd;
}						t_glbl;

extern t_glbl			g_glbl;

typedef struct s_list
{
	enum e_token		type;
	int					list_len;
	int					flag;
	char				*value;
}						t_list;

typedef struct s_link
{
	enum e_token		type;
	int					list_len;
	int					flag;
	char				*value;
	struct s_link		*prev;
	struct s_link		*next;
}						t_link;

int						ft_opr_pair(char *input);
int						ft_str_shred(char *input);
int						ft_strlen(char *input, int index, char c);
int						ft_opr_which(char input);
void					ft_uname(t_list *list, char *input);
void					ft_untype(t_list *list);
void					ft_couple_core(char *input, int *i, char c);
void					ft_env_check(char *input, t_list *list);
char					*ft_restrlen(char *str, int *j);
char					*ft_appro_proc(char *str, int value);
void					ft_appro_name(t_list *list);
void					ft_str_base(t_list *list, int start, int finish,
							int now);
char					*ft_piece(char *env);
int						ft_builtins(t_command *cmd);
void					ft_echo(t_command *cmd);
void					ft_pwd(void);
void					ft_cd(t_command *cmd);
void					ft_export(t_command *cmd);
int						which_commant(char *str1, char *str2);
int						arg_count(t_execute *execute);
int						export_size(void);
void					ft_env(t_execute *cmd);
void					init_env(t_list *list);
void					ft_unset(t_command *cmd);
void					ft_exit(t_command *cmd);
void					ctrl_d(t_glbl *glbl);
void					free_execute(t_glbl *glbl);
void					free_char(char **arg);
char					ft_issue(char *str, char sea);
int						ft_check_flag(char *str);
void					ft_strwrite2(char *new_str, char *str, int *step,
							int c);
void					ft_free(t_list *list);
t_link					*ft_lstnew(t_list *list);
void					ft_lstadd_back(t_link **lst, t_link *new);
t_link					*ft_lstlast(t_link *lst);
int						ft_parse_eror(t_link *link);
int						ft_fill_command(t_link *link);
t_link					*ft_copy_list(t_list *list);
t_radira				*fill_redirect(t_link *link, t_radira **redirects);
t_execute				*fill_execute(t_link *link, t_execute **execute);
int						check_arg(char *str, char *status);
void					ft_opr_step(char *input, int *i);
int						ft_while_break(char *input, int *i, char *c);
void					run_cmd(void);
void					heredoc(int *fd, char *endline);
void					actuation(t_command *cmd);
int						redirect_outputs(t_command *cmd);
void					close_all_fd(void);
char					*get_path(char *cmd);
void					directory_err(char *str);
int						is_parent(void);
void					no_file_err(char *str);
char					**get_arg_fill(t_execute *execute);
void					command_err(char *str);
int						input(char *file);
int						output(char *file, int mode);
int						contain_heredoc(void);
void					fill_paths(void);
void					signal_init(void);
int						is_builtin(t_command *cmd);
void					lst_add_back_execute(t_execute **lst,
							t_execute *new_node);
t_execute				*lst_new_elem_execute(char *value);
char					*ft_how_far(char *str, int *j);
char					*ft_env_search(char *str);
int						ft_stay_stop(char c);
char					ft_quartes_selec(char *str, int i);
char					*ft_env_null(char *str, int *j, int temp);
void					ft_strwrite2(char *new_str, char *str, int *step,
							int c);
void					ft_strwrite(char *new_str, char *str, int *step,
							char c);
char					*ft_str_rebuild_base(char *list, int *j);
char					*ft_str_rebuild_query(char *list, int *j);
int						ft_how_far_chec(char c);
char					*ft_restrlen2(char *str, int *j);
char					*ft_env_null_orien(char *search, char *str, int *j,
							int temp);
int						ft_pipe_more(t_list *list);
int						ft_run_before(t_list **list, t_link **link);
void					ft_begin_assign(char **env);
void					init_envair(char **env);
void					ft_decomp_free(int id, t_list *list, t_link *link);
void					ft_free_exec(t_execute *exec);
void					ft_free_radi(t_radira *radi);
void					free_execute(t_glbl *glbl);
void					ft_add_export(char *arg);
void					ft_add_env(char *arg);
void					ft_print_export(void);
void					ft_adding_export(char **new_export, char *arg);
void					ft_adding_env(char **new_env, char *arg);
int						which_commant(char *str1, char *str2);
void					cd_err(char *value, char *str);
char					*check_tilde(char *str);
int						ft_strncheck(const char *s1, const char *s2, size_t n);
char					*ft_export_join(char *s1, char *s2);
int						equal_process(char *str1, char *str2, int *j, int *k);
t_execute				*ft_double_n(int *i, int *flag, t_execute *temp);
void					ft_check_zero(int flag);
void					ft_echo_defini(int *i, int *flag);

#endif
