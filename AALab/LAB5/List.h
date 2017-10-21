#include<stdio.h>
#include<stdlib.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int VexType;

void Error(char []);
List MakeEmpty(List L);
List CreateList();
int IsEmpty(List L);
void Insert(VexType V, List L);
void Delete(VexType V,List L);
Position Find(VexType V, List L);

struct Node{
	VexType Vertex;
	PtrToNode Next;
};

void Error(char s[])
{
	printf("%s",s);
	exit(-1);
}

List CreateList(void)
{
	List L = (PtrToNode)malloc(sizeof(struct Node));
	if(L == NULL)
		Error("Out of Space!");
	L->Next == NULL;
	return L;
}

int IsEmpty(List L)
{
	return L->Next == NULL;
}

void Insert(VexType V, List L)
{
	PtrToNode TmpCell = (PtrToNode)malloc(sizeof(struct Node));
	if(TmpCell == NULL)
		Error("Out of Space!");
	TmpCell->Vertex = V;
	TmpCell->Next = L->Next;
	L->Next = TmpCell;
//	printf("Inserted Successed!\n");
//	printf("L->Next->Vertex = %c\n",L->Next->Vertex);
}   
Position Find(VexType V, List L)
{
	Position P;

	P = L;
	while(P->Next != NULL){
		if(P->Next->Vertex == V){
//			printf("Find %c!\n",P->Next->Vertex);
			return P;
		}
		else{
			if(P->Next->Next == NULL)
				return NULL;
			P = P->Next;
		}
	}

}

void Delete(VexType V,List L)
{
	Position P = Find(V,L);
	if(P == NULL)
		return;
	PtrToNode TmpCell = (PtrToNode)malloc(sizeof(struct Node));					if(TmpCell == NULL)
		Error("Out of Space!");
	TmpCell = P->Next;
	P->Next = P->Next->Next;
	free(TmpCell);

}

void DeleteList(List L)
{
	Position P;
	P = L->Next;
	L->Next == NULL;
	while(P!=NULL)
	{
		free(P);
		P = P->Next;
	}
}

void ShowList(List L)
{   
	PtrToNode TmpCell = (PtrToNode)malloc(sizeof(struct Node));
	if(TmpCell == NULL){
		Error("Out Of Space!");
		exit(-1);
	}
	TmpCell = L->Next;
	while(TmpCell->Next != NULL){
		printf("%d->",TmpCell->Vertex);
		TmpCell = TmpCell->Next;
	}
	printf("NULL");	
}

