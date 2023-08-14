NAME        := minishell
CC        := gcc

FLAGS    := -Wall -Wextra -Werror #-fsanitize=address -g
SRCS        :=              libft/ft_atoi.c \
                          libft/ft_bzero.c \
                          libft/ft_calloc.c \
                          libft/ft_isalnum.c \
                          libft/ft_isalpha.c \
                          libft/ft_isascii.c \
                          libft/ft_isdigit.c \
                          libft/ft_isprint.c \
                          libft/ft_itoa.c \
                          libft/ft_lstadd_back.c \
                          libft/ft_lstadd_front.c \
                          libft/ft_lstclear.c \
                          libft/ft_lstdelone.c \
                          libft/ft_lstiter.c \
                          libft/ft_lstlast.c \
                          libft/ft_lstnew.c \
                          libft/ft_lstsize.c \
                          libft/ft_memchr.c \
                          libft/ft_memcmp.c \
                          libft/ft_memcpy.c \
                          libft/ft_memmove.c \
                          libft/ft_memset.c \
                          libft/ft_putchar_fd.c \
                          libft/ft_putendl_fd.c \
                          libft/ft_putnbr_fd.c \
                          libft/ft_putstr_fd.c \
                          libft/ft_split.c \
                          libft/ft_strchr.c \
                          libft/ft_strdup.c \
                          libft/ft_striteri.c \
                          libft/ft_strjoin.c \
                          libft/ft_strlcat.c \
                          libft/ft_strlcpy.c \
                          libft/ft_strlenn.c \
                          libft/ft_strmapi.c \
                          libft/ft_strncmp.c \
                          libft/ft_strnstr.c \
                          libft/ft_strrchr.c \
                          libft/ft_strtrim.c \
                          libft/ft_substr.c \
                          libft/ft_tolower.c \
                          libft/ft_toupper.c \
                          minishell_main.c \
                          ./parse/minishell_sum.c \
                          ./parse/minishell_utils.c \
                          minishell_signall.c \
                          builtins/builtins.c \
                          builtins/ft_cd.c \
                          builtins/ft_echo.c \
                          builtins/ft_export.c \
                          builtins/ft_pwd.c \
                          builtins/ft_env.c \
                          builtins/ft_unset.c \
                          builtins/ft_exit.c \
                          builtins/ft_cd_utils.c \
                          builtins/ft_export_adding.c \
                          builtins/ft_export_utils.c \
                          ./exec_box/minishell_link.c \
                          ./exec_box/minishell_parse_error.c \
                          ./exec_box/minishell_cmd_box.c \
                          ./exec_box/minishell_exec_add.c \
                          ./exec_box/minishell_radi_add.c \
                          run_cmd.c \
                          heredoc.c \
                          actuation.c \
                          redirects.c \
                          close_fd.c \
                          get_path.c \
                          get_path_error.c \
                          actuation2.c \
                          create_file.c \
                          fill_path.c \
                          signal.c \
                          ./env/minishell_env_parse.c \
                          ./env/minishell_env_utils.c \
                          ./env/minishell_env_creat.c \
                          ./env/minishell_env_utils2.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I/Users/uguyildi/readline/include

RM		    := rm -f

${NAME}:	${OBJS}
			@echo "[COMPILING...]"
			@${CC} ${FLAGS} -o ${NAME} ${OBJS} -I/Users/uguyildi/readline/include -L/Users/uguyildi/readline/lib -lreadline
			@echo "[COMPILING FINISHED]"

all:		${NAME}

bonus:		all

clean:
			@echo "[DELETING...]"
			@${RM} *.o */*.o */*/*.o
			@echo "[DELETED]"

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
