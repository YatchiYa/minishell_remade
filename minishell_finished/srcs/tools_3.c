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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != 0)
		len++;
	return (len);
}

void	ft_putstr(char *s)
{
	if (s)
	{
		while (*s != '\0')
			ft_putchar_fd(*s++, 1);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*cpy_ret;

	if (!s1 && !s2)
		return (0);
	ret = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (0);
	cpy_ret = ret;
	if (s1)
		while (*s1 != '\0')
			*cpy_ret++ = *s1++;
	if (s2)
		while (*s2 != '\0')
			*cpy_ret++ = *s2++;
	*cpy_ret = '\0';
	return (ret);
}

char		*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ret;

	if (!s1)
		return (0);
	if (!(ret = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (0);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
