#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void shell_cat(char **input, int count)
{
    pid_t cat_pid = fork();
    if (cat_pid == 0)
    {
        switch(count)
        {
            case 1:
            {
                execl("/bin/cat",input[0], NULL);
                break;
            }
            case 2:
            {
                execl("/bin/cat",input[0], input[1], NULL);
                break;
            }
            default:
            {
                execl("/bin/cat",input[0], input[1], input[2], NULL);
                break;
            }
        }
    }
    else
        wait(NULL);
    return;
}