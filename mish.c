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

int main(){
	return userLoop();
}
/**
 * Name: userLoop
 * Purpose: reads input from the user with stdin
 * Parameters:  -Array av typen command struct enligt parser.h 
 * 		med information om de commandon som ska köras
 *		-antalet kommandon som användaren har angivit.
 * Return values: 1 on error, 0 on success.
 * */

int userLoop(){
	int result = 0;
	command comms[MAXCOMMANDS];
	char *userLine;
	int userargc,status;
	size_t len;
	sysprint();
	while((getline(&userLine,&len,stdin))!=-1){
		userargc=parse(userLine,comms);
		if(userargc!=0)
			runCommand(comms,userargc);
		sysprint();
	}
	free(userLine);
	return result;
}

/**
 * Name: runCommand
 * Purpose: executes commandos from the user.
 * Parameters:  -Array av typen command struct enligt parser.h 
 * 		med information om de commandon som ska köras
 *		-antalet kommandon som användaren har angivit.
 * Return values: void
 * */
void runCommand(command comms[],int userargc){
	switch(checkFunction(*comms[0].argv)){
		case 0:
			external(comms,userargc);
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

void sysprint(){
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

int checkFunction(char *command){
	int result=0;
	if(strcmp(command,"echo")==0)
		result=1;
	else if(strcmp(command,"cd")==0)
		result=2;
	return result;

}


