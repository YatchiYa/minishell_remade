#include "minishell.h"

int				handle_redirect_setenv_ext(char **container, int j)
{
	int		fd;

	if (strcmp(container[j], ">")  == 0)
		if (container[(j) + 1] == NULL)
			return (-1);
		else
		{	
			fd = open(container[j + 1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
			return (2);
		}
	if (strcmp(container[j], "<")  == 0)
		if (container[j + 1] == NULL)
			return (-1);
		else
		{
			fd = open(container[j + 1], O_RDWR);
			if (fd == -1)
				return (-1);
			return (2);
		}
	if (container[j][0] > '0' && container[j][0] < '9')
		return (1);
	return (0);
}

char			*trim_case(char *str)
{
	int		i;
	int		j;
	int		ret;
	int		xet;
	char	*dest;

	dest = trim_quote(str, &ret, &xet);
	if (ret % 2 != 0 && ret != 0)
	{
		ft_putstr("minishell > error parse quote \n");
		return (NULL);
	}
	else if (xet % 2 != 0 && xet != 0)
	{
		ft_putstr("minishell > error parse quote \n");
		return (NULL);
	}
	else
	{
		i = 0;
		while (str[i])
		{
			if ((str[i] == '"' || str[i] == '\'') && str[i + 1] && str[i + 1] == ' ')
				return (NULL);
			i++;
		}
		j = -1;
		i = -1;
		while (str[++i])
			if (str[i] != '"' && str[i] != '\'')
				dest[++j] = str[i];
		dest[++j] = '\0';
		return (dest);
	}
}

int				handle_export(char *str)
{
	char	**tab;
	char	**container;
	int		j;
	int		fd;
	int		res;

	while (str && *str == ' ')
		str++;
	if (str == NULL)
	{
		print_env();
		return (0);
	}
	container = ft_strsplit(str, ' ');
	j = 0;
	while (container[j])
	{
		res = 0;
		if (container[j] && (res = handle_redirect_setenv_ext(container, j)) == -1)
		{
			ft_putstr("minishell > error either redirection false or file doesn't exist or ident is numeric \n");
			return (1);
		}
		j += res;
		if (container[j] && (container[j] = trim_case(container[j])) == NULL)
		{
			ft_putstr("minishell > error parsing quotes\n");
			return (1);
		}
		if (container[j] != NULL)
		{
			tab = ft_strsplit(container[j], '=');
			set_env_var(tab[0], tab[1]);
			j++;
		}
	}
	return (0);
	
}

en_status           bultinSETENV(char   **words)
{
    int rval;
	
	rval = handle_export(words[1]);
    if(rval == 0)
        return STATUS_SUCCESS;
    return STATUS_SOFT_FAILURE;
}