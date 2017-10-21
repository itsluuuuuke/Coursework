#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main()
{
	int i;
	Graph G = CreateGraph();
	G = InsertVertex(G,1);
	G = InsertVertex(G,2);
	G = InsertVertex(G,3);
	G = InsertVertex(G,4);
	G = InsertVertex(G,5);
	G = InsertVertex(G,6);
	G = InsertVertex(G,7);
	G = InsertEdge(G,1,2,2);
	G = InsertEdge(G,1,4,1);
	G = InsertEdge(G,2,4,3);
	G = InsertEdge(G,2,5,10);
	G = InsertEdge(G,3,1,4);
	G = InsertEdge(G,3,6,5);
	G = InsertEdge(G,4,3,2);
	G = InsertEdge(G,4,5,2);
	G = InsertEdge(G,4,6,8);
	G = InsertEdge(G,4,7,4); 
	G = InsertEdge(G,5,7,6); 
	G = InsertEdge(G,7,6,1); 

	ShowGraph(G);
	Table T = Dijkstra(G);
	ShowDijkstraTable(T);

	return 0;
}

