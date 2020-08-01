
#include "minishell.h"

void	signal_handler_main()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler2);
	signal(SIGTSTP, signal_handler3);
}

en_status	exec_command(char *line)
{
	int			ret;
	char		**tab;
	en_status	status;

	ret = 0;
	if (check_error(line) == 0)
	{
		printf("minishell : syntax error \n");
		return (1);
	}
	line = ft_substr(line, 0, ft_strlenx(line) - 1);
	tab = ft_strsplit(line, ';');
	ret = 0;
	while (tab[ret])
	{
		status = pipeCmds(tab[ret]);
		ret++;
	}
	return (status);
}

void	minishell(char **envv)
{
    char		*line;
	char		*buff;
	int			ret;
	char		*first_char;
	int			status;

	buff = NULL;
	line = strdup(" ");
	status = 1;
	while (status)
	{
		isPipe = 0;
		if (ctrld == 0)
			display_prompt_msg();
		signal_handler_main();
		ret = get_next_line(0, &buff);
		line = ft_strjoin(line, buff);
		line = ft_substr(line, 1, ft_strlenx(line));
		if (ctrld == 1)
			first_char = ft_substr(line, 0, 1);
		if (ft_strlenx(line) == 0 && ctrld == 1)
			exit(0);
		if (line[ft_strlenx(line) - 1] != '\n')
		{
			free(buff);
			if (ctrld == 1)
				line = ft_strjoin(first_char, line);
			ctrld = 1;
			line = strdup(line);
		}
		else
		{
			if (exec_command(line) == STATUS_EXIT)
				status = 0;
			ctrld = 0;
			free(buff);
			free(line);
			line = strdup(" ");
		}
	}
}

int		main(int ac, char **av, char **envv)
{
	init_envv(ac, av, envv);
	system("clear");
	ft_putstr(" \033[31mWelcome\033[0m\033[32mTo\033[0m\033[33m << ");
	ft_putstr("\033[0m\033[34mMinishell\033[0m\033[35m >>\033[0m \n");
	set_env_var("OLDPWD", " ");
	minishell(envv);
	return (EXIT_SUCCESS);
}
