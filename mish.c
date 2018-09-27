#include "parser.h"
#include "mish.h"
#include "echo.h"
#include "cd.h"
#include "external.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linkedList.h"
int main(int argc,char **argv){
	command comms[MAXCOMMANDS];
	int userargc;
	char *userLine;
	size_t len=0;
	fprintf(stderr, "mish%% ");
	fflush(stderr);
	while((getline(&userLine,&len,stdin))!=-1){
		userargc=parse(userLine,comms);
		for(int i=0;i<userargc;i++)
			runCommand(comms[i]);
		fprintf(stderr, "mish%% ");
		fflush(stderr);
	}
	free(userLine);
	return 0;
}

void runCommand(command com){
	
	switch(checkFunction(*com.argv)){
		case 0:
			echo(com);
			break;
		case 1:
			cd(com);
			break;
		default:
			external(com);
			break;
	}

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


