#include <stdio.h>
#include <unistd.h>
#include "cd.h"
#include "parser.h"
void cd(char* dir){
	if(chdir(dir))perror(dir);
}
