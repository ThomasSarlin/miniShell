#include <stdio.h>
#include <stdlib.h>
#include "external.h"
#include "execute.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int userc;
pid_t pid[MAXCOMMANDS];
void external(command comms[], int userargc){
	pid_t pidreturn;
	userc=userargc;
	int status;
	int pipes[userargc-1][2];
	for(int i=0;i<userargc-1;i++)
		pipe(pipes[i]);

	for(int i=0;i<userargc;i++)
		if((pid[i]=fork())==0){
			if(comms[i].infile!=NULL)
				if(!redirect(comms[i].infile,READ_END,READ_END)){
					perror(comms[i].infile);
					exit(1);
				}
			if(i!=0 && userargc>1 && comms[i].infile==NULL){
				dupPipe(pipes[i-1],READ_END,READ_END);
			}
			if(comms[i].outfile!=NULL)
				if(!redirect(comms[i].outfile,WRITE_END,WRITE_END)){
					perror(comms[i].infile);
					exit(1);
				}
			if(i!=(userargc-1) && userargc>1 && comms[i].outfile==NULL){
				dupPipe(pipes[i],WRITE_END,WRITE_END);
			}
			execvp(*comms[i].argv,comms[i].argv);
		}
	for(int i=0;i<userargc-1;i++){
		close(pipes[i][0]);
		close(pipes[i][1]);
	}

	for(int i=0;i<userargc;i++){
		pidreturn=wait(&status);
		if(status==1)
			for(int j=0;j<userargc-1;j++){
				terminate();
			}
	}
}

