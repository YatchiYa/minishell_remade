/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarab <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:50:44 by yarab             #+#    #+#             */
/*   Updated: 2020/02/27 18:41:50 by yarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# define BUFFER_SIZE 2048

char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
int				get_next_line(int fd, char **line);
int				ft_line_break(char *stock);
int				ft_read_file(char **stock, int fd);
void			ft_fill_static(char **stock, char *buff);
size_t			ft_strlenx(char *s);

#endif
