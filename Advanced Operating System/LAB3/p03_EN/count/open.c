#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

int main()
{
	int rtvalue = open("this.txt",O_RDONLY,S_IRUSR);
	printf("return value is: %d\n",rtvalue);

	return 0;
}
