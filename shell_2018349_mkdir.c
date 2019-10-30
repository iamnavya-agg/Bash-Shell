#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void shell_mkdir(char **input, int count)
{
    pid_t mkdir_pid = fork();
    if (mkdir_pid == 0)
    {
        switch(count)
        {
            case 1:
            {
                execl("/bin/mkdir",input[0], NULL);
                break;
            }
            case 2:
            {
                execl("/bin/mkdir",input[0], input[1], NULL);
                break;
            }
            case 3:
            {
                execl("/bin/mkdir",input[0], input[1], input[2], NULL);
                break;
            }
            default:
            {
                execl("/bin/mkdir",input[0], input[1], input[2], input[3], NULL);
                break;
            }
        }
    }
    else
        wait(NULL);
    return;
}