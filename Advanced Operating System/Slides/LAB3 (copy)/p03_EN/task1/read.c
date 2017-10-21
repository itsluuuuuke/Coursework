#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

#define BUF_SIZE 1000
int main()
{
	char buffer[BUF_SIZE];
	int handle1 = open("this.txt",O_RDONLY,S_IRUSR);
	int handle2 = open("this.txt",O_RDONLY,S_IRUSR);
	int result = read(handle1,&buffer,BUF_SIZE);
	printf("result = %d\n",result);
	result = read(handle2,&buffer,BUF_SIZE);
	printf("result = %d\n",result);

	
	return 0;
}
