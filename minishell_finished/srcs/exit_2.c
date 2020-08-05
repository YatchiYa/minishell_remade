
#include "minishell.h"

void		eof_exit(void)
{
	ft_putstr("\n");
	free_all();
	exit(0);
}

void		error_minishell(void)
{
	ft_putstr_fd("minishell: fatal error : ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	free_all();
	exit(EXIT_FAILURE);
}

int			syntax_error(char *token, int ret)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("\'\n", 2);
	return (ret);
}

int			error_commande(char *cmd, int ret)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

int			too_many_arg_error(char *cmd, int ret)
{
	ft_putstr_fd("minishell: too many arguments: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}
