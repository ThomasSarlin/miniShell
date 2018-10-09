#include "parser.h"
#include <sys/types.h>

void external(command[],int);
void createPipes(int[][2],int);
void run(command[],int,int[][2]);
void rePipe(command,int[][2],int,int);
void exec(command);
void redirectEnd(char*,int);
int notFirst(char*,int,int);
int notLast(char*,int,int);
void closePipes(int[][2],int);
void terminate(void);
void awaitResponse(int[],int);
