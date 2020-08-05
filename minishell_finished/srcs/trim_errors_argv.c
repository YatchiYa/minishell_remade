
#include "minishell.h"

int	trim_queue(const char *s1, const char *s2)
{
	if (!ft_strcmp(s1, s2))
		return (1);
	return (0);
}

int		is_redir_quote(char *s)
{
	if (trim_queue(s, "<"))
		return (1);
	if (trim_queue(s, ">"))
		return (1);
	if (trim_queue(s, ">>"))
		return (1);
	return (0);
}

int		is_redirections(char **argv)
{
	int i;
	int fredi;

	fredi = 0;
	i = 0;
	while (argv[i])
	{
		if (is_redir_quote(argv[i]))
		{
			fredi++;
			if (fredi == 2)
				return (syntax_error(argv[i], 0));
		}
		else if (fredi == 1 &&
			(trim_queue(argv[i], "|")
			|| trim_queue(argv[i], ";")))
			return (syntax_error(argv[i], 0));
		else
			fredi = 0;
		i++;
	}
	if (i != 0 && is_redir_quote(argv[i - 1]))
		return (syntax_error("newline", 0));
	return (1);
}

int		is_pipe(char **argv)
{
	int fpip;
	int i;

	fpip = 0;
	i = 0;
	while (argv[i])
	{
		if (trim_queue(argv[i], "|"))
		{
			if (i == 0)
				return (syntax_error("|", 0));
			fpip++;
			if (fpip == 2)
				return (syntax_error("|", 0));
		}
		else if (fpip == 1 &&
			(is_redir_quote(argv[i]) || trim_queue(argv[i], ";")))
			return (syntax_error(argv[i], 0));
		else
			fpip = 0;
		i++;
	}
	if (i != 0 && trim_queue(argv[i - 1], "|"))
		return (syntax_error("|", 0));
	return (1);
}

int		is_point_virgule(char **argv)
{
	int i;
	int fsemi;

	i = 0;
	fsemi = 0;
	while (argv[i])
	{
		if (trim_queue(argv[i], ";"))
		{
			if (i == 0)
				return (syntax_error(";", 0));
			fsemi++;
			if (fsemi == 2)
				return (syntax_error(";", 0));
		}
		else
			fsemi = 0;
		i++;
	}
	return (1);
}

