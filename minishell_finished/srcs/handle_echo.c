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
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (i < cnt - 1)
			ft_putstr(" ");
		i++;
	}
}

int			handle_echo(t_cmd *cmd)
{
	int cnt;

	cnt = count_arg(cmd->argv);
	if (cnt > 2 && ft_strcmp_v2(cmd->argv[1], "-n"))
		display_echo(cmd->argv, 2, cnt);
	else
	{
		display_echo(cmd->argv, 1, cnt);
		ft_putstr("\n");
	}
	return (EXIT_SUCCESS);
}
