NAME = minishell

CC = gcc

FLAGS = 


SRC = src/builtin.c \
	src/cd.c \
	src/close.c \
	src/dollar.c \
	src/echo.c \
	src/env.c \
	src/envv.c \
	src/export.c \
	src/external-commands.c \
	src/ft_split.c \
	src/ft_strsplit.c \
	src/get_absolute_path.c \
	src/init.c \
	src/itoa.c \
	src/main.c \
	src/minishell.c \
	src/parse_line.c \
	src/prompt.c \
	src/pwd.c \
	src/redirect.c \
	src/signal.c \
	src/tools.c \
	src/trim_parse.c \
	src/unset.c \
	src/gnl/get_next_line.c \
	src/gnl/get_next_line_utils.c \

OBJS = $(SRC:.c=.o)

HEADER = srcs/minishell.h

all: $(NAME)

$(LIBS):
	make -C $(LIBFT_DIR)

$(NAME): $(SRC)
	$(CC) $(FLAGS) -I $(HEADER) $(SRC) -o minishell

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all