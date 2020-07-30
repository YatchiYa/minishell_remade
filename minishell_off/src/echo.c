#include "minishell.h"

char    *malloc_sortie(int len)
{
    char    *str;

    if (!(str = malloc(sizeof(char) * (len + 1))))
        return (NULL);
    return (str);
}

int		calc_c(char *str, char c)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == c)
			ret++;
		i++;
	}
	return (ret);
}

void	extend(char *str, char c)
{
	int		i;
	char	*line;
	int		back;

	i = 0;
	back = 0;
	while (str[ft_strlenx(str) - 1] != c && calc_c(str, c) % 2 != 0)
	{
		line = NULL;
		ft_putstr("quote > ");
		get_next_line(0, &line);
		str = ft_strjoin(str, "\n");
		str = ft_strjoin(str, line);
	}
	while (str[i])
	{
		i = 0;
		while (str[i] == ' ')
			i++;
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			back = 1;
			i += 2;
		}
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '\"')
			{
				if (str[i] == '$')
				{
					ft_putstr(parse_dollar(&str[i]));
					while (str[i] != ' ' && str[i] && str[i] != '\0')
						i++;
					i--;
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
	}       
    ft_putstr("\n");   
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

int			handle_echo(char *str)
{
	int		i;
	char	*dest;
	int		ret;
	int		xet;
	int		back;

	i = -1;
	dest = malloc_sortie(ft_strlenx(str));
	while (str[++i])
		dest[i] = str[i];
	dest[i] = '\0';
	i = -1;
	ret = 0;
	xet = 0;
	back = 0;
    while (dest[++i])
	{
		if (dest[i] == '"' && xet == 0)
			ret++;
		else if (dest[i] == '\'' && ret == 0)
			xet++;
	}
	if (ret % 2 != 0 && ret != 0)
	{
		ft_putstr("minishell > parse error quote \n");
		return (1);
	}
	else if (xet % 2 != 0 && xet != 0)
	{
		ft_putstr("minishell > parse error quote \n");
		return (1);
	}
	else if ((ssx(dest, ">|<") == 1) && (search_delim(dest, '"', ret) == 1))
	{
		return (handle_redirect_echo(dest));
	}
	else if (str[ft_strlenx(str) - 2] == '\\' && (str[ft_strlenx(str) - 1] == '"' || str[ft_strlenx(str) - 1] == '\''))
	{
		ft_putstr("sytanx error\n");
		return (1);
	}
	else
	{
		i = 0;
		while (str[i] == ' ')
			i++;
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			back = 1;
			i += 2;
		}
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '\"')
			{
				if (str[i] == '$')
				{
					ft_putstr(parse_dollar(&str[i]));
					while (str[i] != ' ' && str[i] && str[i] != '\0')
						i++;
					i--;
				}
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
	}
	return (0);
}

en_status           bultinECHO(char   **words)
{
    int rval = handle_echo(words[1]);
    if(rval == 0)
        return STATUS_SUCCESS;
    return STATUS_SOFT_FAILURE;
}