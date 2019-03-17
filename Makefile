shell: main.o command_parser.o commands.o file_processing.o variables.o
	gcc -o shell main.o command_parser.o commands.o file_processing.o variables.o

main.o: main.c
	gcc -c main.c

command parser.o: command_parser.c command_parser.h
	gcc -c command_parser.c -o command_parser.o

commands.o: commands.c commands.h
	gcc -c commands.c -o commands.o

file processing.o: file_processing.c file_processing.h
	gcc -c file_processing.c -o file_processing.o

variables.o: variables.c variables.h
	gcc -c variables.c -o variables.o

clean: 
	rm command_parser
	rm commands
	rm file_processing
	rm variables
	
 
