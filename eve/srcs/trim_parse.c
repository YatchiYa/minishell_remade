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

int		trim_backslash(char *line, int *i, char quote)
{
	if (!line[*i])
		return (0);
	if (line[*i] == '\\')
		++*i;
	else if (line[*i] == quote)
		return (0);
	return (1);
}

int		trim_quote(char *line, int i)
{
	if (line[i] == '\"' && (i == 0 || (line[i - 1] != '\\'
				&& line[i - 2] != '\\')))
	{
		i++;
		while (trim_backslash(line, &i, '\"'))
			i++;
		if (line[i] == '\0')
		{
			ft_putstr("QUOTES DXDD NEED TO BE CLOSE\n");
			return (-1);
		}
	}
	else if (line[i] == '\'' && (i == 0 || (line[i - 1] != '\\'
				&& line[i - 2] != '\\')))
	{
		i++;
		while (line[i] != '\'' && line[i])
			i++;
		if (line[i] == '\0')
		{
			ft_putstr("QUOTES ZZ NEED TO BE CLOSE\n");
			return (-1);
		}
	}
	return (i);
}

int		check_sep(char *line, int i, int use)
{
	int ret;

	if (line[i] == ' ' || line[i] == '\t')
		ret = 1;
	else if (line[i] == '>' && line[i + 1] == '>')
		ret = 2;
	else if (line[i] == '>')
		ret = 1;
	else if (line[i] == '<')
		ret = 1;
	else if (line[i] == '|')
		ret = 1;
	else if (line[i] == ';')
		ret = 1;
	else
		return (0);
	if (use == 1)
		return (ret);
	else if (use == 2)
		return (trim_space(line, i, ret));
	return (0);
}

int		ft_is_sep_space(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		word_str_count(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (!ft_is_sep_space(SEP_SPACE, line[i]) && line[i])
		{
			count++;
			while (!ft_is_sep_space(SEP_SPACE, line[i]) && line[i])
			{
				if ((i = trim_quote_2(line, i)) == -1)
					return (0);
				if (trim_backslash_2(line, &i) == 0)
					return (0);
				i++;
			}
		}
		if (ft_is_sep_space(SEP, line[i]))
			count++;
		i += check_sep(line, i, 2);
	}
	return (count);
}
