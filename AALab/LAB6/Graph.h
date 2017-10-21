#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Queue.h"

#define MAX_VEX 7
#define INFINITY 100
#define DG 1
#define AG 2
#define WDG 3
#define WAG 4
#define TRUE 1
#define FALSE 0

struct tnode;
typedef struct tnode *PtrTotnode;
typedef PtrTotnode Table;

struct tnode
{
	ArcValType Dist[MAX_VEX];
	VexType Pre[MAX_VEX];
	VexType S[MAX_VEX];
	int size;
};

typedef int Boolean;
typedef struct MGraph
	{ 	int kind;
		VexType Vertex[MAX_VEX]; //Save the Header Node Vertex
		int Current; //Store the number of vertex
		List VEX[MAX_VEX];
	}MGraph;

typedef struct MGraph *PtrToMGraph;
typedef PtrToMGraph Graph;
Graph CreateGraph();
Graph InsertEdge(Graph G, VexType V1, VexType V2, ArcValType Val);
Graph DeleteVertex(Graph G, VexType V);
void ShowGraph(Graph G);
Graph InsertVertex(Graph G, VexType V);
Table CreateTable();
int FindMin(ArcValType d[], int max);
void ShowDijkstraTable(Table T);
Table Dijkstra(Graph G);

Table CreateTable()
{
	Table T = (PtrTotnode)malloc(sizeof(struct tnode));
	if(T == NULL)
		Error("Out of Space");
	T->size = 0;
	printf("Table created successfully!!\n");
	return T;
}
	
Graph CreateGraph()
{
	int i = 0;
	unsigned int kindselect;
	printf("Please enter graph kind:\n");
	printf("1 for Directed Graph\n2 for Undirected Graph\n");
	printf("3 for Weighted Directed Graph\n4 for Weighted Undirected Graph\n");
	scanf("%d",&kindselect);
	Graph G = (PtrToMGraph)malloc(sizeof(struct MGraph));
	if(G == NULL){
		Error("Out Of Space!");
		exit(-1);
	}
	printf("\nGraph Has Been Successfully Created!\n");
	switch(kindselect){
		case 1: G->kind = DG;break;
		case 2: G->kind = AG;break;
		case 3: G->kind = WDG;break;
		case 4: G->kind = WAG;break;
	}
	G->Current= -1;
	return G;
}
Graph InsertVertex(Graph G, VexType V)
{
	if(G->Current+1 > MAX_VEX)
		Error("This Graph has reached its Max Number of Vertices!");
	G->Current++;
	G->VEX[G->Current] = (PtrToNode)malloc(sizeof(struct Node));
	Insert(V,G->VEX[G->Current]);
	G->Vertex[G->Current] = V;
//	printf("Vertex[%d] = %c\n",G->Current,G->Vertex[G->Current]);
//	printf("After Insert Vertex %c, there are %d vertices in the Graph\n",V,G->Current+1);
	return G;
}

Graph InsertEdge(Graph G, VexType V1, VexType V2, ArcValType Val)
{
	int i = 0;
	switch(G->kind){
		case WDG:
		//Directed From V1 to V2
		for(i = 0; i<=G->Current; i++){
			if(G->Vertex[i] == V1)
			{
				Insert(V2,G->VEX[i]);
				G->VEX[i]->Next->ArcVal = Val;
			}
		}break;

		case DG:
		for(i = 0; i<=G->Current; i++){
			if(G->Vertex[i] == V1)
				Insert(V2,G->VEX[i]);
		}break;

	     case AG:
	     for(i = 0; i<=G->Current; i++){
			if(G->Vertex[i] == V1)
				Insert(V2,G->VEX[i]);
			else if(G->Vertex[i] == V2)
				Insert(V1,G->VEX[i]);
		 }break;
	}

	return G;
}
Graph DeleteVertex(Graph G, VexType V)
{
	int i;
	Position P;
	//Delete the Vertex in Edges
	for(i = 0; i <= G->Current; i++)
	{
		Position P = Find(V, G->VEX[i]); 
		if(P)
			Delete(V,G->VEX[i]);
	}
	//Delete the Vertex
	for(i = 0; i<=G->Current; i++)
	{
		if(G->Vertex[i] == V){
			DeleteList(G->VEX[i]);
			free(G->VEX[i]);
			G->Vertex[i] = INFINITY;
		}

	}
	return G;
}
Graph DeleteEdge(Graph G, VexType V1, VexType V2)
{
	int i;
	for(i = 0; i <= G->Current; i++)
	{
		//Delete (V1,V2) IN V1
		if(G->Vertex[i] == V1)
				Delete(V2,G->VEX[i]);
		//Delete (V1,V2) IN V2
		else if(G->Vertex[i] == V2)
				Delete(V1,G->VEX[i]);
	}
	return G;
}
Boolean GIsEmpty(Graph G)
{
	return (G->Current == -1);
}

