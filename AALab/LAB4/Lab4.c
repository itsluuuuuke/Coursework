#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define MAX 100000
#define CUTOFF 20
# define CLK_TCK CLOCKS_PER_SEC
clock_t Start, Stop;
double duration;
void Swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void Qsort( int A[], int Left, int Right );

void InsertionSort(int A[],int N)
{
    int i, j;
	int Tmp;
    for(i = 1; i < N; i++)
    {
        Tmp = A[i];
        for(j = i; j>0 && A[j-1] > Tmp; j--)
            A[j] = A[j-1];
        A[j] = Tmp;
    }
  //  printf("Insertion Sort Completed!\n");
}

int Median3 (int Arr[], int Left, int Right)
{
    int Centre = (Left + Right)/2;
    if(Arr[Left] > Arr[Centre])
        Swap(&Arr[Left],&Arr[Centre]);
    if(Arr[Left] > Arr[Right])
        Swap(&Arr[Left], &Arr[Right]);
    if(Arr[Centre] > Arr[Right]) 
        Swap(&Arr[Centre],&Arr[Right]);

    Swap(&Arr[Centre],&Arr[Right-1]);
    return Arr[Right-1];
}

void QuickSort(int Arr[],int N)
{
    Qsort(Arr, 0, N-1);
}

void Qsort( int A[], int Left, int Right )
{
    int i,j;
    int Pivot;

    if(Left + CUTOFF <= Right )
    {
        Pivot = Median3(A, Left, Right);
        i = Left; j = Right - 1;
        for( ; ; )
        {
            while(A[++i]<Pivot){};
            while(A[--j]>Pivot){};
            if(i<j)
                Swap(&A[i],&A[j]);
            else
                break;
        }
        Swap(&A[i], &A[Right-1]);

        Qsort(A, Left, i-1);
        Qsort(A, i+1, Right);
    }
    else
        InsertionSort(A+Left ,Right-Left + 1);
}


//void Quicksort()
int main()
{
    //To generate a random array with range 0-MAX and write it into Original.txt
    int i, j = 0, k;
    FILE *fp = fopen("input.txt","w+");
    srand((unsigned) time (NULL));
    int a[MAX];
    for(i = 0; i<MAX; i++)
    {
        a[i] = rand()%(MAX+1);
   //     printf("a[%d] = %4d\n",i,a[i]);
        fprintf(fp,"%d ",a[i]);
    }
    fclose(fp);
    //read integers from input.txt
    FILE *rfp = fopen("input.txt","r");
    int b[MAX];
    int c[MAX];
	int d[MAX];
    while(fscanf(rfp,"%d\n",&b[j]) == 1){
  //      printf("b[%d] = %d\n", j, b[j]);
        j++;}
    fclose(rfp);
	for(k = 0; k < MAX; k++){
		c[k] = b[k];
//		printf("c[%d] = %d\n",k,c[k]);
	}
    //Do the Sorting1
	printf("MAX = %d CUTOFF = %d \n",MAX,CUTOFF);
    Start = clock();
    QuickSort(b,MAX);
	Stop = clock();
    duration = ((double)(Stop - Start))/CLK_TCK;
    printf("QuickSort: Duration = %f\n", duration);
	Start = clock();
    InsertionSort(c,MAX);
    Stop = clock();
    duration = ((double)(Stop - Start))/CLK_TCK;
    FILE *wfp_I = fopen("Output(InsertionSort).txt","w+");
    FILE *wfp_Q = fopen("Output(QuickSort).txt","w+");
    printf("InsertionSort: Duration = %f\n", duration);
    for(i = 0; i<MAX; i++){
        fprintf(wfp_I, "%d\n",c[i]);
        fprintf(wfp_Q, "%d\n",b[i]);
	}
    fclose(wfp_I);
    fclose(wfp_Q); 
    return 0;
}

