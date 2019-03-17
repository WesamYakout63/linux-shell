#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cd( const char* path )
{
    // you should implement this function
    char word[] = "..";
    if(path == '\0' || path[0] == '~')
    {
        char *previous = getenv("PWD");
        setenv("PWD", getenv("HOME"), 1);
        chdir(getenv("HOME"));
        if(path[0] == '~' && strlen(path) >= 2)
        {
            char *temp = malloc(strlen(path) - 1);
            strncpy(temp, path + 1, strlen(path) - 1);
            if(chdir(temp) == -1)
            {
                perror("Error!! :");
                chdir(previous);
            }
        }
    }
    else if(compare_string(path, word))
    {
        char *mpath = getenv("PWD");
        if(strlen(mpath) > 2)
        {
            char *trnck = strrchr(mpath, '/');
            char *dir = malloc(strlen(mpath) - strlen(trnck));
            strncpy(dir, mpath, strlen(mpath) - strlen(trnck));
            setenv("PWD", dir, 1);
            chdir(path);
        }
    }
    else if(strchr(path, '/') == '\0')
    {
        char *mpath = getenv("PWD");
        strcat(mpath, path);
        setenv("PWD", mpath, 1);
        chdir(path);
    }
    else
    {
        setenv("PWD", path, 1);
        chdir(path);
    }
}


void echo(const char **message)
{
    // you should implement this function
    int i = 1;
    char *temp;
    while(message[i] != '\0')
        printf("%s ",message[i++]);
    printf("\n");
}
