#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
void Error(char *s)
{
    printf("%s",s);
    exit(-1);
}

typedef struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

struct Node
{
    float Operand;
    char Operator;
    int IsOperator;
    PtrToNode Next;
};

Stack CreateStack()
{
    Stack S = (PtrToNode)malloc(sizeof(struct Node));
    if(S == NULL)
        Error("Out of Space!");
    S->Next == NULL;
    return S;
}

void ShowStack(Stack S)
{
    PtrToNode TmpCell;
    TmpCell = S->Next;
    while(TmpCell != NULL)
    {
        printf("%.1f %c %d\n",TmpCell->Operand,TmpCell->Operator,TmpCell->IsOperator);
        if(TmpCell->Next != NULL)
            TmpCell = TmpCell->Next;
		else
			break;
    }
}

int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

void PushOpnd(int Opnd, Stack S)
{
    PtrToNode TmpCell = (PtrToNode)malloc(sizeof(struct Node));
    if(TmpCell == NULL)
        Error("Out of Space!");
    TmpCell->Operand = Opnd;
    TmpCell->IsOperator = 0;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
}

void PushOptr(char Optr, Stack S)
{
    PtrToNode TmpCell = (PtrToNode)malloc(sizeof(struct Node));
    if(TmpCell == NULL)
        Error("Out of Space!");
	TmpCell->Operator = Optr;
	TmpCell->IsOperator = 1;
	TmpCell->Next = S->Next;
	S->Next = TmpCell;
}
	
void PopOpnd(Stack S)
{
	if(S->Next->IsOperator)
		Error("You pop an Operator in PopOperand!\n");
	PtrToNode TmpCell = (PtrToNode)malloc(sizeof(struct Node));
	if(TmpCell == NULL)  
		Error("Out of Space!");

 	TmpCell = S->Next;
	S->Next = TmpCell->Next;
	free(TmpCell);
}

void PopOptr(Stack S)
{
	if(!S->Next->IsOperator)
		Error("You pop an Operand in PopOperator!\n");
	PtrToNode TmpCell = (PtrToNode)malloc(sizeof(struct Node));
	if(TmpCell == NULL)  
		Error("Out of Space!");

 	TmpCell = S->Next;
	S->Next = TmpCell->Next;
	free(TmpCell);
}

int TopOpnd(Stack S)
{
	if(IsEmpty(S))
	{
		printf("Empty Stack!");
		exit(-1);
	}
	return S->Next->Operand;
}

char TopOptr(Stack S)
{
	if(IsEmpty(S))
	{
		printf("Empty Stack!");
		exit(-1);
	}
	return S->Next->Operator;
}
 
int PriorityCmp(char op1, char op2)
 //return 1 if op1 > op2 
{
	switch(op1){
		case'(': if(op2 == '(') return 0;
				 else return 1;break;
		case'*':
		case'/': if(op2 == '(') return -1;
				 else if(op2 == '*' || op2 == '/') return 0;
				 else return 1;break;
		case'+':
		case'-': if(op2 == '+' || op2 == '-') return 0;
			     else return -1;break;
	}
}

Stack Conversion(char *s)
{
	Stack OptrStack = CreateStack();
	Stack Output = CreateStack();
	char *p = s;
	int i = 0, j, k, flag, TmpOpnd;
	while(*p)
	{
		if(isdigit(*p)){
			while(!isdigit(*p))
				p++;
			TmpOpnd = atoi(p);
			PushOpnd(TmpOpnd,Output);
			while(isdigit(*p))
				p++;
			continue;
		}
		else if(*p == ')'){
			while(TopOptr(OptrStack) != '('){
				PushOptr(TopOptr(OptrStack),Output);
				PopOptr(OptrStack);
			}
			PopOptr(OptrStack);
		}
		else if(*p == '('){
			PushOptr(*p,OptrStack);
		}
		else{
				if(IsEmpty(OptrStack))
					PushOptr(*p,OptrStack);
				else
				{
					while(!IsEmpty(OptrStack) && (PriorityCmp(*p,TopOptr(OptrStack)) < 1) && TopOptr(OptrStack) != '('){
						PushOptr(TopOptr(OptrStack),Output);
						PopOptr(OptrStack);
					}
					PushOptr(*p,OptrStack);
				}
		}
		p++;
	}
	while(!IsEmpty(OptrStack)){
		PushOptr(TopOptr(OptrStack),Output);
		PopOptr(OptrStack);
	}
	return Output;
}

Stack Reversion(Stack S)
{
	Stack Tmp = CreateStack();
	if(Tmp == NULL)
		Error("Out of Space!");
	PtrToNode P = S->Next;
	while(P != NULL){
		if(P->IsOperator)
			PushOptr(P->Operator,Tmp);
		else
			PushOpnd(P->Operand,Tmp);
		P = P->Next;
	}
	return Tmp;
}

void ShowPostFix(Stack S)
{
	PtrToNode P = S->Next;
	printf("The PostFix Expression is:");
	while(P != NULL)
	{
		if(P->IsOperator)
			printf("%c",P->Operator);
		else
			printf("%.1f ",P->Operand);
		P = P->Next;
	}
	printf("\n");
}

float Compute(Stack S)
{
	float TmpOpnd1, TmpOpnd2;
	Stack Result = CreateStack();
	PtrToNode P = S->Next;
	if(Result == NULL)
		Error("Out of Space!");
	
	while(P != NULL)
	{
		if(!P->IsOperator)
		PushOpnd(P->Operand,Result);
		else{
			TmpOpnd1 = Result->Next->Operand;
			TmpOpnd2 = Result->Next->Next->Operand;
			PopOpnd(Result);
			PopOpnd(Result);
			switch(P->Operator){
				case'+': PushOpnd(TmpOpnd1 + TmpOpnd2,Result);break;
				case'-': PushOpnd(TmpOpnd1 - TmpOpnd2,Result);break;
				case'*': PushOpnd(TmpOpnd1 * TmpOpnd2,Result);break;
				case'/': PushOpnd(TmpOpnd2 / TmpOpnd1,Result);break;
			}
		}
		P = P->Next;
	}

	return Result->Next->Operand;
}
