#include "parser.h"
#include "mish.h"
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
	printf("mish: ");
	while((getline(&userLine,&len,stdin))!=-1){
		userargc=parse(userLine,comms);
		for(int i=0;i<userargc;i++)
			runCommand(comms[i]);
		printf("mish: ");
	}
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

/*	int i=0;
	printf("{\n");
	printf(" Argv: [");
	while(*(com.argv+i) != NULL){
		printf("\"%s\"",(*(com.argv+i)));
		if(i<com.argc -1) printf(", ");
		i++;
			
	}	
	printf(" Argc: %d\n",com.argc);
	printf(" Infile: %s\n", com.infile);
	printf(" Outfile: %s\n", com.outfile);
	printf("}\n");
*/
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

void echo(command com){
	
	FILE *infile,*outfile;
	char c;
	if(com.infile!=NULL){
		if((infile=fopen(com.infile,"r"))==NULL){
			perror(com.infile);
			exit(1);
		}
	}
	if(com.outfile!=NULL){
		outfile=fopen(com.outfile,"w");
	}
	if(com.infile!=NULL && com.outfile!=NULL){
		while((c= getc(infile))!=EOF)
			putc(c,outfile);
		fclose(outfile);
		fclose(infile);
	}
	if(com.infile!=NULL && com.outfile==NULL){
		while((c= getc(infile))!=EOF)	
			printf("%d",c);
		fclose(infile);
	}
	if(com.infile==NULL && com.outfile==NULL){
		int i=1;
		while(*(com.argv+i)!=NULL){
			printf("%s",(*(com.argv+i)));
			(i<com.argc-1)?printf(" "):printf("\n");
			i++;
		}
	}
}
void cd(command com){
	printf("CD\n");
}
void external(command com){
	printf("External\n");
}
