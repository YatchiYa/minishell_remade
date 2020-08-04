/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:16:29 by wpark             #+#    #+#             */
/*   Updated: 2020/03/05 11:46:56 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
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
