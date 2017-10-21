#include"readchar_R.h"
#include"count_M.h"
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char **argv)
{
	int i;

	if(argc != 3){
		printf("Incorrect Parameter!");
		exit(-1);
	}

	for(i = 0; i < argc; i++)
		printf("%s ",argv[i]);

	int fd = open(argv[1],O_RDONLY);
	if(fd == -1){
		printf("Failed to open file!");
		exit(-1);
	}

	printf("%d",CountCharacters(fd,argv[2]));

	return 0;
}
