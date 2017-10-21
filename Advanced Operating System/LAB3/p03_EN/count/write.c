#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

#define BUF_SIZE 5
int main()
{
	char buffer[BUF_SIZE];
	char* message = "This is a message for substitution";

	int handle1 = open("this.txt",O_RDONLY,S_IRUSR);
	int readResult = read(handle1,&buffer,BUF_SIZE);
	printf("Read %d characters\n",readResult);
	int result = write(handle1,&message,BUF_SIZE);
	printf("result = %d\n",result);

	readResult = read(handle1,&buffer,BUF_SIZE);
	
	return 0;
}
