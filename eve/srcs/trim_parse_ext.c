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

int		trim_space(char *line, int i, int jmp)
{
	i += jmp;
	while (line[i] == ' ' || line[i] == '\t')
	{
		i++;
		jmp++;
	}
	return (jmp);
}

int		trim_comment(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
			return (i);
		i++;
	}
	return (-1);
}

int		trim_backslash_2(char *line, int *i)
{
	if (!line[*i])
		return (0);
	if (line[*i] == '\\')
		++*i;
	if (line[*i] == '\0')
	{
		ft_putstr("QUOTES BB NEED TO BE CLOSE\n");
		return (0);
	}
	return (1);
}

int		exttt(char *line, int i)
{
	if (line[i] == '\'' && line[i - 1] && line[i - 1] == '\\')
	{
		i++;
		while (line[i] != '\'' && line[i])
			i++;
		if (line[i] == '\0')
		{
			ft_putstr("QUOTES NEED TO BE CLOSE\n");
			return (-1);
		}
	}
	else if (line[i] == '"' && line[i - 1] && line[i - 1] == '\\')
	{
		i++;
		while (line[i] != '"' && line[i])
			i++;
		if (line[i] == '\0')
		{
			ft_putstr("QUOTES NEED TO BE CLOSE\n");
			return (-1);
		}
	}
	return (i);
}

int		trim_quote_2(char *line, int i)
{
	if (line[i] == '\"' && (i == 0 || line[i - 1] != '\\'))
	{
		i++;
		while (trim_backslash(line, &i, '\"'))
			i++;
		if (line[i] == '\0')
		{
			ft_putstr("QUOTES XXXX NEED TO BE CLOSE\n");
			return (-1);
		}
	}
	else if (line[i] == '\'' && (i == 0 || line[i - 1] != '\\'))
	{
		i++;
		while (line[i] != '\'' && line[i])
			i++;
		if (line[i] == '\0')
		{
			ft_putstr("QUOTES NEED TO BE CLOSE\n");
			return (-1);
		}
	}
	else
		return (exttt(line, i));
	return (i);
}
