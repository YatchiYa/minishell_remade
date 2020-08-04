/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_white_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 10:31:46 by froussel          #+#    #+#             */
/*   Updated: 2020/03/05 10:32:10 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	conv_white_space(char c)
{
	if (c == ' ')
		return (' ');
	else if (c == 't')
		return ('\t');
	else if (c == 'n')
		return ('\n');
	else if (c == 'r')
		return ('\r');
	else if (c == 'v')
		return ('\v');
	return (c);
}
