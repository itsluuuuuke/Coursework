#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include"readchar_R.h"
char ReadCharacter(int fd, int position)
{
	char ch;
	lseek(fd,position,SEEK_SET);
	read(fd,ch,1);
	return ch;
}
