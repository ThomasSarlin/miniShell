#include <stdio.h>
#include <stdlib.h>
#include "external.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void external(command com){
	printf("external\n");
	pid_t pid1,pid;
	int status;
	if((pid1=fork())==0)
		execvp(*com.argv,com.argv);
}
