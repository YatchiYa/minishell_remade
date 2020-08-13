NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC = 	srcs/cmd_init.c	\
		srcs/cmd_init_extends.c	\
		srcs/env_init.c	\
		srcs/env_init_extends.c	\
		srcs/exit_1.c	\
		srcs/exit_2.c	\
		srcs/ft_getline.c	\
		srcs/get_next_line.c	\
		srcs/handle_cd.c	\
		srcs/handle_command.c	\
		srcs/handle_echo.c	\
		srcs/handle_env.c	\
		srcs/handle_exit.c	\
		srcs/handle_export.c	\
		srcs/handle_non_btin.c	\
		srcs/handle_pwd.c	\
		srcs/handle_unset.c	\
		srcs/main.c	\
		srcs/parse_dollars_2.c	\
		srcs/pipe_handle.c	\
		srcs/prompt.c	\
		srcs/redirect_config.c	\
		srcs/redirections.c	\
		srcs/tools.c	\
		srcs/tools_2.c	\
		srcs/tools_3.c	\
		srcs/tools_4.c	\
		srcs/trim_errors_argv.c	\
		srcs/trim_parse.c

OBJS = $(SRC:.c=.o)

HEADER = srcs

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) -I $(HEADER) $(SRC) -o minishell

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all