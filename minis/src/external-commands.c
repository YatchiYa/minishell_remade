#include "minishell.h"

char        **dup_arg(char **argv)
{
    int         i;
    char        **tmp_argv;

    i = 0;
	tmp_argv = (char**)malloc(sizeof(argv));
	while (argv[i])
	{
		tmp_argv[i] = strdup(argv[i]);
		i++;
	}
	tmp_argv[i] = NULL;
    return (tmp_argv);
}

en_status			fdx_redirect_left(char	**argv, int index_input)
{
	int	fdxx;

	if (argv[index_input + 1] == NULL)
	{
		ft_putstr("minishell > eror file not defined\n");
		return (STATUS_FAILURE);
	}
	fdxx = open(argv[index_input + 1], O_RDWR);
	if (fdxx == -1)
	{
		printf("minishell : error opening file \n");
		return (0);
	}
	if (dup2(fdxx, 0) == -1)
		perror("dupp 1 ");
	return (STATUS_SUCCESS);
}

en_status			fdx_redirect_right(char	**argv, int index_output)
{
	int		fdx;

	if (argv[index_output + 1] == NULL)
	{
		ft_putstr("minishell > eror file not defined\n");
		return (STATUS_FAILURE);
	}
	while (argv[index_output])
	{
		if (strcmp(argv[index_output], ">>") == 0 && argv[index_output + 1])
		{
			fdx = open(argv[index_output + 1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR
												| S_IRGRP | S_IWGRP | S_IWUSR);
		}
		if (strcmp(argv[index_output], ">") == 0 && argv[index_output + 1])
		{
			remove(argv[index_output + 1]);
			fdx = open(argv[index_output + 1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
		}
		index_output++;
	}
	if (dup2(fdx, 1) == -1)
		perror("dupp 1 ");
	return (STATUS_SUCCESS);
}

en_status			fdx_redirect_right_2(char	**argv, int index_output)
{
	int		fdx;

	if (argv[index_output + 1] == NULL)
	{
		ft_putstr("minishell > eror file not defined\n");
		return (STATUS_FAILURE);
	}
	while (argv[index_output])
	{
		if (strcmp(argv[index_output], ">") == 0 && argv[index_output + 1])
		{
			remove(argv[index_output + 1]);
			fdx = open(argv[index_output + 1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
		}
		else if (strcmp(argv[index_output], ">>") == 0 && argv[index_output + 1])
		{
			fdx = open(argv[index_output + 1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR
												| S_IRGRP | S_IWGRP | S_IWUSR);
		}
		index_output++;
	}
	if (dup2(fdx, 1) == -1)
		perror("dupp 1 ");
	return (STATUS_SUCCESS);
}

char            **redirect_arg(char **tmp_argv, char **argv, int index, int index_input, int index_output)
{
    int     fdx;
    int     fdxx;
	int		is_output;

	is_output = 0;
    if (argv && (index) != 0)
		{
			if (index_input != 0 && strcmp(argv[index_input], "<") == 0)
			{
				if (fdx_redirect_left(argv, index_input) == STATUS_FAILURE)
					return (STATUS_FAILURE);	
			}
			if (index_output != 0 && strcmp(argv[index_output], ">>") == 0)
			{
				if (fdx_redirect_right_2(argv, index_output) == STATUS_FAILURE)
					return (STATUS_FAILURE);
			}
			if (index_output != 0 && strcmp(argv[index_output], ">") == 0)
			{
				if (fdx_redirect_right_2(argv, index_output) == STATUS_FAILURE)
					return (STATUS_FAILURE);
			}

			tmp_argv = sub_argv(argv);
        }
        return (tmp_argv);
}

en_status forkExecWait(char* path, char** argv, int argc, char *envp[], int* fds){
    int     status = 0;
    int     i = 0;
	int		index;
    pid_t   pid = fork();
	char	**tmp_argv;
    int     index_output = 0;
    int     index_input = 0;
    
    tmp_argv = dup_arg(argv);
	index = redirect_index(argv);
	index_output = redirect_index_output(argv);
	index_input = redirect_index_input(argv);
	if(pid == 0){
		// Child:
		if(fds){
			// Redirect input:
			if(fds[0] != 0)
				dup2(fds[0], 0);
			// Redirect output:
			if(fds[1] != 1)
				dup2(fds[1], 1);
		}
		tmp_argv = redirect_arg(tmp_argv, argv, index, index_input, index_output);
		return execve(path, tmp_argv, envp);
	}
	else if(pid > 0)
	{
			// Parent:
		pid_t pid2 = pid;
		pid2 = waitpid(pid, &status, 0);
		char **tmp;
		tmp = trim_arg(argv, index_output);
		int len = wordCount(tmp);
		if (len == 1 || index_output == 0)
			return (parentResult(pid, pid2, status));
        else if (index_output != 0 && len == 3)
			return (parentResult(pid, pid2, status));
		else
			return (processExternalCmd(tmp, len, envp, fds));
	}
	printf("Problem with fork: Returned %i.\n", pid);
	return STATUS_SOFT_FAILURE;
}

bool owner_can_execute(char* path){
    //assert(path);
    struct stat sb;
    int result = stat(path, &sb);
    if(result == 0){
        if(sb.st_mode & S_IXUSR){
            return true;
        }
    }
    return false;
}

en_status get_absolute_from_path(char* name, char* pathOutput){
    // Check for executable directly
    int res = 0;
    res = sprintf(pathOutput, "%s", name);
    //assert(res >= 0);
    if(owner_can_execute(pathOutput)){
        return STATUS_SUCCESS;
    }
    const char* PATH = getenv("PATH");
    char pathVar[MAX_PATH_SIZE];
    strcpy(pathVar, PATH);

    // Parse PATH using strtok
    char* token = strtok(pathVar, ":");
    res = sprintf(pathOutput, "%s/%s", token, name);
    //assert(res >= 0);
    if(owner_can_execute(pathOutput)){
        return STATUS_SUCCESS;
    }
    while(token){
        token = strtok(NULL, ":");
        res = sprintf(pathOutput, "%s/%s", token, name);
        //assert(res >= 0);
        if(owner_can_execute(pathOutput)){
            return STATUS_SUCCESS;
        }
    }
    return STATUS_FAILURE;
}

