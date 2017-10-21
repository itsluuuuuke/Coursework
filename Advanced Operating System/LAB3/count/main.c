#include"readchar_R.h"
#include"count_M.h"
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

char ReadCharacter(int fd, int position);
int CountCharacters(int fd, char character);

int main(int argc, char **argv)
{
	int count = 0; // for counting character with readchar
	struct stat st;
	int position = 0; //for counting character with readchar
	//Check the number of the parameters
	if(argc != 4){
		printf("Incorrect Parameter! Please enter 3 parameters");
		exit(-1);
	}
	
	//Open the file indicate in the parameter
	int fd = open(argv[2],O_RDONLY);
	if(fd == -1){
		printf("Failed to open file!");
		exit(-1);
	}
	
	//Function type = readcharacter
	if(!strcmp(argv[1],"R")){
		printf("Count with readChar\n");
		//get the length of the file
		stat(argv[2],&st);
		int size = st.st_size;
		while(position != size){
			if(ReadCharacter(fd,position++)==argv[3][0])
				count++;
		}
		printf("Occurence of character %c is: ",argv[3][0]);
		printf("%d\n",count);

	}

	else if(!strcmp(argv[1],"M")){
		printf("Count with memory mapping\n");
		printf("Occurence of character %c is: ",argv[3][0]);
		printf("%d\n",CountCharacters(fd,argv[3][0]));
	}
	
	else{
		printf("Incorrect Function type! R or M\n");
		exit(-1);
	}
	return 0;
}
