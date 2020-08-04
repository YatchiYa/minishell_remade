# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wpark <wpark@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/13 14:21:52 by froussel          #+#    #+#              #
#    Updated: 2020/03/14 18:06:23 by wpark            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
SRC_NAME = main.c \
		check_rdir_dollar.c \
		dollar_quotes.c \
		error_1.c \
		error_2.c \
		exec_cd.c \
		exec_command.c \
		exec_echo.c \
		exec_env.c \
		exec_exit.c \
		exec_export.c \
		exec_non_btin.c \
		exec_pwd.c \
		exec_unset.c \
		free_1.c \
		free_2.c \
		get_static.c \
		init_cmd.c \
		init_env.c \
		lexer_1.c \
		lexer_2.c \
		lst_cmd.c \
		lst_env_to_char.c \
		lst_env.c \
		lst_rdir.c \
		parser_1.c \
		pipe.c \
		quit.c \
		read_line.c \
		redirection.c

SRC_PATH = ./srcs
SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

INC_LINK = -I./includes
LIBFT = -L./lib/libft -lft
all : $(NAME)

$(NAME) : $(OBJ) libft
	gcc $(FLAGS) $(OBJ) $(INC_LINK) $(LIBFT) -o $(NAME) 

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc $(FLAGS) $(INC_LINK) -o $@ -c $<
	
# libft compile
libft :
	@$(MAKE) -C ./lib/libft all

clean :
	@$(MAKE) -C ./lib/libft clean
	@rm -rf ./obj

fclean :
	@$(MAKE) -C ./lib/libft fclean
	@rm -rf ./obj $(NAME)

re : fclean all

.PHONY: all clean fclean re
