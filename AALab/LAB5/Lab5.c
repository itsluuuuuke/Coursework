#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main()
{
	int i;
	Graph G = CreateGraph();

	printf("GIsEmpty Function Test\n");
	if(GIsEmpty(G))
		printf("Empty Graph!\n");

//	Insert Vertices and Edges
	G = InsertVertex(G,0);
	G = InsertVertex(G,1);
	G = InsertVertex(G,2);
	G = InsertVertex(G,3);
	G = InsertVertex(G,4);
	G = InsertVertex(G,5);
	G = InsertVertex(G,6);
	G = InsertVertex(G,7);
	G = InsertEdge(G,0,1);
	G = InsertEdge(G,0,2);
	G = InsertEdge(G,1,3);
	G = InsertEdge(G,1,4);
	G = InsertEdge(G,2,5);
	G = InsertEdge(G,2,6);
	G = InsertEdge(G,3,7);
	G = InsertEdge(G,4,7);
	G = InsertEdge(G,5,7);
	G = InsertEdge(G,6,7); 

// Print Out the Graph
	ShowGraph(G);
	BFS(G);
	 
	DeleteEdge(G,0,2);
	printf("\n*After DeleteEdge*\n");
	ShowGraph(G);

	DeleteVertex(G,4);
	printf("\n*After DeleteVertex*\n");
	ShowGraph(G);

	return 0;
}

