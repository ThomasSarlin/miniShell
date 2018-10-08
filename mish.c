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
	command comms[MAXCOMMANDS];
	char *userLine;

	userLoop(userLine,comms);

	free(userLine);
	return 0;
}
void userLoop(char* userLine, command comms[]){
	int userargc,status;
	size_t len;
	sysprint();
	while((getline(&userLine,&len,stdin))!=-1){
		userargc=parse(userLine,comms);
		if(userargc!=0)runCommand(comms,userargc);
		sysprint();
	}
}
void sysprint(){
	fprintf(stderr, "mish%% ");
	fflush(stderr);
}
int runCommand(command comms[],int userargc){
	int result=-1;
	switch(checkFunction(*comms[0].argv)){
		case 0:
			echo(comms[0]);
			break;
		case 1:
			if(comms[0].argc!=0)
				cd(*(comms[0].argv+1));
			else
				cd(getenv("HOME"));
			break;
		default:
			result=0;
			external(comms,userargc);
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


