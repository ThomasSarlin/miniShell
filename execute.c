int dupPipe(int pip[2],int end, int destfd){
	int pipe = dup2(pip[end],destfd);
	close(pip);
	return pipe;
}


int redirect(char *filename, int flags, int desfd){
	
	int filefd,newfd;
	if(filefd = fopen(filename,flags)!=NULL){
		perror(filename);
		exit(1);
	}
	newfd=dup2(filefd,desfd);
	fclose(filefd);
	return newfd;
}
