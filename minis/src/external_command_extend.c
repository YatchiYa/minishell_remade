#include "minishell.h"

en_status parentResult(pid_t pid1, pid_t pid2, int status){
    if(pid1 != pid2){
        //printf("Problem with fork: pids %i != %i.\n", pid1, pid2);
        return STATUS_SOFT_FAILURE;
    }
    if (WIFEXITED(status)){
        return STATUS_SUCCESS;
    }else if (WIFSIGNALED(status)){
        //printf("fork: Child ended because of an uncaught signal.\n");
        return STATUS_SOFT_FAILURE;
    }else if (WIFSTOPPED(status)){
        //printf("fork: Child process has stopped.\n");
        return STATUS_SOFT_FAILURE;
    }
    //printf("fork: Unknown error!");
    return STATUS_SOFT_FAILURE;
}

en_status processExternalCmd(char** argv, int num, char* envp[], int* fds)
{
    ctrlc = 1;
    if (strcmp(argv[wordCount(argv) - 1], "&") == 0)
    {
        ft_putstr("minishell can't handle background process \n");
        return (STATUS_SOFT_FAILURE);
    }
    char fullPath[256];
    en_status cmdResult = get_absolute_from_path(argv[0], fullPath);
    if(cmdResult == STATUS_SUCCESS)
    {
        cmdResult = forkExecWait(fullPath, argv, num, envp, fds);
    }
    else
    {
        printf("Unrecognized command: '%s'\n", argv[0]);
    }
    return cmdResult;
}
