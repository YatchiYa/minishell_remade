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

en_status forkExecWait(char* path, char** argv, int argc, char *envp[], int* fds){
    int     status = 0;
    int     i = 0;
    int     fdx;
	int		index;
    pid_t   pid = fork();
	char	**tmp_argv;
    int     index_output = 0;
    int     index_input = 0;
    
	tmp_argv = (char**)malloc(sizeof(argv));
	while (argv[i])
	{
		tmp_argv[i] = strdup(argv[i]);
		i++;
	}
	tmp_argv[i] = NULL;
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
		if (argv && (index) != 0)
		{
			if (index_output != 0 && strcmp(argv[index_output], ">") == 0)
			{
				if (argv[index_output + 1] == NULL)
				{
					ft_putstr("minishell > eror file not defined\n");
					return (STATUS_FAILURE);
				}
				fdx = open(argv[index_output + 1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
				if (dup2(fdx, 1) == -1)
					perror("dupp 1 ");				
			}
			if (index_input != 0 && strcmp(argv[index_input], "<") == 0)
			{
				if (argv[index_input + 1] == NULL)
				{
					ft_putstr("minishell > eror file not defined\n");
					return (STATUS_FAILURE);
				}
				fdx = open(argv[index_input + 1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
				if (dup2(fdx, 0) == -1)
					perror("dupp 1 ");		
			}
			tmp_argv = sub_argv(argv);
		}
		return execve(path, tmp_argv, envp);
	}
	else if(pid > 0)
	{
			// Parent:
		pid_t pid2 = pid;
		pid2 = waitpid(pid, &status, 0);
		char **tmp;
		tmp = trim_arg(argv, index);
		int len = wordCount(tmp);
		if (len == 1 || index == 0)
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
