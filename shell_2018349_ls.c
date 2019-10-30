#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void shell_ls(char **input, int count)
{
    pid_t ls_pid = fork();
    if (ls_pid == 0)
    {
        switch(count)
        {
            case 1:
            {
                execl("/bin/ls",input[0], NULL);
                break;
            }
            case 2:
            {
                execl("/bin/ls",input[0], input[1], NULL);
                break;
            }
            default:
            {
                execl("/bin/ls",input[0], input[1], input[2], NULL);
                break;
            }
        }
    }
    else
        wait(NULL);
    return;
}