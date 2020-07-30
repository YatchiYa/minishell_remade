
#include "minishell.h"

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
	if (!(dest[0] = malloc(sizeof(char) * 10)))
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
    while (*line == ' ')
        ++line;
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
    assert(str);
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
    assert(words);
    int count = 0;
    while(words[count]){
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