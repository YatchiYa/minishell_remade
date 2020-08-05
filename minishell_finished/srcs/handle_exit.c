
#include "minishell.h"

int		no_file_error(char *cmd, char *file, int ret)
{
	ft_putstr_fd("minishell", 2);
	if (cmd)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
	}
	if (file)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(file, 2);
	}
	ft_putstr_fd(": No such file or directory\n", 2);
	return (ret);
}

int		exit_digit_error(char *cmd, char *file, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_all();
	return (ret);
}

int		file_too_long(char *cmd, char *file, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": File name too long\n", 2);
	return (ret);
}

int		check_str_digit(char *s)
{
	while (s && *s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int		handle_exit(t_cmd *cmd)
{
	int		count;
	int		index;
	char	ret;

	count = count_arg(cmd->argv);
	index = check_str_digit(cmd->argv[1]);
	if (cmd->argv[1])
	{
		if (!index)
		{
			ft_putstr("exit\n");
			exit(exit_digit_error(cmd->argv[0], cmd->argv[1], 2));
		}
		if (count > 2)
		{
			ft_putstr("exit\n");
			return (too_many_arg_error(cmd->argv[0], 1));
		}
		ret = (char)ft_atoi(cmd->argv[1]);
		free_all();
		exit(ret);
	}
	free_all();
	exit(EXIT_SUCCESS);
}
