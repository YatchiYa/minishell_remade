/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarab <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 19:31:22 by yarab             #+#    #+#             */
/*   Updated: 2020/02/28 19:31:25 by yarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		signal_handler_main(void)
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
	line = trim_start(line);
	if (check_error(line) == 0 || check_error_2(line) == 0)
	{
		printf("minishell : syntax error \n");
		return (1);
	}
	if (line[0] == '>')
		line = ft_strjoin("cat ", line);
	else if (line[0] == '<')
		line = ft_strjoin("less ", line);
	line = ft_substr(line, 0, ft_strlenx(line) - 1);
	tab = ft_strsplit(line, ';');
	ret = -1;
	while (tab[++ret])
		status = pipeCmds(tab[ret]);
	free((void**)(tab));
	tab = NULL;
	return (status);
}

int			minishell_extend(char *line, char *buff, char *first_char)
{
	int		status;

	status = 1;
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
		ctrlc = 0;
		free(buff);
		free(line);
		line = strdup(" ");
	}
	return (status);
}

void		minishell(char **envv)
{
	char		*line;
	char		*buff;
	int			ret;
	char		*first_char;
	int			status;

	status = 1;
	while (status)
	{
		buff = NULL;
		line = strdup(" ");
		isPipe = 0;
		if (ctrld == 0 && ctrlc == 0)
			display_prompt_msg();
		signal_handler_main();
		ret = get_next_line(0, &buff);
		line = ft_strjoin(line, buff);
		line = ft_substr(line, 1, ft_strlenx(line));
		status = minishell_extend(line, buff, first_char);
	}
	free(line);
}

int			main(int ac, char **av, char **envv)
{
	init_envv(ac, av, envv);
	system("clear");
	ft_putstr(" \033[31mWelcome\033[0m\033[32mTo\033[0m\033[33m << ");
	ft_putstr("\033[0m\033[34mMinishell\033[0m\033[35m >>\033[0m \n");
	set_env_var("OLDPWD", " ");
	minishell(envv);
	return (EXIT_SUCCESS);
}
