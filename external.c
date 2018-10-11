/* external.h
 * Thomas Sarlin
 * Laboration 3 : Systemnära programmering, HT-18
 * Responsible for external commands
 */

#include <stdio.h>
#include <stdlib.h>
#include "external.h"
#include "execute.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
pid_t pid[MAXCOMMANDS];
int userc;

/** 
 * Name: external
 * Purpose: main function for executing user commands
 * Parameters:  array of usercommands, number of arguments
 * */
	
void external(command comms[], int userargc){
	int pipes[userargc-1][2];
	userc=userargc;
	signal(SIGINT,terminate);
	createPipes(pipes,userargc);
	run(comms,userargc,pipes);
	closePipes(pipes,userargc);
	awaitResponse(userargc);
}

/**
 * Name: createPipes
 * Purpose: creates Pipes depending on the number of arguments.(n-1)
 * Parameters: array representing the pipes,number of arguments
 * */

void createPipes(int pipes[][2],int userargc){
	for(int i=0;i<userargc-1;i++)
		if(pipe(pipes[i])){
			perror("pipe error");
			exit(1);
		};
}

/**
 * Name: run 
 * Purpose: looping trough the user commands and fork
 * Parameters: array of user commands, number of arguments
 *              array of pipes.
 * */

void run(command comms[],int userargc,int pipes[][2]){
	for(int index=0;index<userargc;index++)
		if((pid[index]=fork())==0){
				rePipe(comms[index],pipes,userargc,index);
				closePipes(pipes,userargc);
				exec(comms[index]);
		}
}

/**
 * Name: rePipe
 * Purpose: arranges the pipes for a specific command
 * Parameters: user command,pipe,number of arguments
 *             current index in command array.
 * */

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

/**
 * Name: exec
 * Purpose: executes command
 * Parameters: user command
 * Comment: exit(1) if invalid command.
 * */

void exec(command com){
	if(execvp(*com.argv,com.argv)==-1){
		perror(*com.argv);
		exit(1);
	}
}

/**
* Name: redirectEnd
* Purpose: redirecting WRITE_END or READ_END to/from file.
* Parameters: filename, WRITE_END or READ_END.
*/

void redirectEnd(char *file, int end){
	if(redirect(file,end,end)==-1){
		perror(file);
		exit(1);
	}
}

/**
* Name: notFirst
* Purpose: checking if the command is not the first command.
* Parameters: infile,user arguments, index
*/

int notFirst(char* infile,int userargc,int index){
	return (index!=0 && userargc>1 && infile==NULL);
}

/**
* Name: notLast
* Purpose: checking if the command is not the last command.
* Parameters: infile,user arguments, index
*/

int notLast(char* outfile,int userargc,int index){
	return (index!=(userargc-1) && userargc>1 && outfile==NULL);
}

/**
* Name: closePipes
* Purose: close pipes
* Parameters: array of pipes, user arguments
* Comment: will close n-1 user arguments of pipes.
*/

void closePipes(int pipes[][2], int userargc){
	for(int i=0;i<userargc-1;i++){
		if(close(pipes[i][0]))perror("pipe closing error");
		if(close(pipes[i][1]))perror("pipe closing error");
	}
}

/**
* Name: awaitResponse
* Purpose: Await status messages from children.
* Parameters: number of user arguments.
* Comment: if status 1 is returned all children will
*            be terminated.
*/

void awaitResponse(int userargc){
	pid_t pidreturn;
	int status;
	for(int i=0;i<userargc;i++){
		pidreturn=wait(&status);
		if(status==1)
			terminate(SIGKILL);
	}
}
/**
* Name: terminate
* Purpose: Kill all children
*/
void terminate(int sig){
	for(int i=0;i<userc;i++){
		if(kill(pid[i],sig))perror("kill error");
	}
}