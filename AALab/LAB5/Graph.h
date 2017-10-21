#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Queue.h"

#define MAX_VEX 7
#define INFINITY 'x'
#define DG 1
#define AG 2
#define WDG 3
#define WAG 4
#define TRUE 1
#define FALSE 0

typedef int Boolean;
typedef int ArcValType; 
typedef struct ArcType
	{
		VexType vex1, vex2;
		ArcValType ArcVal;
	}ArcType;
typedef struct MGraph
	{ 	int kind;
		VexType Vertex[MAX_VEX]; //Save the Header Node Vertex
		int Current; //Store the number of vertex
		List VEX[MAX_VEX];
	}MGraph;

typedef struct MGraph *PtrToMGraph;
typedef PtrToMGraph Graph;
Graph CreateGraph();
Graph InsertEdge(Graph G, VexType V1, VexType V2);
Graph DeleteVertex(Graph G, VexType V);
void ShowGraph(Graph G);
Graph InsertVertex(Graph G, VexType V);

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

Graph InsertEdge(Graph G, VexType V1, VexType V2)
{
	int i = 0;
	if(G->kind == DG || G->kind == WDG) //Determine whether the Graph
	{
		//Directed From V1 to V2
		for(i = 0; i<=G->Current; i++){
			if(G->Vertex[i] == V1)
				Insert(V2,G->VEX[i]);
		}
	}
	else
	{
		//Undirected Graph
		for(i = 0; i<=G->Current; i++){
			if(G->Vertex[i] == V1)
				Insert(V2,G->VEX[i]);
			else if(G->Vertex[i] == V2)
				Insert(V1,G->VEX[i]);
		}
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

int Search(VexType V, VexType *Array, int MAX)
{
	int i = 0;
	for(i = 0; i < MAX; i++)
	{
		if(Array[i] == V)
			return 1;
	}
	return 0;
}

void BFS(Graph G)
{
	printf("\nProcess of Breadth First Search\n");
	printf("//***************************//\n");
	int i,VisitedNum = 0, index;
	Position P;
	VexType Visited[100];
	Queue Q = CreateQueue(100);
	Enqueue(Q,0); /*Enqueue the first element */
	while(!QIsEmpty(Q) && VisitedNum <= G->Current)
	{
		index = Q->Array[Q->front];
		if(!Search(index,Visited,VisitedNum)){
		  Visited[VisitedNum] = index;
		  VisitedNum++;
		}
		Dequeue(Q);
		P = G->VEX[index]->Next;
		while(P->Next != NULL){
			Enqueue(Q,P->Vertex);
			P = P->Next;
		}
		printf("Visited ");
		for(i = 0; i<VisitedNum; i++)
			printf("%d ",Visited[i]);
		printf("\n");

	}
	printf("//***************************//\n");
	
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

