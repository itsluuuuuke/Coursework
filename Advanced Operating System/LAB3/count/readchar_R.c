#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include"readchar_R.h"
char ReadCharacter(int fd, int position)
{
	char ch[1];
	lseek(fd,position,SEEK_SET-1); //the -1 is for setting the beginning index to 1
	read(fd,ch,1);
	return ch[0];
}
