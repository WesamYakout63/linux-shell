#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef enum { false = 0, true = 1 } bool;

void start_shell(bool read_from_file);
void shell_loop(bool input_from_file);
void execute(char **command, bool foregnd);
char *path;

int main(int argc, char *argv[])
{

    initalize();
    path = getenv("PATH");
    // any other early configuration should be here

    if( argc > 1 )
    {
        start(true);
    }
    else
    {
        start(false);
    }

    return 0;
}

void start(bool read_from_file)
{
    //cd(""); // let shell starts from home

    if(read_from_file)
    {
        // file processing functions should be called from here

        shell_loop(true);
    }
    else
    {
        shell_loop(false);
    }
}

void handle(int seg)
{
    return 0;
}

void handler(int sig)
{
    pid_t PID;
    PID = wait(NULL);
    open_log_file();
    fputs("fChild process was terminatedf\n", get_log_file());
    close_log_file();
}

void execute(char **command, bool foregnd)
{
    pid_t PID;
    int status;
    signal(SIGCHLD, handler);
    PID = fork();
    bool successful = false;
    if(PID == 0)
    {
        if(strchr(command[0], '/'))
        {
            if(execv(command[0], command) == -1)
                perror("Error!! :");
        }
        else
        {
            while(strlen(path) > 0 && !successful)
            {
                char *rest = strchr(path, ':');
                char *cur = malloc(strlen(path) - strlen(rest));
                strncpy(cur, path, strlen(path) - strlen(rest));
                path = strdup(++rest);
                strcat(cur, "/");
                strcat(cur, command[0]);
                if(execv(cur, command) == '\0')
                    successful = true;
            }
            if(!successful)
                perror("Error!! :");
        }
    }
    else if(PID < 0)
        perror("forking Error!! :");
    else
    {
        if(foregnd)
            wait(PID, &status, 0);
    }
    return ;
}

void shell_loop(bool input_from_file)
{
    bool from_file = input_from_file;

    while(true)
    {
        ssize_t length = 512;
        char *command = malloc(length * sizeof(char));

        if(from_file)
        {
            //read next instruction from file
            // if end of file {from_file = false; continue;}
            if(get_commands_batch_file() != '\0')
            {
                if(fgets(command, length, get_commands_batch_file()))
                    printf("%s\n", command);
                else
                {
                    close_commands_batch_file();
                    from_file = false;
                }
            }
            else
            {
                perror("Error!! , file isn`t found");
                from_file = false;
            }
        }
        if(!from_file)
        {
            //read next instruction from console
            printf("wesam`s shell --> ");
            getline(&command, &length, stdin);
        }
        open_history_file("a");
        fputs(command, get_history_file());
        close_history_file();
        char **arguments = parse_command(command), *last;
        int x = 0;
        while(arguments[x] != '\0')
            last = arguments[x++];
        int type = command_type(arguments[0]);
        bool foregnd = foreground(last);
        if(type == 1)
            continue;
        else if(type == 2)
            cd(arguments[1]);
        else if(type == 3)
            echo(arguments);
        else if(type == 4)
        {
            printf("Program successfully terminated :D , BYE!");
            break;
        }
        else if(type == 5)
            execute(arguments, foregnd);
        else if(type == 6)
        {
            open_history_file("r");
            while(!feof(get_history_file()))
            {
                char *com = malloc(512 * sizeof(char));
                fgets(com, 512, get_history_file());
                printf("%s\n", com);
            }
            close_history_file();
        }
        else if(type == 7)
        {
            from_file = true;
            open_commands_batch_file(arguments[1]);
        }
        else if(type == 8)
            set_variable(arguments[0], arguments[1]);

        //parse your command here

        //execute your command here

        /*
        	you don't need to write all logic here, a better practice is to call functions,
        	each one contains a coherent set of logical instructions
        */
    }
    //close_commands_batch_file();
}
