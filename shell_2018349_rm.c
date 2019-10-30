#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void shell_rm(char **input, int count)
{
    pid_t rm_pid = fork();
    if (rm_pid == 0)
    {
        switch(count)
        {
            case 1:
            {
                execl("/bin/rm",input[0], NULL);
                break;
            }
            case 2:
            {
                execl("/bin/rm",input[0], input[1], NULL);
                break;
            }
            case 3:
            {
                execl("/bin/rm",input[0], input[1], input[2], NULL);
                break;
            }
            default:
            {
                execl("/bin/rm",input[0], input[1], input[2], input[3], NULL);
                break;
            }
        }
    }
    else
        wait(NULL);
    return;
}