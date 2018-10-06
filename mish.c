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
#include "linkedList.h"
int main(int argc,char **argv){
	command comms[MAXCOMMANDS];
	int userargc;
	char *userLine;
	size_t len=0;
	int waitsize=0;
	int status;
	pid_t pid;
	fprintf(stderr, "mish%% ");
	fflush(stderr);
	while((getline(&userLine,&len,stdin))!=-1){
		userargc=parse(userLine,comms);
		runCommand(comms);
		fprintf(stderr, "mish%% ");
		fflush(stderr);
	}
	free(userLine);
	return 0;
}

int runCommand(command comms[]){
	int result=-1;
	switch(checkFunction(*comms[0].argv)){
		case 0:
			echo(comms[0]);
			break;
		case 1:
			cd(comms[0]);
			break;
		default:
			result=0;
			external(comms);
			break;
	}
	return result;

}
int checkFunction(char *command){
	int result=-1;
	if(strcmp(command,"echo")==0){
		result=0;
	}else if(strcmp(command,"cd")==0){
		result=1;
	}
	return result;

}


