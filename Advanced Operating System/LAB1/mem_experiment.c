/*
Program mem_experiment .c
*/

#include <stdio.h>// Declaration of printf () ( and more )
#include "dynamic_mem.h"// Decl . of things in dynamic_mem .c

// Declaration of other functions :

void hello ( void ); // Doesn 't receive or return anything
void strings ( void );// "
int three ( void ); // Receives nothing ; returns an integer
int factorial ( int ); // Receives an integer ; returns another one


// Declaration ( AND DEFINITION ) of other function:

int triple(int x)
{
    printf("Function triple(): %p\n"  //%p: pointer
           "\tValue of x : %d\n"      //%d int (in decimal)
           "\tAddress of x : %p",     //%p: another pointer
           &triple,x,&x);		  //<--- Value to show

    return 3*x;
}
//　Declaration (and def.) of some global variables:

int a = 34;
int b;
int c = -5;

float d; //d and D are not related at all
int D;   //(the C language is case-sensitive)

//Main function of the program:

int main()
{
    //local variables
    int x = 3, y;

    hello();

    printf("\n\tGlobal variables (addr.,name, value):\n");
    printf("\t\t%p a %d\n", &a,a);
    printf("\t\t%p b %d\n", &b,b);
    printf("\t\t%p c %d\n", &c,c);
    printf("\t\t%p d %f\n", &d,d);
    printf("\t\t%p D %d\n", &D,D);
    printf("\t\t%p k %d\n", &k,k);

    printf("\n\tLocal Variables(addr.,name,value):\n");
    printf("\t\t%p x %d\n",&x,x);
    printf("\t\t%p y %d\n",&y,y);

    printf("\n\tComputing 3! ...\n");
    x = factorial(three());
    printf("\t3! == %d\n",x);

    dynamic_mem();

    strings();

    return 0;
}

//Definition of the remaining functions:

void hello(void)
{
    printf("Hello world!\n");
}

int three(void)
{
    return 3;
}

int factorial(int n)
{
    int f;

    printf("\tFuntion factorial(%d): %p\n", n, &factorial);
    printf("\t\tParameter n (addr.,value): %p %d\n",&n, n);
    printf("\t\tVariable f (addr., value): %p %d\n",&f, f);

    f = n<2 ? 1 : n*factorial(n-1);

    printf("\t\tfactorial(%d) returning %d\n",n, f);

    return f;
}

void strings(void)
{
    //These two arrays have the same size
    //and contain exactly the same:
    char a[] = "hello";
    char b[] = {'h','e','l','l','o'};

    char * c = "see you later";

    printf("\n\tFunction strings(): %p\n",&strings);
    printf("\t\ta: %p  \"%s\"\n", a, a);
    printf("\t\tb: %p  \"%s\"\n", b, b);
    printf("\t\tc: %p  \"%s\"\n", c, c);
    printf("\t\t&c: %p\n",&c);

    printf("\t\tPlaying a bit with c...\n");

    c = a;
    *c = 'H';

    printf("\t\ta: %p  \"%s\"\n",a, a);
    printf("\t\tb: %p  \"%s\"\n",b, b);
    printf("\t\tc: %p  \"%s\"\n",c, c);
    printf("\t\t&c : %p\n", &c);
}
