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
	int		i;
	char	*value;

	i = 0;
	value = find_env("HOME");
	if (argv[0] == '~' && (argv[1] == ' ' || argv[1] == '\0'))
	{
		*j = ft_strlcat(buff, value, LINE_MAX) - 1;
		return (1);
	}
	else if (argv[i] == '~' && argv[1] && argv[i + 1] == '/'
		&& (argv[2] == ' ' || argv[2] == '\0'))
	{
		*j = ft_strlcat(buff, value, LINE_MAX) - 1;
		return (1);
	}
	else
		return (0);
}
