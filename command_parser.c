#include <stdio.h>
int expression, getval;

char **parse_command( const char* command )
{
// you should implement this function
    int i = 0, start = 0, ind = 0;
    expression = 0, getval = 0;
    char **arguments = malloc(30 * sizeof(char));

    while(command[i] != '\n' && command[i] != '\0')
    {
        if(i > 0 && command[i] != ' ' && (command[i - 1] == ' ' || command[i - 1] == '='))
        {
            if(command[i] != '$')
                start = i;
            else
            {
                start = ++i;
                getval = 1;
            }
        }
        if(getval)
        {
            for( ; (command[i] >= 'a' && command[i] <= 'z') || (command[i] >= 'A' && command[i] <= 'Z') ; i++);
            char tok[i - start];
            strncpy(tok, command + start, i - start);
            tok[i - start] = '\0';
            start = i;
            for( ; command[i] != ' ' && command[i] != '\n' ; i++);
            if(i > start)
            {
                char temp[i - start];
                strncpy(temp, command + start, i - start);
                temp[i - start] = '\0';
                char *t = malloc(strlen(tok) + strlen(temp) + 1);
                strcpy(t, lookup_variable(tok));
                strcat(t, temp);
                arguments[ind++] = strdup(t);
            }
            else
                arguments[ind++] = strdup(lookup_variable(tok));
        }
        else if(command[i] != ' ' && command[i] != '"'  && (command[i + 1] == ' ' || command[i + 1] == '\n' || command[i + 1] == '\0'))
        {
            char tok[i - start + 1];
            strncpy(tok, command + start, i - start + 1);
            tok[i - start + 1] = '\0';
            arguments[ind++] = strdup(tok);
        }
        else if(command[i] == '"')
        {
            start = ++i;
            for( ; command[i] != '"' ; i++)
            {
                if(command[i] == '$')
                {
                    start = ++i;
                    for( ; (command[i] >= 'a' && command[i] <= 'z') || (command[i] >= 'A' && command[i] <= 'Z') ; i++);
                    char tok[i - start];
                    strncpy(tok, command + start, i - start);
                    tok[i - start] = '\0';
                    start = i;
                    for( ; command[i] != ' ' && command[i] != '\n' ; i++);
                    if(i > start)
                    {
                        char temp[i - start];
                        strncpy(temp, command + start, i - start);
                        temp[i - start] = '\0';
                        char *t = malloc(strlen(tok) + strlen(temp) + 1);
                        strcpy(t, lookup_variable(tok));
                        strcat(t, temp);
                        arguments[ind++] = strdup(t);
                    }
                    else
                        arguments[ind++] = strdup(lookup_variable(tok));
                }
            }
            char tok[i - start];
            strncpy(tok, command + start, i - start);
            tok[i - start] = '\0';
            arguments[ind++] = strdup(tok);
        }
        else if(i > 0 && command[i] == '=' && command[i - 1] != ' ' && command[i - 1] != '"')
        {
            expression = 1;
            char tok[i - start];
            strncpy(tok, command + start, i - start);
            tok[i - start] = '\0';
            arguments[ind++] = strdup(tok);
            start = i + 1;
        }
        i++;
    }
    if(!ind)
        arguments[ind++] = strdup("\n");
    arguments[ind] = '\0';
    return arguments;
}

int compare_string(char *type, char word[])
{
    int i = 0, j = 0;
    while(type[i] != '\0' && word[i] != '\0')
    {
        if(type[i] == word[i])
        {
            i++;
            j++;
        }
        else
            return 0;
    }
    if(i == j)
        return 1;
    return 0;
}

int command_type(char *type)
{
    char word[][6] = {"cd", "echo", "exit", "shell", "history"};
    if(type[0] == '#' || type[0] == '\n')
        return 1;
    else if(compare_string(type, word[0]))
        return 2;
    else if(compare_string(type, word[1]))
        return 3;
    else if(compare_string(type, word[2]))
        return 4;
    else if(compare_string(type, word[3]))
        return 7;
    else if(compare_string(type, word[4]))
        return 6;
    else if(expression)
        return 8;
    else
        return 5;
}

int foreground(char *arg)
{
    int i = 0;
    char x = arg[0];
    while(arg[i] != '\0')
        x = arg[i++];
    if(x == '&')
    {
        arg[i] = '\0';
        return 0;
    }
    return 1;
}
