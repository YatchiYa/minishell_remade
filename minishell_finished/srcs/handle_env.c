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

void		printenv(t_env *env)
{
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr(env->key);
			ft_putstr("=");
			ft_putstr(env->value);
			ft_putstr("\n");
		}
		env = env->next;
	}
}

int			handle_env(t_cmd *cmd)
{
	(void)cmd;
	printenv(get_minish()->env);
	return (EXIT_SUCCESS);
}
