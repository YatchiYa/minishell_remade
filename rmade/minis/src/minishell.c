#include "minishell.h"

en_status			processCmd(char* buffer, char* envp[], int* fds)
{
    char		**argv;
    char		**str;
	int			num;
	en_status	cmdResult;
	
	str = split_commande(buffer);
    argv = splitString(buffer, " \t\n\v\f\r", "\"\'");
	num = wordCount(argv);
    if(num == 0){
        free(argv);
        return STATUS_SUCCESS;
    }

    cmdResult = STATUS_NULL;
	cmdResult = processBuiltinCmd(str, fds);
    if (cmdResult == STATUS_EXIT)
        exit_shell();
    if(cmdResult == STATUS_UNRECOGNIZED)
        cmdResult = processExternalCmd(argv, num, envp, fds);
    free((void**)(argv));
    argv = NULL;
    return cmdResult;
}

en_status           pipeCmds_extend(char **commands, int num)
{
    int newPipe[2];
    int fd[2];
    int i;

    i = -1;
	isPipe = 1;
    while (++i < num - 1)
    {
        fd[0] = newPipe[0];
        pipe(newPipe);
        fd[1] = newPipe[1];
        processCmd(commands[i], g_envv, fd);
        if(i > 0)
            close(fd[0]);
        close(fd[1]);
    }
    fd[0] = newPipe[0];
    fd[1] = 1;
    processCmd(commands[i], g_envv, fd);
    close(fd[0]);
    free(commands);
    commands = 0;
    return STATUS_SUCCESS;
}

en_status           pipeCmds(char* buffer)
{
    char    **commands;
    int     num;
    int     status;

    strReplace(buffer, '\n', 0);
	if (buffer[0] == '"' || buffer[0] == '\'')
		if ((buffer = trim_parse(buffer)) == NULL)
			return STATUS_FAILURE;
    //commands = splitString(buffer, "|", "");
	commands = ft_strsplit(buffer, '|');
    num = wordCount(commands);
    if(num == 0){
        return STATUS_SUCCESS;
    }
    if(num == 1){
        int cmdResult = processCmd(commands[0], g_envv, NULL);
        free(commands);
        commands = 0;
        if (cmdResult == STATUS_SUCCESS)
            set_env_var("?", "0");
        else
            set_env_var("?", "1");
        return cmdResult;
    }
	else
    	return (pipeCmds_extend(commands, num));
}
