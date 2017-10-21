#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define BUFFERSIZE 10

int main()
{
	int fd_src = open("myfile.txt",O_RDONLY);
	int fd_dst = open("myfile1.txt",O_RDWR);
	if(fd_src == -1 || fd_dst == -1){
		printf("Failed to open the file");
		exit(-1);
	}

	printf("File opened successfully! fd_src = %d\n fd_dst = %d\n",fd_src,fd_dst);
	
	//To read some bytes from the source file
	char buffer[BUFFERSIZE];
	read(fd_src,buffer,BUFFERSIZE);
	printf("%s\n",buffer);
	
	//To write some bytes to the destination file
	write(fd_dst,buffer,BUFFERSIZE);

	//To read some bytes from the destination file
	read(fd_dst,buffer,BUFFERSIZE);
	printf("%s\n",buffer);
	
	//Reset the offset using lseek
	lseek(fd_dst,offset,0);
	//Overwrite bytes in the destination file
	write(fd_dst,"Overwrite test",14);
	
	//To read some bytes from the destination file
	read(fd_dst,buffer,BUFFERSIZE);
	printf("%s\n",buffer);

	close(fd_src);
	close(fd_dst);
	return 0;
}


