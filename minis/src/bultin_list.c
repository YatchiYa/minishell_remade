#include "minishell.h"

en_status           bultinCD(char   **words)
{
	char	**tmp;

	if (words[1] == NULL)
	{
		cd_handle_home();
        return STATUS_SUCCESS;
	}
	tmp = ft_strsplit(words[1], ' ');
    if (tmp[1] != NULL)
    {
        ft_putstr("minishell > too many arguments \n");
        return STATUS_SOFT_FAILURE;
    }
    int rval = handle_cd(tmp[0]);
    if(rval == 0)
        return STATUS_SUCCESS;
    return STATUS_SOFT_FAILURE;
}

en_status           bultinECHO(char   **words)
{
    int rval = handle_echo(words[1]);
    if(rval == 0)
        return STATUS_SUCCESS;
    return STATUS_SOFT_FAILURE;
}