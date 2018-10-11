/* external.h
 * Thomas Sarlin
 * Laboration 3 : Systemnära programmering, HT-18
 * Responsible for external commands
 */


#include "parser.h"
#include <sys/types.h>
/** 
 * Name: external
 * Purpose: main function for executing user commands
 * Parameters:  array of usercommands, number of arguments
 * */
void external(command[],int);
/**
 * Name: createPipes
 * Purpose: creates Pipes depending on the number of arguments.(n-1)
 * Parameters: array representing the pipes,number of arguments
 * */
void createPipes(int[][2],int);
/**
 * Name: run 
 * Purpose: looping trough the user commands and fork
 * Parameters: array of user commands, number of arguments
 *              array of pipes.
 * */
void run(command[],int,int[][2]);

/**
 * Name: rePipe
 * Purpose: arranges the pipes for a specific command
 * Parameters: user command,pipe,number of arguments
 *             current index in command array.
 * */
void rePipe(command,int[][2],int,int);
/**
 * Name: exec
 * Purpose: executes command
 * Parameters: user command
 * Comment: exit(1) if invalid command.
 * */
void exec(command);
/**
* Name: redirectEnd
* Purpose: redirecting WRITE_END or READ_END to/from file.
* Parameters: filename, WRITE_END or READ_END.
*/
void redirectEnd(char*,int);
/**
* Name: notFirst
* Purpose: checking if the command is not the first command.
* Parameters: infile,user arguments, index
*/
int notFirst(char*,int,int);
/**
* Name: notLast
* Purpose: checking if the command is not the last command.
* Parameters: infile,user arguments, index
*/
int notLast(char*,int,int);
/**
* Name: closePipes
* Purose: close pipes
* Parameters: array of pipes, user arguments
* Comment: will close n-1 user arguments of pipes.
*/
void closePipes(int[][2],int);

/**
* Name: awaitResponse
* Purpose: Await status messages from children.
* Parameters: number of user arguments.
* Comment: if status 1 is returned all children will
*            be terminated.
*/
void awaitResponse(int);

/**
* Name: terminate
* Purpose: send signal to children
* Parameters: Signal code
*/
void terminate(int);