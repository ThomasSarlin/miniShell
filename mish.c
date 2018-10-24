/* mish.c
 * Thomas Sarlin
 * Laboration 3 : Systemnära programmering, HT-18
 * Responsible for running the program mish
 */

#include "parser.h"
#include "mish.h"
#include "echo.h"
#include "cd.h"
#include "external.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char **argv){
	return userLoop();
}
/**
 * Name: userLoop
 * Purpose: reads input from the user with stdin
 * Return values: 1 on error, 0 on success.
 * */

int userLoop(void){
	int result = 0;
	command comms[MAXCOMMANDS];
	char *userLine;
	int userargc;
	size_t len=0;
	sysprint();
	signal(SIGINT,sighandler);
	while((getline(&userLine,&len,stdin))!=-1){
		userargc=parse(userLine,comms);
		if(userargc!=0)
			runCommand(comms,userargc);
		sysprint();
		signal(SIGINT,sighandler);
	}
	free(userLine);
	return result;
}


/**
 * Name: runCommand
 * Purpose: executes commandos from the user.
 * Parameters:  -Array of commands (check parser.h)
 *		-number of commands
 * Return values: void
 * */

void runCommand(command comms[],int userargc){
	switch(checkFunction(*comms[0].argv)){
		case 0:
			external(comms,userargc);
			break;
		case 1:
			echo(comms[0]);
			break;
		case 2:
			if(comms[0].argc!=0)
				cd(*(comms[0].argv+1));
			else
				cd(getenv("HOME"));
			break;
		default:
			break;
	}

}

/**
 * Name: sysprint
 * Purpose: stderr print for mish command row.
 * Parameters:  void 
 * Return values: void
 * */

void sysprint(void){
	fprintf(stderr, "mish%% ");
	fflush(stderr);
}

/**
 * Name: checkFunction
 * Purpose: checks if the argument is internal or external
 * Parameters:  first argument of command
 * Return values: 0 if function is external, 1 if echo, 2 for cd
 * Comment: should not be called if there are no arguments.
 * */

int checkFunction(char *com){
	int result=0;
	if(strcmp(com,"echo")==0)
		result=1;
	else if(strcmp(com,"cd")==0)
		result=2;
	return result;

}
/**
 * Name: sighandler
 * Purpose: Ingnoring ctrl+c and instead of closing the program
 *  the prompt will be reprinted, propsing the user to enter a vaild
 *  commmand. 
 * Parameters: signal
 *  */
void sighandler(int sig){
	fprintf(stderr,"\n");
	sysprint();
}

