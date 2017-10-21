#include<stdio.h>
#include<sys/time.h>

int main()
{		
	FILE *Out;
	if ( (Out = fopen("lab8_2_out.txt", "w")) == NULL)
	{
		printf("Error opening the file, so exiting\n");
		exit(1);
	}
	
	fprintf(Out,"unsigned int: %d bytes, %d bits\n",sizeof(unsigned int),8*sizeof(unsigned int));
   fprintf(Out,"double: %d bytes, %d bits\n",sizeof(double),8*sizeof(double));
	fprintf(Out,"long: %d bytes, %d bits\n",sizeof(long),8*sizeof(long));
	fprintf(Out,"long long : %d bytes, %d bits\n",sizeof(long long),8*sizeof(long long));
	fprintf(Out,"char : %d bytes, %d bits\n",sizeof(char),8*sizeof(char));
	fprintf(Out,"float : %d bytes, %d bits\n",sizeof(float),8*sizeof(float));
	fprintf(Out,"struct timeval : %d bytes, %d bits\n",sizeof(struct timeval),8*sizeof(struct timeval));
	
	printf("unsigned int: %d bytes, %d bits\n",sizeof(unsigned int),8*sizeof(unsigned int));
	printf("double: %d bytes, %d bits\n",sizeof(double),8*sizeof(double));
	printf("long: %d bytes, %d bits\n",sizeof(long),8*sizeof(long));
	printf("long long : %d bytes, %d bits\n",sizeof(long long),8*sizeof(long long));
	printf("char : %d bytes, %d bits\n",sizeof(char),8*sizeof(char));
	printf("float : %d bytes, %d bits\n",sizeof(float),8*sizeof(float));
	printf("struct timeval : %d bytes, %d bits\n",sizeof(struct timeval),8*sizeof(struct timeval));
	return 0;
}
