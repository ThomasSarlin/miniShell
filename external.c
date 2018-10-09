#include <stdio.h>
#include <stdlib.h>
#include "external.h"
#include "execute.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void external(command comms[], int userargc){
	pid_t pid[userargc];
	int pipes[userargc-1][2];

	createPipes(pipes,userargc);
	run(comms,userargc,pipes,pid);
	closePipes(pipes,userargc);
	awaitResponse(pid,userargc);
}
void createPipes(int pipes[][2],int userargc){
	for(int i=0;i<userargc-1;i++)
		if(pipe(pipes[i])){
			perror("pipe error");
			exit(1);
		};
}
void run(command comms[],int userargc,int pipes[][2],pid_t pid[]){
	for(int index=0;index<userargc;index++)
		if((pid[index]=fork())==0){
				rePipe(comms[index],pipes,userargc,index);
				closePipes(pipes,userargc);
				exec(comms[index]);
		}
}

void rePipe(command com,int pipes[][2], int userargc, int index){
	if(com.infile!=NULL)
		redirectEnd(com.infile,READ_END);
	else if(notFirst(com.infile,userargc,index))
		dupPipe(pipes[index-1],READ_END,READ_END);

	if(com.outfile!=NULL)
		redirectEnd(com.outfile,WRITE_END);
	else if(notLast(com.outfile,userargc,index))
		dupPipe(pipes[index],WRITE_END,WRITE_END);
}

void exec(command com){
	if(execvp(*com.argv,com.argv)==-1){
		perror(*com.argv);
		exit(1);
	}
}

int notFirst(char* infile,int userargc,int index){
	return (index!=0 && userargc>1 && infile==NULL);
}
int notLast(char* outfile,int userargc,int index){
	return (index!=(userargc-1) && userargc>1 && outfile==NULL);
}

void redirectEnd(char *file, int end){
	if(redirect(file,end,end)==-1){
		perror(file);
		exit(1);
	}
}

void closePipes(int pipes[][2], int userargc){
	for(int i=0;i<userargc-1;i++){
		if(close(pipes[i][0]))perror("pipe closing error");
		if(close(pipes[i][1]))perror("pipe closing error");
	}
}


void awaitResponse(int pid[],int userargc){
	pid_t pidreturn;
	int status;
	for(int i=0;i<userargc;i++){
		pidreturn=wait(&status);
		if(status==1)
			terminate(pid,userargc);
	}
}

void terminate(int pid[],int userargc){
	for(int i=0;i<userargc-1;i++)
		if(kill(pid[i],SIGKILL))perror("kill error");
}
