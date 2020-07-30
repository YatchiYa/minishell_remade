#include "minishell.h"

void	extendx(char *str, char c)
{
	int		i;
	char	*line;

	i = 0;
	while (str[ft_strlenx(str) - 1] != c && calc_c(str, c) % 2 != 0)
	{
		line = NULL;
		ft_putstr("quote > ");
		get_next_line(0, &line);
		str = ft_strjoin(str, "\\n");
		str = ft_strjoin(str, line);
	}
    ft_putstr("Minishell : commande not found");   
    ft_putstr(str);
    ft_putstr("\n");
}

char		*trim_str(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlenx(str + 1)));

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] != '"' && str[j] != '\'')
		{
			tmp[i] = str[j];
			i++;
		}
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char		*trim_parse_ex(char *dest, char *str)
{
	char	**tab;
	
	tab = split_commande(dest);
	if (((tab[0][0] == '"' || tab[0][0] == '\'') && (tab[0][1] == ' ' || tab[0][1] == '\0'))
		|| ((tab[0][ft_strlenx(tab[0])] == '"' || tab[0][ft_strlenx(tab[0])] == '\'') && (tab[0][ft_strlenx(tab[0]) - 1] == ' ' || tab[0][ft_strlenx(tab[0]) - 1] == '\0')))
	{
		ft_putstr("command error :");   
		ft_putstr(tab[0]);
		return (NULL);
	}
	else
	{
		char *tmp = trim_str(tab[0]);
		char *tmp2 = trim_str(tab[1]);
		str = ft_strjoin(tmp, tmp2);
		return (str);
	}
}

char	*trim_parse(char *str)
{
    char	*dest;
    int		ret;
	int		xet;
	
	dest = trim_quote(str, &ret, &xet);
	if (ret % 2 != 0 && ret != 0)
	{
		printf("minishell > erreor quote parse \n");
		return (NULL);
	}
	else if (xet % 2 != 0 && xet != 0)
	{
		printf("minishell > erreor quote parse \n");
		return (NULL);
	}
	else
		return (trim_parse_ex(dest, str));
}
