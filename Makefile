#makefile to compile the shell_2018349.c code

all:    #target name
		gcc shell_2018349.c
clean:	#clean the history file
		rm history.txt
		touch history.txt