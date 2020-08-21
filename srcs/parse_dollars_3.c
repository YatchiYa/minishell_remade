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

int			parse_home(char *argv, char *buff, int *j)
{
	char	*value;

	value = find_env("HOME");
	if (ft_strcmp(argv, "~") == 0)
	{
		*j = ft_strlcat(buff, value, LINE_MAX) - 1;
		free(buff);
		return (ft_strlen(argv) - 1);
	}
	else if (ft_strcmp(argv, "~/") == 0)
	{
		*j = ft_strlcat(buff, value, LINE_MAX) - 1;
		free(buff);
		return (ft_strlen(argv) - 1);
	}
	else
	{
		value = ft_strdup("~");
		*j = ft_strlcat(buff, value, LINE_MAX) - 1;
		free(value);
		return (0);
	}
}
