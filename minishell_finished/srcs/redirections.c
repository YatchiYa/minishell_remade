/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:13:46 by pray              #+#    #+#             */
/*   Updated: 2020/02/21 14:13:49 by pray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rdir		*new_rdir(char *file, int mode)
{
	t_rdir *new;

	new = malloc(sizeof(t_rdir));
	new->file_io = ft_strdup(file);
	new->file_dup2 = -1;
	new->over_write = mode;
	new->next = NULL;
	return (new);
}

t_rdir		*last_rdir(t_rdir *begin)
{
	while (begin->next)
		begin = begin->next;
	return (begin);
}

t_rdir		*add_rdir(t_rdir *begin, char *file, int mode)
{
	t_rdir *last;

	if (!begin)
		return (new_rdir(file, mode));
	last = last_rdir(begin);
	last->next = new_rdir(file, mode);
	return (begin);
}
