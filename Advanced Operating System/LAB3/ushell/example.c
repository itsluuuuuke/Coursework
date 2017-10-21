/*
    example.c
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<time.h>
#include "parser.h"

#define MAX_SIZE 1000 //Use for mycp

void show_command (command * C);
void getParameters(char** buffer,command *C);
int getParameterNum(command *C);

//All the functions implement for the shell
void mypwd(void); //Show the information of the current dir
void myls(char* dirName, int detailedFlag); //List the entries of the dir
											//With detailedFlag set to 1, 
											//shows detailed field in every 
											//entry
void mymkdir(char* dirName); //Make a new directory
void myrmdir(char* dirName); //Remove a directory
void mycd(char* dirName); //Go back to the initial dir if no arg passed
void mycat(char* fileName); //Print out the content of the file
void mycp(char* inFile, char* outFile); //Copy from inFile to outFile
void myrm(char* fileName); //Remove(unlinked) the file
void exitShell(void); //Exit the shell

int main ()
{
    command C;
    int r, parameterNum = 0; //parameterNum is the number of parameters in C
	char defaultPath[100]; // Use for mycd as the default
	getcwd(defaultPath,100);
    printf ("Type commands (press Ctrl-D to finish)\n");

    do              // Read commands and show them
    {
        init_command (&C);

        printf ("$ ");
        r = read_command (&C, stdin);

        if (r < 0)
            fprintf (stderr, "\nError %d: %s\n",
                             -r, err_messages[-r]);
        else
            show_command (&C);
		
		//Retrieve the parameters from Command C
		parameterNum = getParameterNum(&C);
		char* parameter[parameterNum];
		getParameters(parameter,&C);
	
		if(!strcmp(parameter[0],"mypwd"))
			mypwd();

		else if(!strcmp(parameter[0],"myls")){
			//#parameter == 1
			if(parameterNum == 1)
				myls(defaultPath,0);
			
			//#parameter == 2
			else if(parameterNum == 2){
				if(!strcmp(parameter[1],"l"))
					myls(defaultPath,1);
				else
					myls(parameter[1],0);
			}
			else
				myls(parameter[1],1);
		}		
			
		else if(!strcmp(parameter[0],"mymkdir"))
			mymkdir(parameter[1]);

		else if(!strcmp(parameter[0],"myrmdir"))
			myrmdir(parameter[1]);

		else if(!strcmp(parameter[0],"mycd")){
			if(parameterNum == 2) //When there is a given dir
				mycd(parameter[1]);
			else
				//default
				mycd(defaultPath);
		}

		else if(!strcmp(parameter[0],"mycat"))
			mycat(parameter[1]);

		else if(!strcmp(parameter[0],"mycp")){
			if(parameterNum != 3){
				printf("Wrong number of parameters! mycp file1 file2\n");
				exit(-1);
			}
			mycp(parameter[1],parameter[2]);
		}
		
		else if(!strcmp(parameter[0],"myrm"))
			myrm(parameter[1]);

		else if(!strcmp(parameter[0],"exit"))
			exitShell();

			free_command (&C);
    }
    while (r==0);   // Repeat until error or EOF

    return 0;
}

void getParameters(char** buffer, command *C)
{
	int i;
	for(i = 0; i < C->argc; i++)
		buffer[i] = C->argv[i];
}

int getParameterNum(command *C)
{
	return C->argc;
}

void mypwd()
{
	int size = 100;
	char pathinfo[size];
	getcwd(pathinfo, size);
	printf("The information of the current directory: \n%s\n",pathinfo);
}

void myls(char* dirName, int detailedFlag)
{
	//When detailedFlag is set to 1, more info is displayed
	DIR * dir;
	dir = opendir(dirName);
	struct dirent * ptr;
	struct stat buf; //use for detailed info
	while((ptr = readdir(dir)) != NULL)
	{
		printf("\nfile/dir name : %s  ", ptr->d_name);
		if(detailedFlag){
			stat(ptr->d_name,&buf);
			printf("uid=%ld,gid=%ld,mode:%lo,",(long)buf.st_uid,(long)buf.st_gid,(unsigned long)buf.st_mode);
			printf("size=%lld bytes\n,last modification date:%s\n",(long long)buf.st_size,ctime(&buf.st_mtime));
		}
	}
	printf("\n");
		
	closedir(dir);
}

void mymkdir(char* dirName)
{
	if(mkdir(dirName,S_IRUSR) == 0) //The mode is default by read only 
		printf("Directory %s is created!\n",dirName);

	else 
		printf("Fail to create directory!\n");
}

void myrmdir(char* dirName)
{
	if(rmdir(dirName) == 0)
		printf("Successfully removed directory %s! \n",dirName);	
	else
		printf("Fail to delete directory!\n");

}

void mycd(char* dirName)
{
	if(!chdir(dirName))
		printf("Successfullt change to directory %s!\n",dirName);
	else
		printf("Failed to change directory!\n");
}

void mycat(char* fileName)
{
	char* p; //Use for memory mapping
	int fd;
	int pagesize = getpagesize();
	fd = open(fileName,S_IRUSR);
	if(!fd){
		printf("Failed to open file!");
		exit(-1);
	}
	p=mmap(0,pagesize,PROT_READ,MAP_PRIVATE,fd,0);
	printf("%s",p);
	
	printf("\n");
	munmap(p,pagesize);
}

void mycp(char* inFile, char* outFile)
{
	int fdIN,fdOUT,length;

	fdIN = open(inFile,O_RDONLY,S_IRUSR);
	if(!fdIN){
		printf("Failed to open inFile!");
		exit(-1);
	}

	fdOUT = open(outFile,O_RDWR,S_IWUSR);
	if(!fdOUT){
		printf("Failed to open inFile!");
		exit(-1);
	}
	
	length = lseek(fdIN,0,SEEK_END);
	lseek(fdIN,0,SEEK_SET);
		
	char buffer[length];
	if(read(fdIN,&buffer,length) == -1)
		printf("Failed to read file!\n");

	if(write(fdOUT,&buffer,length) == -1)	
		printf("Failed to write file!\n");
	else
		printf("Successfully copied content from %s to %s \n", inFile,outFile);
	close(fdIN);
	close(fdOUT);
	
}

void myrm(char* fileName)
{
	if(unlink(fileName) == 0)
		printf("Successfully delete file %s!\n",fileName);
	else
		printf("Failed to delete file!\n");
}

void exitShell(void)
{
	printf("Exiting shell......\n");
	exit(1);
}

void show_command (command * C)
{
    int i;

    printf ("\tRaw command: \"%s\"\n", C->raw_command);
    printf ("\tNumber of arguments: %d\n", C->argc);

    for (i=0; i<=C->argc; i++)
        if (C->argv[i] != NULL)
            printf ("\t\targv[%d]: \"%s\"\n", i, C->argv[i]);
        else
            printf ("\t\targv[%d]: NULL\n", i);

    if (C->input)
        printf ("\tInput: \"%s\"\n", C->input);

    if (C->output)
        printf ("\tOutput: \"%s\"\n", C->output);

    if (C->output_err)
        printf ("\tErr. output: \"%s\"\n", C->output_err);

    printf ("\tExecute in background: %s\n",
            C->background ? "Yes" : "No");
}


