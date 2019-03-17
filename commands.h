#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

/*
	- This function should be responsible for implementing the "cd" shell command
*/
void cd( const char* path );

/*
	- This function should be responsible for implementing the "echo" shell command
	- Typically should lookup any variable included in the message
*/
void echo( char** message );


#endif // COMMANDS_H_INCLUDED
