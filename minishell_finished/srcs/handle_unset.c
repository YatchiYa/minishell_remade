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

void		remove_data(char *key)
{
	t_env *prev;
	t_env *tmp;
	t_env *next;

	prev = 0;
	tmp = get_minish()->env;
	while (tmp)
	{
		next = tmp->next;
		if (ft_strcmp_v2(tmp->key, key))
		{
			if (prev)
				prev->next = next;
			else
				get_minish()->env = next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = next;
	}
}

int			handle_unset(t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd->argv[i])
	{
		remove_data(cmd->argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
