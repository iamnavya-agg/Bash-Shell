#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void remove_func(int count, char **input)
{
    int l;
    l = strlen(input[2]) - 1;
    char *arg = malloc(256 * sizeof(char));
    if (arg == NULL) 
    {
        perror("malloc failed");
        exit(1);
    }
    if (input[2][0] == '"' && input[2][l] == '"')
    {
        for(int i=1; i<l; i++)
        arg[i-1] = input[2][i];
        strcpy(input[2],arg);
    }
    return;
}

void shell_date(char **input, int count)
{
    pid_t date_pid = fork();
    if (date_pid == 0)
    {
        switch(count)
        {
            case 1:
            {
                execl("/bin/date",input[0], NULL);
                break;
            }
            case 2:
            {
                execl("/bin/date",input[0], input[1], NULL);
                break;
            }
            case 3:
            {
                remove_func(3,input);
                execl("/bin/date",input[0], input[1], input[2], NULL);
                break;
            }
            default:
            {
                execl("/bin/date",input[0], input[1], input[2], input[3], NULL);
                break;
            }
        }
    }
    else
        wait(NULL);
    return;
}