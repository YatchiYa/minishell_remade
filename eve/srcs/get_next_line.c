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

int		free_all_lines(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	str = NULL;
	return (-1);
}

int		ft_line_break(char *stock)
{
	while (*stock)
		if (*(stock++) == '\n')
			return (1);
	return (0);
}

void	ft_fill_static(char **stock, char *buff)
{
	char	*to_free;

	to_free = *stock;
	*stock = strdup(buff);
	free(to_free);
	free(buff);
}

int		ft_read_file(char **stock, int fd)
{
	char		*buffer;
	int			ret;

	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)))
	|| read(fd, buffer, 0) < 0)
		return (-1);
	if (*stock == NULL)
		*stock = strdup("");
	while (!ft_line_break(*stock) && (ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		ft_fill_static(stock, ft_strjoin(*stock, buffer));
	}
	free(buffer);
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char		*stock[55];
	int				ret;
	int				i;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > 55 || line == NULL
	|| (ret = ft_read_file(&stock[fd], fd)) < 0)
		return (-1);
	i = 0;
	while (stock[fd][i] != '\n' && stock[fd][i])
		i++;
	*line = ft_strsub(stock[fd], 0, i);
	if ((ret == 0 && ft_strlen(stock[fd]) > ft_strlen(*line)) || ret > 0)
		ret = 1;
	ft_fill_static(&stock[fd],
			ft_strsub(stock[fd], ++i, ft_strlen(stock[fd])));
	if (ret <= 0)
	{
		free(stock[fd]);
		stock[fd] = NULL;
	}
	return (ret);
}
