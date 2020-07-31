#include "minishell.h"

en_status parentResult(pid_t pid1, pid_t pid2, int status){
    if(pid1 != pid2){
        printf("Problem with fork: pids %i != %i.\n", pid1, pid2);
        return STATUS_SOFT_FAILURE;
    }
    if (WIFEXITED(status)){
        return STATUS_SUCCESS;
    }else if (WIFSIGNALED(status)){
        printf("fork: Child ended because of an uncaught signal.\n");
        return STATUS_SOFT_FAILURE;
    }else if (WIFSTOPPED(status)){
        printf("fork: Child process has stopped.\n");
        return STATUS_SOFT_FAILURE;
    }
    printf("fork: Unknown error!");
    return STATUS_SOFT_FAILURE;
}

// Fork and execve, don't wait, exit. Used to get rid of zombie processes.
// Parent waits for this process. Resulting in orphan child process.
en_status secondFork(char* path, char** argv, int argc, char* envp[], int* fds){
    pid_t pid = fork();
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
        return execve(path, argv, envp);
    }else if(pid > 0){
        // Middle Parent (Exits immediately after fork()):
        printf("Child process started: [%i].\n", pid);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}

// Ampersand & - Fork and execve without waiting for child process to finish
// Return: int returnStatus (See enum in definitions.h)
en_status forkExecNoWait(char* path, char** argv, int argc, char* envp[], int* fds){
    int status;
    pid_t pid = fork();
    if(pid == 0){
        // Child:
        secondFork(path, argv, argc, envp, fds);
    }else if(pid > 0){
        // Parent:
        pid_t pid2 = pid;
        pid2 = waitpid(pid, &status, 0);
        return parentResult(pid, pid2, status);
    }
    printf("Problem with fork: Returned %i.\n", pid);
    return STATUS_SOFT_FAILURE;
}

int			rediret_index(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], "<") == 0)
			return (i);
		i++;
	}
	return (0);
}

char		**sub_argv(char **argv)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (char**)malloc(sizeof(argv));
	while (argv[i] && strcmp(argv[i], ">") != 0 && strcmp(argv[i], "<") != 0)
	{
		tmp[i] = strdup(argv[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
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
	tmp = (char**)malloc(sizeof(argv));
	while (argv[i])
	{
		if (i == index)
			i += 2;
		if (argv[i])
		{
			tmp[j] = strdup(argv[i]);
			j++;
			i++;
		}
	}
	tmp[i] = NULL;
	return (tmp);
}

en_status redirect_commande_external(char* path, char **argv, int index, char *envp[], int* fds)
{
	int			fdx;
    pid_t   	pid = fork();
	int     	status = 0;
	char		**tmp_arg;

	tmp_arg = sub_argv(argv);
	if (pid == 0)
    {
		if (fds)
		{
			if (strcmp(argv[index], ">") == 0)
			{
				if (argv[index + 1] == NULL)
				{
					ft_putstr("minishell > eror file not defined\n");
					return (STATUS_FAILURE);
				}
				fdx = open(argv[index + 1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
				dup2(fdx, 1);
			}
			else
				dup2(fds[1], 1);
			if (strcmp(argv[index], "<") == 0)
			{
				if (argv[index + 1] == NULL)
				{
					ft_putstr("minishell > eror file not defined\n");
					return (STATUS_FAILURE);
				}
				fdx = open(argv[index + 1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
				dup2(fdx, 0);
			}
			else
				dup2(fds[0], 0);
		}
		if (strcmp(argv[index], ">") == 0)
		{
			
			if (argv[index + 1] == NULL)
			{
				ft_putstr("minishell > eror file not defined\n");
				return (STATUS_FAILURE);
			}
			fdx = open(argv[index + 1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
			if (dup2(fdx, 1) == -1)
				perror("dupp");
		}
		if (strcmp(argv[index], "<") == 0)
		{
			if (argv[index + 1] == NULL)
			{
				ft_putstr("minishell > eror file not defined\n");
				return (STATUS_FAILURE);
			}
			fdx = open(argv[index + 1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
			dup2(fdx, 0);
		}
		printf("debug 44\n");
		return execve(path, tmp_arg, envp);
    }
	else if(pid > 0)
	{
			// Parent:
			printf("debug 55\n");
		char		**tmp = trim_arg(argv, index);
			printf("debug 55\n");
		pid_t pid2 = pid;
		pid2 = waitpid(pid, &status, 0);
		if (tmp[0] && strcmp(tmp[0], " ") != 0 &&
			parentResult(pid, pid2, status) ==  STATUS_SUCCESS)
			return forkExecWait(path, tmp, index, envp, fds);
		else
			return (parentResult(pid, pid2, status));
	}
	printf("Problem with fork: Returned %i.\n", pid);
	return STATUS_SOFT_FAILURE;
}

en_status forkExecWait(char* path, char** argv, int argc, char *envp[], int* fds){
    int     status = 0;
    int     i = 0;
    int     fdx;
	int		index;
    pid_t   pid = fork();
    
	if (argv && (index = rediret_index(argv)) != 0)
		return (redirect_commande_external(path, argv, index, envp, fds));
	else
	{
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
			return execve(path, argv, envp);
		}
		else if(pid > 0)
		{
				// Parent:
			pid_t pid2 = pid;
			pid2 = waitpid(pid, &status, 0);
			return parentResult(pid, pid2, status);
		}
		printf("Problem with fork: Returned %i.\n", pid);
		return STATUS_SOFT_FAILURE;
	}
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

en_status processExternalCmd(char** argv, int num, char* envp[], int* fds){
    bool willWait = true;

    char* lastArgument = argv[num-1];
    ////assert(lastArgument);
    int length = strlen(lastArgument);
    if(lastArgument[length-1] == '&'){
        lastArgument[length-1] = 0;
        if(length == 1){
            argv[num-1] = NULL;
            --num;
        }
        willWait = false;
    }
    char fullPath[256];
    en_status cmdResult = get_absolute_from_path(argv[0], fullPath);
    if(cmdResult == STATUS_SUCCESS)
    {
        if(willWait){
            cmdResult = forkExecWait(fullPath, argv, num, envp, fds);
        }else{
            cmdResult = forkExecNoWait(fullPath, argv, num, envp, fds);
        }
    }
    else
    {
        printf("Unrecognized command: '%s'\n", argv[0]);
    }
    return cmdResult;
}
