#include "minishell.h"

char    *malloc_sortie(int len)
{
    char    *str;

    if (!(str = malloc(sizeof(char) * (len + 1))))
        return (NULL);
    return (str);
}

int		hand_back_slash(char *str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	str[i + 1] == 'n' ? ft_putstr("\n") : 0;
	str[i + 1] == 't' ? ft_putstr("    ") : 0;
	while (str[i] == '\\')
	{
		ret++;
		if (ret == 3)
		{
			write(1, &str[i], 1);
			return (2);
		}
		i++;
	}
	if (ret == 2)
		return (1 + hand_back_slash(&str[i - 1]));
	return (1);
}

int		handl_echo_ext(char *str, int back, int ret, int xet)
{
	int		i;

	i = 0;
	while (*str == ' ')
		++str;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		back = 1;
		i += 2;
	}
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			if (str[i] == '$' && xet == 0)
			{
				ft_putstr(parse_dollar(&str[i]));
				while (str[i] != ' ' && str[i] && str[i] != '\0')
					i++;
				i--;
			}
			else if (strcmp("'\\'", str) == 0)
				ft_putstr("\\");
			else if (str[i] == '\\')
			{
				i += hand_back_slash(&str[i]);
			}
			else
				write(1, &str[i], 1);
		}
		i++;
	}
	if (back == 1)
		;
	else
		ft_putstr("\n");
	return (0);
}

int			handle_echo(char *str)
{
	int		i;
	char	*dest;
	int		ret;
	int		xet;
	int		back;

	if (str == NULL)
	{
		ft_putstr("\n");
		return (0);
	}
	dest = trim_quote(str, &ret, &xet);
	if (ret % 2 != 0 && ret != 0)
	{
		ft_putstr("minishell > error parse quote \n");
		return (1);
	}
	else if (xet % 2 != 0 && xet != 0)
	{
		ft_putstr("minishell > error parse quote \n");
		return (1);
	}
	else if ((ssx(dest, ">|<") == 1) && (search_delim(dest, '"', ret) == 1))
	{
		return (handle_redirect_echo(dest));
	}
	else if (str[ft_strlenx(str) - 2] == '\\' && (str[ft_strlenx(str) - 1] == '"'))
	{
		ft_putstr("sytanx error\n");
		return (1);
	}
	else
		return(handl_echo_ext(str, back, ret, xet));
	return (0);
}
