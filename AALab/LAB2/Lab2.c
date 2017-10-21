#include<stdio.h>
#include"Stack.h"
int main()
{
	while(1){
		printf("Please enter the INFIX expression:");
		char s[MAX];
		gets(s);
		Stack S = Conversion(s);
		Stack Postfix = Reversion(S);
		ShowPostFix(Postfix);
		float result = Compute(Postfix);
		printf("result = %f\n",result);
	}
    return 0;
}
