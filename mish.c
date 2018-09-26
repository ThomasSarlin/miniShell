#include "parser.h"
#include "mish.h"
#include <stdio.h>


int main(int argc,char **argv){
	command arguments[MAXCOMMANDS];
	int userargc;
	char *userLine;
	size_t len=0;
	printf("mish: ");
	while((getline(&userLine,&len,stdin))!=-1){
		userargc=parse(userLine,arguments);
		echo(arguments[0], userargc);
		printf("mish: ");
	}
	return 0;
}


void echo(command arguments,int argc){
	int i=0;
	printf("{\n");
	printf(" Argv: [");
	while(*(arguments.argv+i) != NULL) {
		printf("\"%s\"",(*(arguments.argv+i)));
		if(i<arguments.argc -1) printf(", ");
		i++;
			
	}	
	printf(" Argc: %d\n",arguments.argc);
	printf(" Infile: %s\n", arguments.infile);
	printf(" Outfile: %s\n", arguments.outfile);
	printf("}\n");

}
