#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "shell_2018349_date.c"
#include "shell_2018349_ls.c"
#include "shell_2018349_cat.c"
#include "shell_2018349_rm.c"
#include "shell_2018349_mkdir.c"

char **history_commands;
int pos = 0;

void write_file()
{
    FILE *filePointer = fopen("history.txt", "a");
    if ( filePointer == NULL ) 
        printf( "Error in Opening File" ); 
    else
    {
        for(int i=0; i<pos; i++)
        {
            fputs(history_commands[i], filePointer);    
            fputs("\n", filePointer);
        }
        fclose(filePointer) ;
    }
}

long read_file()
{
    FILE *filePointer = fopen("history.txt", "r");
    long his_serial = 1;
    char text[256]; 
    if ( filePointer == NULL ) 
        printf( "Error in Opening File" ); 
    else
    {
        while(fgets(text,256,filePointer) != NULL) 
        { 
          printf("%ld %s",his_serial,text) ; 
          his_serial+=1;
        } 
        fclose(filePointer) ; 
    }
    return his_serial;
}

void remove_1(int count, char **input)
{
    int l;
    if (count== 2)
    {
        l = strlen(input[1]) - 1;
        char *arg = malloc(256 * sizeof(char));
        if (arg == NULL) 
    {
        perror("malloc failed");
        exit(1);
    }
        if (input[1][0] == '"' && input[1][l] == '"')
            {
                for(int i=1; i<l; i++)
                    arg[i-1] = input[1][i];
                strcpy(input[1],arg);
            }
    }
    else if(count > 2)
    {
        l = strlen(input[count-1]) - 1;
        char * arg1 = malloc(256 * sizeof(char));
        char * arg2 = malloc(256 * sizeof(char));
        if (input[1][0] == '"' && input[count-1][l] == '"');
            {
                for(int i=1; i< strlen(input[1]); i++)
                {
                    arg1[i-1] = input[1][i];
                }
                for(int i=0; i<strlen(input[count-1])-1; i++)
                {
                    arg2[i] = input[count-1][i];
                }
                strcpy(input[1],arg1);
                strcpy(input[count-1],arg2);
            }
    }
    return;
}

void remove_2(int count, char **input)
{
    int l;
    if (count== 3)
    {
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
    }
    else if(count > 2)
    {
        l = strlen(input[count-1]) - 1;
        char * arg1 = malloc(256 * sizeof(char));
        char * arg2 = malloc(256 * sizeof(char));
        if (input[2][0] == '"' && input[count-1][l] == '"');
            {
                for(int i=1; i< strlen(input[2]); i++)
                {
                    arg1[i-1] = input[2][i];
                }
                for(int i=0; i<strlen(input[count-1])-1; i++)
                {
                    arg2[i] = input[count-1][i];
                }
                strcpy(input[2],arg1);
                strcpy(input[count-1],arg2);
            }
    }
    return;
}

char **get_input(char *hist) 
{
    char *input;
    fgets(input,256,stdin);
    input[strlen(input)-1] = '\0';
    strcpy(hist,input);
    char **command = malloc(8 * sizeof(char *));
    if (command == NULL) 
    {
        perror("malloc failed");
        exit(1);
    }
    char *token;
    int i = 0;
    token = strtok(input, " ");
    while (token != NULL) 
    {
        command[i] = token;
        i+=1;
        token = strtok(NULL, " ");
    }
    command[i] = NULL;
    return command;
}

int main()
{
    char *cwd;
    int count;
    history_commands = malloc(256 * sizeof(char *));
    do{
        char cwd[256];
        getcwd(cwd, sizeof(cwd));
        printf("navya@hp:%s$ ", cwd);   
        history_commands[pos] = malloc(sizeof(char)*256);
        char **input = get_input(history_commands[pos]);
        count = 0;
        for(count = 0; input[count] != NULL; count++)
        pos+=1;
        if (strcmp(input[0],"exit")==0)                     //Internal Command-exit
            {
                write_file();
                printf(" logout\n");
                break;
            }
        else if (strcmp(input[0],"pwd")==0)                 //Internal Command-pwd
            {
                printf("%s\n ",cwd);
            }
        else if (strcmp(input[0],"cd")==0)                  //Internal Command - cd
            {
                if (count != 1)
                    chdir(input[1]);
                else    
                printf("Please provide a path.\n");
            }
        else if (strcmp(input[0],"history")==0)           //Internal Command - history
            {
                long serial = read_file();
                for(int i=0; i<pos; i++)
                {
                    printf("%ld %s\n ",serial,history_commands[i]);
                    serial += 1;
                }
            }
        else if (strcmp(input[0],"echo")==0)              //Internal Command - echo
            {
                if (count == 1)
                    printf("\n");
                else if (strcmp(input[1],"-n")==0)
                    {
                        remove_2(count,input);
                        for(int i=2; input[i]!= NULL; i++)
                            printf("%s ",input[i]);
                    }
                else if(strcmp(input[1], "$PWD") == 0)
                    printf("%s\n ",cwd);
                else if (strcmp(input[1],"-E")==0)
                    {
                        remove_2(count,input);
                        for(int i=2; input[i]!= NULL; i++)
                            printf("%s ",input[i]);
                        printf("\n");
                    }
                else if(strcmp("*",input[1]) == 0)
                    {
                        char ** str;
                        str[0] = "ls";
                        str[1] = NULL;
                        shell_ls(input,1);
                        printf("\n");
                    }
                else
                    {
                        remove_1(count,input);
                        for(int i=1; input[i]!= NULL; i++)
                            printf("%s ",input[i]);
                        printf("\n");
                    }
            }
        else if (strcmp(input[0],"date")==0)              //External Command - date  
            {
                shell_date(input,count);
                printf("\n");
            }
        else if (strcmp(input[0],"cat")==0)              //External Command - cat  
            {
                if (count == 1)
                    printf("Error");
                else
                    shell_cat(input,count);
                printf("\n");
            }
        else if (strcmp(input[0],"ls")==0)              //External Command - ls
            {
                shell_ls(input,count);
                printf("\n");
            }
        else if (strcmp(input[0],"mkdir")==0)              //External Command - mkdir  
            {
                if (count == 1)
                    printf("mkdir: missing operand");
                else
                    shell_mkdir(input,count);
                printf("\n");
            }
        else if (strcmp(input[0],"rm")==0)              //External Command - rm  
            {
                if (count == 1)
                    printf("rm: missing operand");
                else
                    shell_rm(input,count);
                printf("\n");
            }
        else
            {
                for(int i=0; input[i] != NULL; i++)
                {
                    printf("%s ",input[i]);
                }
                printf(": command not found \n");
            }
    }while(1);
    return 0;
}