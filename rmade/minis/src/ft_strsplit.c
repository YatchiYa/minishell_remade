#include "minishell.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	sub = ft_memalloc(len + 1);
	if (sub)
		memcpy(sub, s + start, len);
	return (sub);
}

static int	count_words(char *s, char c)
{
	int	words;
	int	ret;
	int	xet;

	words = 0;
	ret = 0;
	xet = 0;
	while (*s && *s == c)
		++s;
	if (*s)
		words = 1;
	while (*s)
	{
		if (*s == '"')
			ret++;
		if (*s == '\'')
			xet++;
		if (*s == c && s[1] && s[1] != c && ret % 2 == 0)
			++words;
		++s;
	}
	return (words);
}

char		**ft_strsplit(char const *s, char c)
{
	int		words;
	char	*start;
	char	**result;
	int		ret = 0;
	int		xet = 0;

	words = count_words((char *)s, c);
	if (!s || !c)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	start = (char *)s;
	while (*s)
	{
		if (*s == '"')
			ret++;
		if (*s == '\'')
			xet++;
		if (*s == c && ret % 2 == 0 && xet % 2 == 0)
		{
			if (start != s)
				*(result++) = ft_strsub(start, 0, s - start);
			start = (char *)s + 1;
			ret = 0;
			xet = 0;
		}
		++s;
	}
	if (start != s)
		*(result++) = ft_strsub(start, 0, s - start);
	*result = NULL;
	return (result - words);
}