/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pray <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:13:46 by pray             #+#    #+#             */
/*   Updated: 2020/02/21 14:13:49 by pray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minish	*get_minish(void)
{
	static t_minish	minish;

	return (&minish);
}

void		free_all(void)
{
	free_1();
	free_env();
}

void		prompt_msg(void)
{
	if (get_minish()->is_end_of_file == 0)
		ft_putstr("\033[32mMINISHELL\033[0m$ ");
}

void		signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (get_minish()->cmd_is_ok == 1)
		{
			ft_putstr("\n");
			get_minish()->cmd_is_ok = 0;
		}
		else
		{
			ft_putstr("\n");
			get_minish()->is_end_of_file = 0;
			prompt_msg();
			get_minish()->signal_is_called = 1;
		}
	}
	else if (signo == SIGQUIT)
	{
		if (get_minish()->cmd_is_ok == 1)
		{
			ft_putstr("Quit (core dumped)\n");
			get_minish()->cmd_is_ok = 0;
		}
	}
}

int			main(int ac, char **av, char **env)
{
	init_env(env);
	system("clear");
	ft_putstr(" \033[31mWelcome\033[0m\033[32mTo\033[0m\033[33m << ");
	ft_putstr("\033[0m\033[34mMinishell\033[0m\033[35m >>\033[0m \n");
	add_data("OLDPWD", NULL);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		display_prompt_msg();
		if (!ft_getline())
			continue ;
		if (!init_cmd(get_minish()->argv))
		{
			free_1();
			continue ;
		}
		exec_command();
		free_1();
	}
	return (0);
}
