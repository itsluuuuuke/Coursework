/*
 * STEP 1: Read the following instructions carefully.
 */

/* CODING RULES:
 * 
 * Replace the "return" statement in each function with one
 * or more lines of C code that implements the function. Your code 
 * must conform to the following style:
 *
 * int Funct(arg1, arg2, ...) {
 *     *brief description of how your implementation works 
 *     int var1 = Expr1;
 *     ...
 *     int varM = ExprM;
 *
 *     varJ = ExprJ;
 *     ...
 *     varN = ExprN;
 *     return ExprR;
 * }
 *
 * Each "Expr" is an expression using ONLY the following:
 * 1. Integer constants 0 through 255 (0xFF), inclusive. You are
 *     not allowed to use big constants such as 0xffffffff.
 * 2. Function arguments and local variables (no global variables).
 * 3. Unary integer operations ! ~
 * 4. Binary integer operations & ^ | + << >>
 *   
 * Some of the problems restrict the set of allowed operators even further.
 * Each "Expr" may consist of multiple operators. You are not restricted to
 * one operator per line.
 *
 * You are expressly forbidden to:
 * 1. Use any control constructs such as if, do, while, for, switch, etc.
 * 2. Define or use any macros.
 * 3. Define any additional functions in this file.
 * 4. Call any functions.
 * 5. Use any other operations, such as &&, ||, -, or ?:
 * 6. Use any data type other than int.  This implies that you
 *    cannot use arrays, structs, or unions.
 *
 *
 * You may assume that your machine:
 * 1. Uses 2s complement, 32-bit representations of integers.
 * 2. Performs right shifts arithmetically.
 * 3. Has unpredictable behavior when shifting an integer by more
 *    than the word size.
 */
#include<stdio.h>

/*EXAMPLES OF ACCEPTABLE CODING STYLE:
 *   pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
 */
    int pow2plus1(int x) {
       /* exploit ability of shifts to compute powers of 2 */
       return (1 << x) + 1;
    }
 
/*
 * STEP 2: Modify the following functions according the coding rules.
 */

/*
 * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
 *   Legal ops: + << 
 */
int pow2plus4(int x) {
   return (1 << x) + 4;
}

/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 */
int bitAnd(int x, int y) {
  return (x&y);
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 */
int negate(int x) {
  return (~x+1);
}

int main()
{
	int x, y;
	printf("x = :");
	scanf("%d",&x);
	printf("y = :");
	scanf("%d",&y);
	printf("pow2plus1 = %d\n",pow2plus1(x));
	printf("pow2plus4 = %d\n",pow2plus4(x));
	printf("bitAnd x&y = %d\n",bitAnd(x,y));
	printf("negate x = %d\n",negate(x));
}
	
