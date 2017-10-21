#include"count_M.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int CountCharacters(int fd, char character);
{
	char* p;
	int result = 0;
	p=mmap(0,sys_conf(_SC_PAGESIZE),PROT_READ,MAP_PRIVATE,fd,0);
	for(int i = 0; i <= sizeof(p); i++){
		if(p[i] == character)
			result++;
	}

	return result;
}
