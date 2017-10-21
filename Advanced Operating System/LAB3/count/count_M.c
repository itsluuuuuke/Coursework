#include"count_M.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>

int CountCharacters(int fd, char character)
{
	char* p;
	int i, result = 0,length = 0,pagesize;

	length = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);
	pagesize = getpagesize();

	p=mmap(0,pagesize,PROT_READ,MAP_PRIVATE,fd,0);
	for(i = 0; i <= length; i++){
		if(p[i] == character)
			result++;
	}
	
	//Unmapped the file	
	munmap(p,pagesize);
	return result;
}
