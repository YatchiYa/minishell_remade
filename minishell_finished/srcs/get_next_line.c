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

int			free_all_lines(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (-1);
}

int			is_line(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

int			give_line(char **str, char **line, int ret)
{
	char	*s;
	int		len;

	s = NULL;
	if (!*str || !**str)
	{
		if (!(*line = ft_strdup("\0")))
			return (free_all_lines(str));
	}
	else if ((len = is_line(*str)) >= 0)
	{
		if (!(*line = ft_strsub(*str, 0, len)))
			return (free_all_lines(str));
		if (!(s = ft_strsub(*str, len + 1, ft_strlen(*str) - len + 1)))
			return (free_all_lines(str));
		ret = 1;
	}
	else
	{
		if (!(*line = ft_strsub(*str, 0, ft_strlen(*str))))
			return (free_all_lines(str));
	}
	free_all_lines(str);
	*str = s;
	return (ret);
}

int			get_next_line(int fd, char **line)
{
	char		*str;
	char		buff[BUFFER_SIZE + 1];
	char		*new_str;
	ssize_t		i;

	str = NULL;
	if (!line || fd < 0)
		return (free_all_lines(&str));
	while ((i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[i] = '\0';
		if (!(new_str = ft_strjoin(str, buff)))
			return (free_all_lines(&str));
		free_all_lines(&str);
		str = new_str;
		if (is_line(str) >= 0)
			break ;
	}
	if (i < 0)
		return (free_all_lines(&str));
	return (give_line(&str, line, 0));
}
