#include <stdio.h>
#include <stdlib.h>
#include "external.h"
#include "execute.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void external(command comms[]){
	printf("external\n");
	pid_t pid1,pid;
	int status;
	if((pid1=fork())==0){
		if(pipe!=-1){
			
		}
		execvp(*comms.argv[0],comms.argv[0]);
	
	}
}
