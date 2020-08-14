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

char			*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *ptr;
	char *ret;
	char *cpy_ret;

	if (!s || !(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	if (start > ft_strlen(s))
		ret[0] = '\0';
	else
	{
		ptr = (char *)s + start;
		cpy_ret = ret;
		while (*ptr && len-- > 0)
			*cpy_ret++ = *ptr++;
		*cpy_ret = '\0';
	}
	return (ret);
}

int				ft_atoi(const char *str)
{
	char	*s;
	int		sign;
	int		n;

	s = (char*)str;
	sign = 1;
	n = 0;
	while (*s == ' ' || *s == '\t'
			|| *s == '\n' || *s == '\r' || *s == '\v' || *s == '\f')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		n = n * 10 + (*s++ - '0');
	return (sign * n);
}

unsigned int	count_digit(unsigned int n)
{
	unsigned int	cnt;

	cnt = 0;
	while (n >= 10)
	{
		n = n / 10;
		cnt++;
	}
	return (cnt + 1);
}

void			assign_num(unsigned int num, char *ptr)
{
	*ptr-- = '\0';
	if (num == 0)
		*ptr = '0';
	while (num)
	{
		*ptr-- = (num % 10) + '0';
		num = num / 10;
	}
}

char			*ft_itoa(int n)
{
	char			*ret;
	unsigned int	cnt;
	unsigned int	sign;
	unsigned int	num;

	num = (n < 0) ? -n : n;
	sign = (n < 0) ? 1 : 0;
	cnt = count_digit(num);
	if (!(ret = (char*)malloc(sizeof(char) * (cnt + sign + 1))))
		return (0);
	if (sign == 1 && (*ret = '-'))
		assign_num(num, ret + cnt + 1);
	else
		assign_num(num, ret + cnt);
	return (ret);
}
