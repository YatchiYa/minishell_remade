/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarab <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:13:46 by yarab             #+#    #+#             */
/*   Updated: 2020/02/21 14:13:49 by yarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		display_echo(char **argv, int i, int cnt)
{
	get_minish()->comment_found = 0;
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (i < cnt - 1)
			ft_putstr(" ");
		i++;
	}
}

int			spec_check_only_n(char *str)
{
	unsigned int		i;

	if (str[0] != '-')
		return (0);
	else if (str[0] == '-' && str[1] && str[1] != 'n')
		return (0);
	else if (str[0] == '-' && str[1])
	{
		i = 1;
		while (str[i] == 'n')
			i++;
		if (i == ft_strlen(str))
			return (1);
		else
			return (0);
	}
	return (0);
}

int			index_echo_display(char **argv, int i)
{
	while (argv[i] && spec_check_only_n(argv[i]) == 1)
		i++;
	return (i);
}

int			handle_echo(t_cmd *cmd)
{
	int cnt;
	int	index;

	cnt = count_arg(cmd->argv);
	if (cnt >= 2 && spec_check_only_n(cmd->argv[1]) != 0)
	{
		index = index_echo_display(cmd->argv, 1);
		display_echo(cmd->argv, index, cnt);
	}
	else
	{
		display_echo(cmd->argv, 1, cnt);
		ft_putstr("\n");
	}
	return (EXIT_SUCCESS);
}
