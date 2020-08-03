
#include "minishell.h"

char	*ft_strdupxx(char *src)
{
	char	*dest;
	int		src_len;
	int		i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (!(dest = (char *)malloc(sizeof(char) * (src_len + 1))))
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


char		**trim_arg(char **argv, int index)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	if (argv == NULL || argv[i] == NULL)
		return (NULL);
	tmp = (char**)malloc(sizeof(char *) * (wordCount(argv) + 1));
	while (argv && argv[i])
	{
		if (i == index && i != 0)
			i = i + 2;
		if (argv[i])
		{
			tmp[j] = ft_strdupxx(argv[i]);
			j++;
			i++;
		}
	}
	tmp[j] = NULL;

	return (tmp);
}

char		**sub_argv(char **argv)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (char**)malloc(sizeof(char *) * (wordCount(argv) + 1));
	while (argv[i] && strcmp(argv[i], ">") != 0 && strcmp(argv[i], "<") != 0 &&
			strcmp(argv[i], ">>") != 0)
	{
		tmp[i] = strdup(argv[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

int			redirect_index(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], "<") == 0 || 
			(argv[i + 1] && strcmp(argv[i], ">>") == 0))
			return (i);
		i++;
	}
	return (0);
}

int			redirect_index_output(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (strcmp(argv[i], ">") == 0 || 
			(argv[i + 1] && strcmp(argv[i], ">>") == 0))
			return (i);
		i++;
	}
	return (0);
}

int			redirect_index_input(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (strcmp(argv[i], "<") == 0)
			return (i);
		i++;
	}
	return (0);
}

void	display_argv(char **argv)
{
	int		i;

	i = 0;
	while (argv && argv[i])
	{
		printf("argv[%d] = [%s]\n", i, argv[i]);
		i++;
	}
}

int	search_delim(char *str, char c, int n)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] && ss(str[i], ">|<") == 0)
	{
		if (str[i] == c)
			res++;
		i++;
	}
	if (res != n)
		return (0);
	return (1);
}

char	*delim_ptr(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '>' && str[i] != '<')
		i++;
	return (&str[i]);
}

char	*ft_strchrx(char *s, char c)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

int		check_is_sep(char *str)
{
	int		i;

	i = 0;
	while (SEP[i])
	{
		if (SEP[i] == str[0])
			return (0);
		i++;
	}
	return (1);
	
}

int		check_error(char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';' && str[i + 1] && str[i + 1] == ';')
		{
			ft_putstr("minishell > syntax error ;;\n");
			return (0);
		}
		i++;
	}
	i = 0;
	tmp = ft_strsplit(str, ' ');
	while (tmp[i] && tmp[i + 1])
	{
		if (check_is_sep(tmp[i]) == 0 && check_is_sep(tmp[i + 1]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		check_error_2(char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_strsplit(str, ' ');
	if (strcmp(tmp[0], "|") == 0 || tmp[wordCount(tmp) - 1][0] == '|')
	{
		ft_putstr("minishell : error parse pipe\n");
		return (0);
	}
	return (1);
}

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	if (!n)
		return ;
	ptr = s;
	i = 0;
	while (i < n)
		*(ptr + i++) = 0;
}

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = malloc(size)))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = -1;
	while (++i < (int)strlen(s) + 1)
		if (*(s + i) == (char)c)
			return ((char *)s + i);
	return (NULL);
}

