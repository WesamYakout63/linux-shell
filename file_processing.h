#ifndef FILE_PROCESSING_H_INCLUDED
#define FILE_PROCESSING_H_INCLUDED

/*
	history file basic functions' prototypes
*/

void open_history_file(char *mode);
FILE* get_history_file();
void close_history_file();

/*
	log file basic functions' prototypes
*/
void open_log_file();
FILE* get_log_file();
void close_log_file();

/*
	CommandsBatch file basic functions' prototypes
*/
void open_commands_batch_file(char *name);
FILE* get_commands_batch_file();
void close_commands_batch_file();

#endif // FILE_PROCESSING_H_INCLUDED
