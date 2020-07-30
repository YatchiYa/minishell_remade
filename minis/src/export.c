#include "minishell.h"

void		handle_export(char *str)
{
	int		i;
	int		err;
	char	**tab;
	char	**container;
	int		j;

	while (*str == ' ')
		str++;
	container = ft_strsplit(str, ' ');
	j = 0;
	while (container[j])
	{
		tab = ft_strsplit(container[j], '=');
		j++;
		if (tab[1])
		{
			i = 0;
			err = 0;
			while(tab[0][i])
			{
				if (tab[0][i] == ' ')
					err = 1;
				i++;
			}
			if (tab[1][0] == ' ')
				err = 1;
			if (err == 0)
				set_env_var(tab[0], tab[1]);
			else
				ft_putstr("error : NOM=VALUE \n");
		}
		else
		{
			i = 0;
			err = 0;
			while (tab[0][i])
			{
				if (tab[0][i] == '=' && tab[0][i - 1] == ' ')
					err = 1;
				i++;
			}
			if (err == 0)
				set_env_var(tab[0], " ");
			else
				ft_putstr("error : space befor = \n");
		}
	}
	
}
