NAME := minishell
CC := gcc
FLAGS := -Wall -Wextra -Werror

SRCS := main.c \
		minishell_utils.c \

OBJS := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

RM := rm -f

${NAME}: ${OBJS}
	@echo "[COMPILING...]"
	@ $(CC) $(FLAGS) $(OBJS) -o ${NAME} -lreadline
	@echo "[COMPILING FINISHED]"

all: ${NAME}

clean:
	@echo "[DELETING...]"
	@${RM} ${OBJS}
	@echo "[DELETED]"

fclean: clean
	@${RM} ${NAME}

re: fclean all
