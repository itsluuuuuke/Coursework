#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	char* p;
    int	fd = open("text.txt",O_RDONLY);
	if(fd == -1){
		printf("Failed to open file!");
		exit(-1);
	}
	p=mmap(0,1,PROT_READ,MAP_SHARED,fd,0);
	putchar(p[0]);
	munmap(p,1);
	return 0;
}
