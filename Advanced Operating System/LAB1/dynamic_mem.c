/*
dynamic_mem .c
*/

# include <stdio.h> // Declaration of printf () ( and more )
# include <stdlib.h> // Decl . of malloc () , free () , ...

# include "dynamic_mem.h" //The .h of this module is included
//in order to ensure that the
//declarations match their
//corresponding definitions


// Global variable " promised " in
// the .h with the extern declaration :

int k;

// Function that makes some experiments with dynamic memory :
void dynamic_mem ( void )
{
    int * p; // "p is a pointer to integer ", or more literally :
    // "* p is an integer " ( declaration resembles use )

    char * q , * r , * s; // More ( and yes : we need to repeat the *)

    printf("\n\tFunction dynamic_mem (): %p\n" , & dynamic_mem );

    printf("\n\tLocal variables ( addr ., name , value ):\n" );
    printf("\t\t%p p %p\n" , &p , p );
    printf("\t\t%p q %p\n" , &q , q );
    printf("\t\t%p r %p\n" , &r , r );
    printf("\t\t%p s %p\n" , &s , s );

// Ask for dynamic memory ( malloc ==" allocate memory "):
    p = ( int *) malloc (7 * sizeof ( int )); // 7 integers
    q = ( char *) malloc (37 * sizeof ( char )); // 37 char
    r = ( char *) malloc (5 * sizeof ( char )); // 5 char
    s = ( char *) malloc ( sizeof ( char )); // 1 char

//( int *) and ( char *) are type conversions , needed
//cause malloc reserves bytes in bulk , and returns a
//generic pointer ( void *) , so we convert it to the
//right type before making the assignment

    if (p == NULL || q == NULL || r == NULL || s == NULL )
    {
        if (p != NULL ) free (p );// If any reservation failed ,
        if (q != NULL ) free (q );// undo the others , and
        if (r != NULL ) free (r );// get out of this function
        if (s != NULL ) free (s );
        return ;
    }

    printf("\n\ tMemory blocks reserved :\ n" );
    printf("\t\tp (7 integers ): %p\n" , p );
    printf("\t\tq (37 integers ): %p\n" , q );
    printf("\t\tr (5 char ): %p\n" , r );
    printf("\t\ts (1 char ): %p\n" , s );

    printf ("\n\tPointer arithmetics :\ n" );
    printf ("\t\tp = %p\t p +1 = %p\n" , p , p +1);
    printf ("\t\tq = %p\t q +1 = %p\n" , q , q +1);

    *r = 'H'; // *r is the same as r[0]
    r[1] = 'o'; // r [1] is the same as *(r+1)
    r[2] = 'w';
    r[3] = '\0'; // Mark the end of the string
    free(p);
    free(q);
    free(r);
    free(s);
}



