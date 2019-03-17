#include <stdio.h>
#include <stdlib.h>

/*
	history file section
*/

FILE *history , *log , *batch;
char *directory;

void open_history_file(char *mode)
{
	// you should implement this function
	directory = malloc(150);
	strcpy(directory , getenv("HOME"));
	strcat(directory , "/");
	strcat(directory , "history.txt");
	history = fopen(directory , mode);
}

FILE* get_history_file()
{
	// you should implement this function
	return history;
}

void close_history_file()
{
	// you should implement this function
	fclose(history);
}


/*
	log file section
*/
void open_log_file()
{
	// you should implement this function
	directory = malloc(150);
	strcpy(directory , getenv("HOME"));
	strcat(directory , "/");
	strcat(directory , "log.txt");
	log = fopen(directory , "a");
}

FILE* get_log_file()
{
	// you should implement this function
	return log;
}

void close_log_file()
{
	// you should implement this function
	fclose(log);
}


/*
	CommandsBatch file section
*/
void open_commands_batch_file(char* name)
{
	// you should implement this function
	batch = fopen(name , "r");
}

FILE* get_commands_batch_file()
{
	// you should implement this function
	return batch;
}

void close_commands_batch_file()
{
	// you should implement this function
	fclose(batch);
}