int		ft_strstartswith(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

char	*ft_strjoinch(char const *s1, char c)
{
	char	*new_str;
	size_t	i;
	size_t	s1_len;

	if (!s1 || !c)
		return (NULL);
	s1_len = strlen(s1);
	new_str = ft_strnew(s1_len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	*(new_str + i) = c;
	return (new_str);
}

char	**split_commande(char *line)
{
	int		i;
	char	**dest;

	if (!(dest = (char**)malloc(sizeof(char*) * 3)))
		return (NULL);
	if (!(dest[0] = malloc(sizeof(char) * (ft_strlenx(line) + 1))))
		return (NULL);
	i = -1;
    dest[3] = NULL;
	while (line[++i] != ' ' && line[i])
		dest[0][i] = line[i];
	dest[0][i] = '\0';
    if (line[i] == '\0')
    {
        dest[1] = NULL;
        return (dest);
    }
	if (!(dest[1] = malloc(sizeof(char) * (ft_strlenx(line) + 1))))
		return (NULL);
	line = line + i;
    //while (*line == ' ')
    //    ++line;
	i = -1;
	while (line[++i])
		dest[1][i] = line[i];
	dest[1][i] =  '\0';
	return (dest);
}

int		only_point(char *str)
{
	int		i;

	i = 0;
	while (str[i] == '.')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int		strcontains(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}


int strReplace(char* str, char match, char replace){
    //assert(str);
    int count = 0;
    for(int i = 0; str[i] != 0; ++i){
        if (str[i] == match) {
            str[i] = replace;
            ++count;
        }
    }
    return count;
}
void ** freeArray(void ** pointerArray){
    if(!pointerArray){
        return NULL;
    }
    for( int i = 0; pointerArray[i] != 0; ++i){
        free(pointerArray[i]);
        pointerArray[i] = NULL;
    }
    free(pointerArray);
    pointerArray = NULL;
    return pointerArray;
}
char** strcpyArray(char** strings){
    assert(strings);
    int count = 0;
    while(strings[count++]);
    char** newArray = malloc(sizeof(char*)*count);
    count = 0;
    while(strings[count]){
        newArray[count] = malloc(sizeof(char)*(1+strlen(strings[count])));
        strcpy(newArray[count], strings[count]);
        ++count;
    }
    newArray[count] = 0;
    return newArray;
}
int wordCount(char** words){
    //assert(words);
    int count = 0;
    while(words[count])
	{
        ++count;
    }
    return count;
}
int indexOf(char* str, const char* chars){
    for(int i = 0; str[i] != 0; ++i){
        for(int j = 0; chars[j] != 0; ++j){
            if(str[i] == chars[j])
                return i;
        }
    }
    return -1;
}
void printStrings(char** strs){
    int index = 0;
    if(strs != NULL){
        for(index = 0; strs[index] != NULL; ++index){
            if(index == 0){
                printf("Strings:");
            }else{
                printf(",");
            }
            printf("'%s'", strs[index]);
        }
    }
    if(index == 0){
        printf("No strings");
    }
    printf("\n");
}
char** splitString(char* buffer, const char* sep, const char* substrsyms){
    assert(buffer);
    assert(sep);

    const int MAX_TOKENS = 25;
    char* tokens[MAX_TOKENS+1];
    int index = 0;

    // Parse string, saved tokens point directly to buffer:
    char* token = strtok(buffer, sep);
    const char SINGLE_QUOTE[] = "\'";
    const char DOUBLE_QUOTE[] = "\"";

    while(token && index < MAX_TOKENS){
        if(token[0] == SINGLE_QUOTE[0]){
            token[strlen(token)] = ' ';
            token = strtok(token, SINGLE_QUOTE);
        }else if(token[0] == DOUBLE_QUOTE[0]){
            token[strlen(token)] = ' ';
            token = strtok(token, DOUBLE_QUOTE);
        }
        tokens[index++] = token;
        token = strtok(NULL, sep);
    }
    tokens[index++] = NULL; // NULL terminated array

    // Allocate array of cstrings:
    char** returnTokens = malloc(sizeof(char*)*index);

    // Copy pointers, not content:
    index = 0;
    while(tokens[index]){
        returnTokens[index] = tokens[index];
        ++index;
    }
    returnTokens[index] = NULL; // NULL terminated array
    return returnTokens;
}

char        *trim_queue(char *str)
{
    char    *tmp;
    int     i;

    i = -1;
	tmp = malloc(sizeof(char) * (ft_strlenx(str) + 1));
	while (str[i] && str[++i] != ' ')
		tmp[i] = str[i];
	tmp[i] = '\0';
	return (tmp);
}

char        *trim_start(char *str)
{
    char    *tmp;
    int     i;
	int		j;

    i = 0;
	tmp = malloc(sizeof(char) * (ft_strlenx(str) + 1));
	while (str[i] && str[i] == ' ')
		i++;
	j = 0;
	while (str[i])
	{
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}