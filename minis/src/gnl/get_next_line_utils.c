/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yarab <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:50:33 by yarab             #+#    #+#             */
/*   Updated: 2020/02/27 18:41:21 by yarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strlenx(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char			*ft_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	size_t	s1_len;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlenx(s1) + ft_strlenx(s2);
	s1_len = ft_strlenx(s1);
	if (!(str = malloc(sizeof(char) * (total_len + 1))))
		return (NULL);
	i = 0;
	while (i < total_len)
	{
		str[i] = (i < s1_len) ? s1[i] : s2[i - s1_len];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (!s || !(substr = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len && s[i + start] && !(start > ft_strlenx(s)))
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
