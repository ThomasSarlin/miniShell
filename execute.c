#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int dupPipe(int pip[2],int end, int destfd){
	int pipe = dup2(pip[end],destfd);
	close(pip[0]);
	close(pip[1]);
	return pipe;
}


int redirect(char *filename, int flags, int desfd){
	
	char *flag =(flags==1)?"wb":"r";
	FILE *filefd;
	int newfd=-1;
	if((filefd = fopen(filename,flag))==NULL){
		perror(filename);
	}else{
		newfd=dup2(fileno(filefd),desfd);
	}
	fclose(filefd);
	return newfd;
}