int FindMin(ArcValType d[],int max)
{
	int i, TmpIndex = 2;
	ArcValType tmp = d[2];
	for(i = 2; i <= max; i++)
	{
		if(d[i] < tmp){
			tmp = d[i];
     		TmpIndex = i;
		}
	}
	return TmpIndex;
}

Table Dijkstra(Graph G)
{
	int i = 1, j = 0, k = 0;
	VexType pivot = G->Vertex[0];
	ArcValType TmpVal;
	VexType Init;
	Position P;
	Table T = CreateTable();

	//Initialize the Table
	P = G->VEX[0]->Next;
	//Dist Initialize
	for(i = 0; i <= MAX_VEX; i++)
		T->Dist[i] = INFINITY;
	while(P->Next != NULL){
		Init = P->Vertex;
		T->Dist[Init] = P->ArcVal;
		P = P->Next;
	}
	//Pre, S Initialize
	for(i = 2; i <= MAX_VEX; i++)
		T->Pre[i] = pivot;
	for(i = 0; i <= MAX_VEX; i++)
		T->S[i] = INFINITY;
	
	T->size = 0;
	T->S[T->size++] = pivot;

	while(T->size < MAX_VEX-1)
	{
		pivot = FindMin(T->Dist,MAX_VEX);
		P = G->VEX[pivot-1]->Next;
		while(P->Next != NULL)
		{
			Init = P->Vertex;
//			printf("Init = %d",Init);
//			printf(" Dist[Init] = %d", T->Dist[Init]); 
			TmpVal = T->Dist[pivot] + P->ArcVal;
			//Update the corresponding Field if the path is shorter
			if(T->Dist[Init] > TmpVal && T->Dist[Init]!= INFINITY){
				T->Dist[Init] = TmpVal;
				T->Pre[Init] = pivot;
			}
			else if(T->Dist[Init] == INFINITY){
				T->Dist[Init] = P->ArcVal;
				T->Pre[Init] = pivot;
			}

			P = P->Next;
		}
			//Update the S set
			int flag = 0;
			for(i = 0; i < T->size; i++)
				if(T->S[i] == pivot)
					flag = 1;
			if(!flag)
				T->S[T->size++] = pivot;
			
			T->Dist[pivot] += INFINITY;  //Mark that pivot has been visited
	}
	return T;
}

void ShowDijkstraTable(Table T)
{
	int i;
	printf("The Shortest Path by Dijkstra's Algorithm:\n");
	printf(" i   Dist[i]   Pre[i]	\n");
	for(i = 2; i <= MAX_VEX; i++){
		if(T->Dist[i] >= INFINITY)
			printf(" %d     %d        %d \n",i,T->Dist[i]-INFINITY,T->Pre[i]);
		else
			printf(" %d     %d        %d \n",i,T->Dist[i],T->Pre[i]);
	}
	printf("S = 1 ");
	for(i = 0; i < MAX_VEX-1; i++)
		printf("%d ",T->S[i]); 
	printf("\n");
}

void ShowGraph(Graph G)
{
	printf(" /*** GRAPH TYPE: %d ***/\n",G->kind);
	int i = 0;
	for(i; i <= G->Current; i++)
	{
		if(G->Vertex[i] != INFINITY){
			printf("Vertex'%d' ->> ",G->Vertex[i]);
			ShowList(G->VEX[i]);
			printf("\n");
		}
			
	}
}

